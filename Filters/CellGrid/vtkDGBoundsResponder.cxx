/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDGBoundsResponder.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDGBoundsResponder.h"

#include "vtkBoundingBox.h"
#include "vtkCellGrid.h"
#include "vtkCellGridBoundsQuery.h"
#include "vtkDGHex.h"
#include "vtkDataSetAttributes.h"
#include "vtkIdTypeArray.h"
#include "vtkObjectFactory.h"
#include "vtkStringToken.h"
#include "vtkTypeInt64Array.h"

#include <unordered_set>

VTK_ABI_NAMESPACE_BEGIN

using namespace vtk::literals;

vtkStandardNewMacro(vtkDGBoundsResponder);

bool vtkDGBoundsResponder::Query(
  vtkCellGridBoundsQuery* query, vtkCellMetadata* cellType, vtkCellGridResponders* caches)
{
  (void)query;
  (void)cellType;
  (void)caches;

  auto* grid = cellType->GetCellGrid();
  if (!grid->GetShapeAttribute())
  {
    return false;
  }
  // TODO: A better way to get at this is to go through the grid's shape attribute.
  auto* pts = grid->GetAttributes("coordinates"_token)->GetVectors();
  std::string cellTypeName = cellType->GetClassName();
  vtkStringToken cellAttrName(cellTypeName.substr(3));
  auto* conn = vtkTypeInt64Array::SafeDownCast(grid->GetAttributes(cellAttrName)->GetArray("conn"));
  if (!pts || !conn)
  {
    return false;
  }
  std::unordered_set<std::int64_t> pointIDs;
  int nc = conn->GetNumberOfComponents();
  std::vector<vtkTypeInt64> entry;
  entry.resize(nc);
  for (vtkIdType ii = 0; ii < conn->GetNumberOfTuples(); ++ii)
  {
    conn->GetTypedTuple(ii, &entry[0]);
    for (int jj = 0; jj < nc; ++jj)
    {
      pointIDs.insert(entry[jj]);
    }
  }
  if (pts->GetNumberOfTuples() > 0)
  {
    std::vector<double> pcoord;
    int dim = pts->GetNumberOfComponents();
    pcoord.resize(dim);

    // Initialize the bounds:
    vtkBoundingBox bbox;
    pts->GetTuple(
      0, &pcoord[0]); // TODO: Check isnan/isinf() on each component and iterate if true.
    bbox.SetMinPoint(&pcoord[0]);
    bbox.SetMaxPoint(&pcoord[0]);

    for (const auto& pointID : pointIDs)
    {
      pts->GetTuple(pointID, &pcoord[0]);
      bbox.AddPoint(&pcoord[0]);
    }
    query->AddBounds(bbox);
  }
  return true;
}

VTK_ABI_NAMESPACE_END
