/*=========================================================================

Program:   Visualization Toolkit
Module:    vtkFileResourceStream.h

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkFileResourceStream_h
#define vtkFileResourceStream_h

#include "vtkIOCoreModule.h" // For export macro
#include "vtkResourceStream.h"

#include <memory> // for std::unique_ptr

VTK_ABI_NAMESPACE_BEGIN

/**
 * @brief vtkResourceStream implementation for file input
 */
class VTKIOCORE_EXPORT vtkFileResourceStream : public vtkResourceStream
{
  struct vtkInternals;

public:
  vtkTypeMacro(vtkFileResourceStream, vtkResourceStream);
  static vtkFileResourceStream* New();
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * @brief Open a file
   *
   * Opening a file reset the stream to intial position: Tell() = 0.
   * EndOfStream is set to true if file opening failed.
   * If path is nullptr, the file will only be closed.
   * This function will increase modified time.
   *
   * @param path the file path
   * @return true if file was succefully opened, false otherwise.
   * Return false if path is nullptr.
   */
  bool Open(VTK_FILEPATH const char* path);

  ///@{
  /**
   * @brief Override vtkResourceStream functions
   */
  std::size_t Read(void* buffer, std::size_t bytes) override;
  bool EndOfStream() override;
  vtkTypeInt64 Seek(vtkTypeInt64 pos, SeekDirection dir) override;
  vtkTypeInt64 Tell() override;
  ///@}

protected:
  vtkFileResourceStream();
  ~vtkFileResourceStream() override = default;
  vtkFileResourceStream(const vtkFileResourceStream&) = delete;
  vtkFileResourceStream& operator=(const vtkFileResourceStream&) = delete;

private:
  std::unique_ptr<vtkInternals> Impl;
};

VTK_ABI_NAMESPACE_END

#endif
