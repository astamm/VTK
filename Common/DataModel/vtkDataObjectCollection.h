/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDataObjectCollection.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkDataObjectCollection
 * @brief   maintain an unordered list of data objects
 *
 * vtkDataObjectCollection is an object that creates and manipulates ordered
 * lists of data objects. See also vtkCollection and subclasses.
 */

#ifndef vtkDataObjectCollection_h
#define vtkDataObjectCollection_h

#include "vtkCollection.h"
#include "vtkCommonDataModelModule.h" // For export macro

#include "vtkDataObject.h" // Needed for inline methods

VTK_ABI_NAMESPACE_BEGIN
class VTKCOMMONDATAMODEL_EXPORT vtkDataObjectCollection : public vtkCollection
{
public:
  static vtkDataObjectCollection* New();
  vtkTypeMacro(vtkDataObjectCollection, vtkCollection);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Add a data object to the bottom of the list.
   */
  void AddItem(vtkDataObject* ds) { this->vtkCollection::AddItem(ds); }

  /**
   * Get the next data object in the list.
   */
  vtkDataObject* GetNextItem() { return static_cast<vtkDataObject*>(this->GetNextItemAsObject()); }

  /**
   * Get the ith data object in the list.
   */
  vtkDataObject* GetItem(int i) { return static_cast<vtkDataObject*>(this->GetItemAsObject(i)); }

  /**
   * Reentrant safe way to get an object in a collection. Just pass the
   * same cookie back and forth.
   */
  vtkDataObject* GetNextDataObject(vtkCollectionSimpleIterator& cookie)
  {
    return static_cast<vtkDataObject*>(this->GetNextItemAsObject(cookie));
  }

protected:
  vtkDataObjectCollection() = default;
  ~vtkDataObjectCollection() override = default;

private:
  // hide the standard AddItem from the user and the compiler.
  void AddItem(vtkObject* o) { this->vtkCollection::AddItem(o); }

private:
  vtkDataObjectCollection(const vtkDataObjectCollection&) = delete;
  void operator=(const vtkDataObjectCollection&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
