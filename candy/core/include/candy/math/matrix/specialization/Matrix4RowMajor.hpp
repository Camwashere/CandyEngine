#pragma once
#include "../base/MatrixBase.hpp"
#include "../base/MatrixExpression.hpp"
#include "xmmintrin.h"
#include <cstring>
#include <iomanip>
#include <array>
namespace Candy::Math
{
  
  
  template<> 
  class AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> : public MatrixIndexData<4, 4>, public LayoutPolicyLeftToRight, public MatrixExpression<float, AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>>
  {
  
  private:
    static constexpr index_t AccessIndex(index_t x, index_t y){return LayoutPolicyLeftToRight::AccessIndex<index_t, 4, 4>(x, y);}
  public:
    using MatrixIndexData<4, 4>::COLUMNS;
    using MatrixIndexData<4, 4>::ROWS;
    using MatrixIndexData<4, 4>::TOTAL_SIZE;
    using MatrixIndexData<4, 4>::IS_SQUARE;
    using MatrixIndexData<4, 4>::isLeaf;
    
  public:
    static const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> IDENTITY;
    
    
    
  
    
  private:
    union
    {
      alignas(16) std::array<float, 16> data{};
      alignas(16) std::array<VectorBase<float, 4>, 4> rows;
      alignas(16) __m128 m128[4];
      
    };
    
    
  public:
    AbstractMatrixBase();
    explicit AbstractMatrixBase(float diagonal);
    explicit AbstractMatrixBase(const VectorBase<float, COLUMNS>& diagonal);
    AbstractMatrixBase(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other);
    
    AbstractMatrixBase(VectorBase<float, COLUMNS> row0, VectorBase<float, COLUMNS> row1, VectorBase<float, COLUMNS> row2, VectorBase<float, COLUMNS> row3);
    
    
    AbstractMatrixBase(float r0c0, float r0c1, float r0c2, float r0c3,
                float r1c0, float r1c1, float r1c2, float r1c3,
                float r2c0, float r2c1, float r2c2, float r2c3,
                float r3c0, float r3c1, float r3c2, float r3c3);
    
    
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
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Diagonal(float diagonal);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Diagonal(const VectorBase<float, 4>& value);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Diagonal(float v0, float v1, float v2, float v3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Inverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix);
    //static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> FastInverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> CreateFromRows(const VectorBase<float, 4>& r0, const VectorBase<float, 4>& r1, const VectorBase<float, 4>& r2, const VectorBase<float, 4>& r3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> CreateFromColumns(const VectorBase<float, 4>& c0, const VectorBase<float, 4>& c1, const VectorBase<float, 4>& c2, const VectorBase<float, 4>& c3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Orthographic(float left, float right, float bottom, float top, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Perspective(float fov, float aspectRatio, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> LookAt(const VectorBase<float, 3>& eye, const VectorBase<float, 3>& target, const VectorBase<float, 3>& up);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Translate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix, const VectorBase<float, 3>& translation);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix, float angle, const VectorBase<float, 3>& axis);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Scale(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix, const VectorBase<float, 3>& scale);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Frustum(float left, float right, float bottom, float top, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> InfinitePerspective(float fov, float aspectRatio, float near);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> Transpose(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix);
    static std::array<float, 16> ValuePtr(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix);
    
    // Create a picking region for selection. It takes in the parameters center, delta and viewport and returns a pick matrix.
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> PickMatrix(const VectorBase<float, 2>& center, const VectorBase<float, 2>& delta, const VectorBase<float, 4>& viewport);
    
    // Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
    static VectorBase<float, 3> Project(const VectorBase<float, 3>& obj, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& projection, const VectorBase<float, 4>& viewport);
    
    // Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
    static VectorBase<float, 3> UnProject(const VectorBase<float, 3>& windowCoords, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& projection, const VectorBase<float, 4>& viewport);
    
    static float Determinant(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix);
    
    
    
  public:
    float& operator[](index_t index);
    float& operator[](index_t row, index_t column);
    float operator[](index_t index)const;
    float operator[](index_t row, index_t column)const;
    
    bool operator==(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const;
    bool operator!=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const;
    
    VectorBase<float, 4> operator*(const VectorBase<float, 4>& vec)const;
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> operator*(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const;
    
    void operator+=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other);
    void operator-=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other);
    void operator*=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other);
    
    
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



std::ostream &operator<<(std::ostream &ostream, const Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyLeftToRight> &mat);
