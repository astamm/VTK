/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkQtTreeView.h

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
 * @class   vtkQtTreeView
 * @brief   A VTK view based on a Qt tree view.
 *
 *
 * vtkQtTreeView is a VTK view using an underlying QTreeView.
 *
 * @par Thanks:
 * Thanks to Brian Wylie from Sandia National Laboratories for implementing
 * this class
 */

#ifndef vtkQtTreeView_h
#define vtkQtTreeView_h

#include "vtkQtView.h"
#include "vtkViewsQtModule.h" // For export macro

#include "vtkSmartPointer.h" // Needed for member variables
#include <QList>             // Needed for member variables
#include <QPointer>          // Needed for member variables

class QAbstractItemDelegate;
class QAbstractItemView;
class QColumnView;
class QItemSelection;
class QModelIndex;
class QTreeView;
class QItemSelectionModel;
class QVBoxLayout;

VTK_ABI_NAMESPACE_BEGIN
class QFilterTreeProxyModel;
class vtkApplyColors;
class vtkQtTreeModelAdapter;

class VTKVIEWSQT_EXPORT vtkQtTreeView : public vtkQtView
{
  Q_OBJECT

Q_SIGNALS:
  void expanded(const QModelIndex&);
  void collapsed(const QModelIndex&);
  void updatePreviewWidget(const QModelIndex&);

public:
  static vtkQtTreeView* New();
  vtkTypeMacro(vtkQtTreeView, vtkQtView);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Get the main container of this view (a  QWidget).
   * The application typically places the view with a call
   * to GetWidget(): something like this
   * this->ui->box->layout()->addWidget(this->View->GetWidget());
   */
  QWidget* GetWidget() override;

  /**
   * Have the view show/hide its column headers (default is ON)
   */
  void SetShowHeaders(bool);

  /**
   * Have the view alternate its row colors (default is OFF)
   */
  void SetAlternatingRowColors(bool);

  /**
   * Have the view alternate its row colors (default is OFF)
   */
  void SetEnableDragDrop(bool);

  /**
   * Show the root node of the tree (default is OFF)
   */
  void SetShowRootNode(bool);

  /**
   * Hide the column of the given index from being shown in the view
   */
  void HideColumn(int i);

  /**
   * Show the column of the given index in the view
   */
  void ShowColumn(int i);

  /**
   * Hide all but the first column in the view
   */
  void HideAllButFirstColumn();

  /**
   * The column used to filter on
   */
  void SetFilterColumn(int i);

  /**
   * The column used to filter on
   */
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
  void SetFilterRegExp(const QRegularExpression& pattern);
#else
  void SetFilterRegExp(const QRegExp& pattern);
#endif

  /**
   * The column used to filter on
   */
  void SetFilterTreeLevel(int level);

  /**
   * Collapses the model item specified by the index.
   */
  void Collapse(const QModelIndex& index);

  /**
   * Collapses all expanded items.
   */
  void CollapseAll();

  /**
   * Expands the model item specified by the index.
   */
  void Expand(const QModelIndex& index);

  /**
   * Expands all expandable items.
   * Warning: if the model contains a large number of items,
   * this function will take some time to execute.
   */
  void ExpandAll();

  /**
   * Expands all expandable items to the given depth.
   */
  void ExpandToDepth(int depth);

  /**
   * Resizes the column given to the size of its contents.
   */
  void ResizeColumnToContents(int column);

  /**
   * Set whether to use a QColumnView (QTreeView is the default)
   */
  void SetUseColumnView(int state);

  /**
   * Updates the view.
   */
  void Update() override;

  /**
   * Set item delegate to something custom
   */
  void SetItemDelegate(QAbstractItemDelegate* delegate);

  ///@{
  /**
   * The array to use for coloring items in view.  Default is "color".
   */
  void SetColorArrayName(const char* name);
  const char* GetColorArrayName();
  ///@}

  ///@{
  /**
   * Whether to color vertices.  Default is off.
   */
  void SetColorByArray(bool vis);
  bool GetColorByArray();
  vtkBooleanMacro(ColorByArray, bool);
  ///@}

  void ApplyViewTheme(vtkViewTheme* theme) override;

protected:
  vtkQtTreeView();
  ~vtkQtTreeView() override;

  void AddRepresentationInternal(vtkDataRepresentation* rep) override;
  void RemoveRepresentationInternal(vtkDataRepresentation* rep) override;

private Q_SLOTS:
  void slotQtSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
  void SetVTKSelection();
  vtkMTimeType CurrentSelectionMTime;
  vtkMTimeType LastInputMTime;

  vtkSetStringMacro(ColorArrayNameInternal);
  vtkGetStringMacro(ColorArrayNameInternal);

  QPointer<QTreeView> TreeView;
  QPointer<QColumnView> ColumnView;
  QPointer<QWidget> Widget;
  QPointer<QVBoxLayout> Layout;
  QPointer<QItemSelectionModel> SelectionModel;
  QList<int> HiddenColumns;
  vtkQtTreeModelAdapter* TreeAdapter;
  QAbstractItemView* View;
  char* ColorArrayNameInternal;
  QFilterTreeProxyModel* TreeFilter;

  vtkSmartPointer<vtkApplyColors> ApplyColors;

  vtkQtTreeView(const vtkQtTreeView&) = delete;
  void operator=(const vtkQtTreeView&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
