#pragma once
#include "../base/MatrixBase.hpp"
#include "../base/MatrixExpression.hpp"
#include "xmmintrin.h"
#include <cstring>
#include <iomanip>
namespace Candy::Math
{
  
  
  template<>
  class AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> : public MatrixIndexData<3, 3>, public LayoutPolicyLeftToRight, public MatrixExpression<float, AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>>
  {
  
  private:
    static constexpr index_t AccessIndex(index_t x, index_t y){return LayoutPolicyLeftToRight::AccessIndex<index_t, 3, 3>(x, y);}
  public:
    using MatrixIndexData<3, 3>::COLUMNS;
    using MatrixIndexData<3, 3>::ROWS;
    using MatrixIndexData<3, 3>::TOTAL_SIZE;
    using MatrixIndexData<3, 3>::IS_SQUARE;
    using MatrixIndexData<3, 3>::isLeaf;
  
  
  
  
  
  private:
    union
    {
      alignas(16) float data[TOTAL_SIZE]{};
      alignas(16) VectorBase<float, COLUMNS> rows[ROWS];
      alignas(16) __m128 m128[3];
      
    };
  
  
  public:
    AbstractMatrixBase();
    explicit AbstractMatrixBase(float diagonal);
    explicit AbstractMatrixBase(const VectorBase<float, COLUMNS>& diagonal);
    AbstractMatrixBase(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other);
    
    AbstractMatrixBase(VectorBase<float, COLUMNS> row0, VectorBase<float, COLUMNS> row1, VectorBase<float, COLUMNS> row2);
    
    
    AbstractMatrixBase(float r0c0, float r0c1, float r0c2,
                       float r1c0, float r1c1, float r1c2,
                       float r2c0, float r2c1, float r2c2);
    
    
    template<typename U, typename E>
    requires(std::is_arithmetic_v<U>)
    AbstractMatrixBase(const MatrixExpression<U, E> &expr)
    {
      for (index_t i=0; i<TOTAL_SIZE; ++i)
      {
        data[i] = expr[i];
      }
      
    }
  
  public:
    static AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> Diagonal(float diagonal);
    static AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> Diagonal(const VectorBase<float, 3>& value);
    static AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> Diagonal(float v0, float v1, float v2);
    static AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> CreateFromRows(const VectorBase<float, 3>& r0, const VectorBase<float, 3>& r1, const VectorBase<float, 3>& r2);
    static AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> CreateFromColumns(const VectorBase<float, 3>& c0, const VectorBase<float, 3>& c1, const VectorBase<float, 3>& c2);

    

  
  
  
  public:
    float& operator[](index_t index);
    float& operator[](index_t row, index_t column);
    float operator[](index_t index)const;
    float operator[](index_t row, index_t column)const;
    
    bool operator==(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const;
    bool operator!=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const;
    
    VectorBase<float, 3> operator*(const VectorBase<float, 3>& vec)const;
    AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> operator*(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const;
    
    void operator+=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other);
    void operator-=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other);
    void operator*=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other);
  
  
  public:
    VectorBase<float, COLUMNS>& Row(index_t index)&;
    [[nodiscard]] const VectorBase<float, COLUMNS>& Row(index_t index)const&;
  
  
  public:
    [[nodiscard]] constexpr index_t GetColumnCount()const{return COLUMNS;}
    [[nodiscard]] constexpr index_t GetRowCount()const{return ROWS;}
    [[nodiscard]] constexpr index_t GetTotalSize()const{return TOTAL_SIZE;}
    [[nodiscard]] constexpr bool IsSquare()const{return IS_SQUARE;}
    
    
  };
  
  
}



std::ostream &operator<<(std::ostream &ostream, const Candy::Math::AbstractMatrixBase<float, 3, 3, Candy::Math::LayoutPolicyLeftToRight> &mat);
