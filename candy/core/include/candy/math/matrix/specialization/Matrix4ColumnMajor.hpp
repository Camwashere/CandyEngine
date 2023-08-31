#pragma once
#include "../base/MatrixBase.hpp"
#include "../base/MatrixExpression.hpp"
#include <array>
#include "xmmintrin.h"
#include <cstring>
#include <iomanip>
namespace Candy::Math
{
  template<typename T>
  struct QuaternionBase;
  
  template<>
  class AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> : public MatrixIndexData<4, 4>, public LayoutPolicyTopToBottom, public MatrixExpression<float, AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>>
  {
  
  private:
    static constexpr index_t AccessIndex(index_t x, index_t y){return LayoutPolicyTopToBottom::AccessIndex<index_t, 4, 4>(x, y);}
  public:
    using MatrixIndexData<4, 4>::COLUMNS;
    using MatrixIndexData<4, 4>::ROWS;
    using MatrixIndexData<4, 4>::TOTAL_SIZE;
    using MatrixIndexData<4, 4>::IS_SQUARE;
    using MatrixIndexData<4, 4>::isLeaf;
    
  public:
    static const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> IDENTITY;
  
  
  
  
  
  private:
    union
    {
      alignas(16) std::array<float, 16> data{};
      alignas(16) std::array<Vector4, 4> columns;
      alignas(16) __m128 m128[4];
      
    };
  
  
  public:
    AbstractMatrixBase();
    explicit AbstractMatrixBase(float diagonal);
    explicit AbstractMatrixBase(const VectorBase<float, ROWS>& diagonal);
    AbstractMatrixBase(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other);
    
    AbstractMatrixBase(VectorBase<float, ROWS> col0, VectorBase<float, ROWS> col1, VectorBase<float, ROWS> col2, VectorBase<float, ROWS> col3);
    
    
    
    AbstractMatrixBase(std::initializer_list<float> elements);
    
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
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Diagonal(float diagonal);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Diagonal(const VectorBase<float, 4>& value);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Diagonal(float v0, float v1, float v2, float v3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Inverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix);
    //static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> FastInverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> CreateFromRows(const VectorBase<float, 4>& r0, const VectorBase<float, 4>& r1, const VectorBase<float, 4>& r2, const VectorBase<float, 4>& r3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> CreateFromColumns(const VectorBase<float, 4>& c0, const VectorBase<float, 4>& c1, const VectorBase<float, 4>& c2, const VectorBase<float, 4>& c3);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Orthographic(float left, float right, float bottom, float top, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Perspective(float fov, float aspectRatio, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> LookAt(const VectorBase<float, 3>& eye, const VectorBase<float, 3>& target, const VectorBase<float, 3>& up);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Translate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix, const VectorBase<float, 3>& translation);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix, float angle, const VectorBase<float, 3>& axis);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix, const QuaternionBase<float>& quaternion);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Scale(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix, const VectorBase<float, 3>& scale);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Frustum(float left, float right, float bottom, float top, float near, float far);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> InfinitePerspective(float fov, float aspectRatio, float near);
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> Transpose(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix);
    static void DecomposeTransform(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix, Vector3& translation, Vector3& rotation, Vector3& scale);
    
    // Create a picking region for selection. It takes in the parameters center, delta and viewport and returns a pick matrix.
    static AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> PickMatrix(const VectorBase<float, 2>& center, const VectorBase<float, 2>& delta, const VectorBase<float, 4>& viewport);
    
    // Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
    static VectorBase<float, 3> Project(const VectorBase<float, 3>& obj, const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& projection, const VectorBase<float, 4>& viewport);
    
    // Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
    static VectorBase<float, 3> UnProject(const VectorBase<float, 3>& windowCoords, const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& projection, const VectorBase<float, 4>& viewport);
    
    static float Determinant(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix);
  
  
  
  public:
    float& operator[](index_t index);
    float& operator[](index_t row, index_t column);
    float operator[](index_t index)const;
    float operator[](index_t row, index_t column)const;
    
    bool operator==(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const;
    bool operator!=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const;
    VectorBase<float, 3> operator*(const VectorBase<float, 3>& vec)const;
    VectorBase<float, 4> operator*(const VectorBase<float, 4>& vec)const;
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> operator*(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const;
    
    void operator+=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other);
    void operator-=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other);
    void operator*=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other);
  
  
  public:
    VectorBase<float, ROWS>& GetColumn(index_t index);
    [[nodiscard]] const VectorBase<float, ROWS>& GetColumn(index_t index)const;
    VectorBase<float, COLUMNS> GetRow(index_t index)const;
    VectorBase<float, 3> GetTranslation()const;
    VectorBase<float, 3> GetScale()const;
    VectorBase<float, 3> GetRotation()const;
    const float* ValuePtr()const;
    float* ValuePtr();
  
  
  public:
    [[nodiscard]] constexpr index_t GetColumnCount()const{return COLUMNS;}
    [[nodiscard]] constexpr index_t GetRowCount()const{return ROWS;}
    [[nodiscard]] constexpr index_t GetTotalSize()const{return TOTAL_SIZE;}
    [[nodiscard]] constexpr bool IsSquare()const{return IS_SQUARE;}
    
    
  };
  
  
}

template<>
struct fmt::formatter<Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyTopToBottom>> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyTopToBottom>& matrix, FormatContext& ctx) {
    return format_to(ctx.out(), "{0}\n{1}\n{2}\n{3}",
                     Candy::Math::Vector4(matrix[0], matrix[4], matrix[8], matrix[12]),
                     Candy::Math::Vector4(matrix[1], matrix[5], matrix[9], matrix[13]),
                     Candy::Math::Vector4(matrix[2], matrix[6], matrix[10], matrix[14]),
                     Candy::Math::Vector4(matrix[3], matrix[7], matrix[11], matrix[15]));
  }
};

std::ostream &operator<<(std::ostream &ostream, const Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyTopToBottom> &mat);
