#pragma once

#include "../../Vector.hpp"
#include "LayoutPolicy.hpp"

#include "MatrixExpression.hpp"
namespace Candy::Math
{
  typedef uint8_t index_t;
  
  
  template<index_t MATRIX_COLUMNS, index_t MATRIX_ROWS>
  struct MatrixIndexData
  {
    static constexpr index_t COLUMNS = MATRIX_COLUMNS;
    static constexpr index_t ROWS = MATRIX_ROWS;
    static constexpr index_t TOTAL_SIZE = COLUMNS*ROWS;
    static constexpr bool IS_SQUARE = COLUMNS == ROWS;
    static constexpr bool isLeaf=true;
    
  };
  
  template<typename DATA_TYPE, index_t MATRIX_COLUMNS, index_t MATRIX_ROWS, class LayoutPolicy=LayoutPolicyLeftToRight>
  requires(ValidLayoutPolicy<index_t, MATRIX_COLUMNS, MATRIX_ROWS, LayoutPolicy>)
  class AbstractMatrixBase : public MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>, public LayoutPolicy
  {
  public:
    
    using MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>::COLUMNS;
    using MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>::ROWS;
    using MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>::TOTAL_SIZE;
    using MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>::IS_SQUARE;
    using MatrixIndexData<MATRIX_COLUMNS, MATRIX_ROWS>::isLeaf;
    
  public:
    [[nodiscard]] constexpr index_t GetColumnCount()const{return COLUMNS;}
    [[nodiscard]] constexpr index_t GetRowCount()const{return ROWS;}
    [[nodiscard]] constexpr index_t GetTotalSize()const{return TOTAL_SIZE;}
    [[nodiscard]] constexpr bool IsSquare()const{return IS_SQUARE;}
  
  };
  
  
  

  
  
  
  
  




}