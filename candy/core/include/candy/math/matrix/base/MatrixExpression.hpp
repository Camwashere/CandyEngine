#pragma once
#include <cstdint>
#include <condition_variable>
namespace Candy::Math
{
  template <typename COMPONENT_TYPE, typename MATRIX>
  class MatrixExpression
  {
  public:
    static constexpr bool isLeaf=false;
    COMPONENT_TYPE operator[](std::size_t index)const{return static_cast<const MATRIX&>(*this)[index];}
    COMPONENT_TYPE operator[](std::size_t row, std::size_t column)const{return static_cast<const MATRIX&>(*this)[row, column];}
    [[nodiscard]] std::size_t RowSize() const{return static_cast<const MATRIX&>(*this).RowSize();}
    [[nodiscard]] std::size_t ColumnSize()const{return static_cast<const MATRIX&>(*this).ColumnSize();}
    
    
  };
  
  template<typename COMPONENT_TYPE, typename MAT1, typename MAT2>
  class MatrixSum : public MatrixExpression<COMPONENT_TYPE, MatrixSum<COMPONENT_TYPE, MAT1, MAT2>>
  {
    std::conditional_t<MAT1::isLeaf, const MAT1&, const MAT1> _u;
    std::conditional_t<MAT2::isLeaf, const MAT2&, const MAT2> _v;
  
  public:
    static constexpr bool isLeaf=false;
    MatrixSum(const MAT1& u, const MAT2& v) : _u(u), _v(v){
      //assert(u.Size() == v.Size());
    }
    COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] + _v[index];}
    COMPONENT_TYPE operator[](std::size_t row, std::size_t column) const {return _u[row, column] + _v[row, column];}
    [[nodiscard]] std::size_t RowSize() const{return _v.RowSize();}
    [[nodiscard]] std::size_t ColumnSize()const{return _v.ColumnSize();}
  };
  
  
  template<typename COMPONENT_TYPE, typename MAT1, typename MAT2>
  class MatrixDif : public MatrixExpression<COMPONENT_TYPE, MatrixDif<COMPONENT_TYPE, MAT1, MAT2>>
  {
    std::conditional_t<MAT1::isLeaf, const MAT1&, const MAT1> _u;
    std::conditional_t<MAT2::isLeaf, const MAT2&, const MAT2> _v;
  
  public:
    static constexpr bool isLeaf=false;
    MatrixDif(const MAT1& u, const MAT2& v) : _u(u), _v(v){
      //assert(u.Size() == v.Size());
    }
    COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] - _v[index];}
    COMPONENT_TYPE operator[](std::size_t row, std::size_t column) const {return _u[row, column] - _v[row, column];}
    [[nodiscard]] std::size_t RowSize() const{return _v.RowSize();}
    [[nodiscard]] std::size_t ColumnSize()const{return _v.ColumnSize();}
  };
  
  template<typename COMPONENT_TYPE, typename MAT>
  class ScalarMatrixMultiply : public MatrixExpression<COMPONENT_TYPE, ScalarMatrixMultiply<COMPONENT_TYPE, MAT>>{
    std::conditional_t<MAT::isLeaf, const MAT&, const MAT> _u;
    const COMPONENT_TYPE _v;
  public:
    static constexpr bool isLeaf=false;
    ScalarMatrixMultiply(const MAT& u, const COMPONENT_TYPE& v) : _u(u), _v(v){}
    ScalarMatrixMultiply(const COMPONENT_TYPE& v, const MAT& u) : _u(u), _v(v){}
    COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] * _v;}
    COMPONENT_TYPE operator[](std::size_t row, std::size_t column) const {return _u[row, column] * _v;}
    [[nodiscard]] std::size_t RowSize() const{return _u.RowSize();}
    [[nodiscard]] std::size_t ColumnSize()const{return _u.ColumnSize();}
  };
  
  
  
  
  
}

// Global Operator Implementations
template <typename COMPONENT_TYPE, typename MAT1, typename MAT2>
Candy::Math::MatrixSum<COMPONENT_TYPE, MAT1, MAT2> operator+(Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT1> const& u, Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT2> const& v) {
  return Candy::Math::MatrixSum<COMPONENT_TYPE, MAT1, MAT2>(*static_cast<const MAT1 *>(&u), *static_cast<const MAT2 *>(&v));
}

template <typename COMPONENT_TYPE, typename MAT1, typename MAT2>
Candy::Math::MatrixDif<COMPONENT_TYPE, MAT1, MAT2> operator-(Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT1> const& u, Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT2> const& v) {
  return Candy::Math::MatrixDif<COMPONENT_TYPE, MAT1, MAT2>(*static_cast<const MAT1 *>(&u), *static_cast<const MAT2 *>(&v));
}

template <typename COMPONENT_TYPE, typename MAT1, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarMatrixMultiply<COMPONENT_TYPE, MAT1> operator*(const Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT1>& vec, const SCALAR_TYPE& scalar) {
  return Candy::Math::ScalarMatrixMultiply<COMPONENT_TYPE, MAT1>(*static_cast<const MAT1 *>(&vec), scalar);
}
template <typename COMPONENT_TYPE, typename MAT1, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarMatrixMultiply<COMPONENT_TYPE, MAT1> operator*(const SCALAR_TYPE& scalar, const Candy::Math::MatrixExpression<COMPONENT_TYPE, MAT1>& vec) {
  return Candy::Math::ScalarMatrixMultiply<COMPONENT_TYPE, MAT1>(scalar, *static_cast<const MAT1 *>(&vec));
}

