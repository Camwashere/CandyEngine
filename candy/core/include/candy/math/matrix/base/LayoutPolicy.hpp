#pragma once
#include <cstdint>
#include <concepts>
namespace Candy::Math
{
  
  
  template<typename INDEX_TYPE, INDEX_TYPE MATRIX_COLUMNS, INDEX_TYPE MATRIX_ROWS, class LayoutPolicy>
  concept ValidLayoutPolicy =
  requires(LayoutPolicy layoutPolicy)
  {
    {LayoutPolicy::template AccessIndex<INDEX_TYPE, MATRIX_COLUMNS, MATRIX_ROWS>(INDEX_TYPE(), INDEX_TYPE())} -> std::same_as<INDEX_TYPE>;
    
  };
  
  
  struct LayoutPolicyLeftToRight
  {
    template<typename T, T COLUMNS, T ROWS>
    requires(std::is_unsigned_v<T>)
    static constexpr T AccessIndex(T row, T column){return column+row*COLUMNS;}
  };
  
 
  
  struct LayoutPolicyTopToBottom
  {
    
    template<typename T, T COLUMNS, T ROWS>
    requires(std::is_unsigned_v<T>)
    static constexpr T AccessIndex(T row, T column){return row+column*ROWS;}
  };
  
  
  
  
}