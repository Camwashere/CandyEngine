#pragma once
#include <spdlog/fmt/ostr.h> // must be included
#include "matrix/base/MatrixBase.hpp"
#include "matrix/specialization/Matrix4RowMajor.hpp"
#include "matrix/specialization/Matrix4ColumnMajor.hpp"


#define MATRIX_LAYOUT_TYPE 1

namespace Candy::Math
{
  #if MATRIX_LAYOUT_TYPE
  typedef AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Matrix4;
  #else
  typedef AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Matrix4;
  #endif
  
}

