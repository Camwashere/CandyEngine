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
  
  template<typename... T>
  concept Integral = requires{std::is_integral_v<T...>;};
  
  template<typename... T>
  concept Numeric = requires{std::is_arithmetic_v<T...>;};
  
  template<typename T>
  concept IsPrimitive = requires{std::is_convertible_v<T, float> || std::is_convertible_v<T, int> || std::is_convertible_v<T, unsigned int> || std::is_convertible_v<T, bool> || std::is_convertible_v<T, char>;};
  
  template<typename T>
  concept IsMatrix = requires(T a)
  {
    { a.RowSize() } -> std::convertible_to<size_t>;
    { a.ColumnSize() } -> std::convertible_to<size_t>;
    { a.TotalSize() } -> std::convertible_to<size_t>;
    {a[0]};
    {a[0,0]};
  };
  
  template<typename T>
  concept IsVector = requires(T a)
  {
    { a.Size() } -> std::convertible_to<size_t>;
    { a.Dimensions() } -> std::convertible_to<size_t>;
    { a[0] };
    typename T::VALUE_TYPE;
  };
  
  template<typename T>
  concept IsContainer = requires(T a)
  {
    { a.begin() };
    { a.end() };
    { a.size() } -> std::convertible_to<size_t>;
  };
  
  template<typename T>
  concept IsVectorContainer = IsVector<typename T::value_type> && IsContainer<T>;
  
  template<typename T>
  concept IsMatrixContainer = IsMatrix<typename T::value_type> && IsContainer<T>;
  
}