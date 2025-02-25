/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkQtRecordView.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/
/**
 * @class   vtkQtRecordView
 * @brief   Superclass for QAbstractItemView-based views.
 *
 *
 * This superclass provides all the plumbing to integrate a QAbstractItemView
 * into the VTK view framework, including reporting selection changes and
 * detecting selection changes from linked views.
 *
 * @par Thanks:
 * Thanks to Brian Wylie from Sandia National Laboratories for implementing
 * this class
 */

#ifndef vtkQtRecordView_h
#define vtkQtRecordView_h

#include "vtkQtView.h"
#include "vtkSmartPointer.h"  // Needed for data table member
#include "vtkViewsQtModule.h" // For export macro
#include <QPointer>           // Needed for the text widget member

class QTextEdit;

VTK_ABI_NAMESPACE_BEGIN
class vtkDataObjectToTable;

class VTKVIEWSQT_EXPORT vtkQtRecordView : public vtkQtView
{
  Q_OBJECT

public:
  static vtkQtRecordView* New();
  vtkTypeMacro(vtkQtRecordView, vtkQtView);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Get the main container of this view (a  QWidget).
   * The application typically places the view with a call
   * to GetWidget(): something like this
   * this->ui->box->layout()->addWidget(this->View->GetWidget());
   */
  QWidget* GetWidget() override;

  enum
  {
    FIELD_DATA = 0,
    POINT_DATA = 1,
    CELL_DATA = 2,
    VERTEX_DATA = 3,
    EDGE_DATA = 4,
    ROW_DATA = 5,
  };

  ///@{
  /**
   * The field type to copy into the output table.
   * Should be one of FIELD_DATA, POINT_DATA, CELL_DATA, VERTEX_DATA, EDGE_DATA.
   */
  vtkGetMacro(FieldType, int);
  void SetFieldType(int);
  ///@}

  vtkGetMacro(CurrentRow, int);
  vtkGetStringMacro(Text);

  /**
   * Updates the view.
   */
  void Update() override;

protected:
  vtkQtRecordView();
  ~vtkQtRecordView() override;

  void AddRepresentationInternal(vtkDataRepresentation* rep) override;
  void RemoveRepresentationInternal(vtkDataRepresentation* rep) override;

  vtkSmartPointer<vtkDataObjectToTable> DataObjectToTable;

  QPointer<QTextEdit> TextWidget;

  char* Text;
  int FieldType;
  int CurrentRow;

private:
  vtkQtRecordView(const vtkQtRecordView&) = delete;
  void operator=(const vtkQtRecordView&) = delete;

  vtkMTimeType CurrentSelectionMTime;
  vtkMTimeType LastInputMTime;
  vtkMTimeType LastMTime;
};

VTK_ABI_NAMESPACE_END
#endif
