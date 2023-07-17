#pragma once
#include <concepts>
namespace Candy {
  template<typename T>
  concept PostIncrementable = requires(T a){ a++; };
  template<typename T>
  concept PreIncrementable = requires(T a){ ++a; };
  template<typename T>
  concept Incrementable = requires (T a){++a; a++;};
  
  template<typename... T>
  concept FloatingPoint = requires{std::is_floating_point_v<T...>;};
  
  template<typename... T>
  concept Unsigned = requires{std::is_unsigned_v<T...>;};
  
  template<typename...T>
  concept Signed = requires{std::is_signed_v<T...>;};
  
  template<typename T>
  concept Integral = requires{std::is_integral_v<T>;};
  
  template<typename... T>
  concept Numeric = requires{std::is_arithmetic_v<T...>;};
  
  template<typename T>
  concept IsMatrix = requires(T a){a.RowSize(); a.ColumnSize(); a.TotalSize(); a[0]; a[0,0]; };
}