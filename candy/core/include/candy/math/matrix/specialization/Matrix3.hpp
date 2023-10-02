#pragma once
#include <cstdint>
#include <array>
#include <candy/math/Vector.hpp>
#include "../base/MatrixExpression.hpp"
#include "xmmintrin.h"
namespace Candy::Math
{
 
  
  class Matrix3 : public MatrixExpression<float, Matrix3>
  {
  private:
    static constexpr int TOTAL_SIZE = 9;
    static constexpr int ROWS = 3;
    static constexpr int COLUMNS = 3;
  
  public:
    static const Matrix3 IDENTITY;
  
  private:
    union
    {
      std::array<float, TOTAL_SIZE> data{};
      std::array<Vector3, 3> columns;
    };
  
  
  
  
  public:
    Matrix3();
    explicit Matrix3(float diagonal);
    explicit Matrix3(const Vector3& diagonal);
    Matrix3(const Matrix3& other);
    Matrix3(Vector3 col0, Vector3 col1, Vector3 col2);
    Matrix3(std::initializer_list<float> elements);
    
    template<typename U, typename E>
    requires(std::is_arithmetic_v<U>)
    Matrix3(const MatrixExpression<U, E> &expr)
    {
      for (int i=0; i<TOTAL_SIZE; ++i)
      {
        data[i] = expr[i];
      }
      
    }
  
  public:
    static Matrix3 Diagonal(float diagonal);
    static Matrix3 Diagonal(const Vector3& value);
    static Matrix3 Diagonal(float v0, float v1, float v2);
    static Matrix3 Inverse(const Matrix3 &matrix);
    static Matrix3 CreateFromRows(const Vector3& r0, const Vector3& r1, const Vector3& r2);
    static Matrix3 CreateFromColumns(const Vector3& c0, const Vector3& c1, const Vector3& c2);
    static Matrix3 Orthographic(float left, float right, float bottom, float top);
    static Matrix3 Translate(const Matrix3& matrix, const Vector2& translation);
    static Matrix3 Rotate(const Matrix3& matrix, float rotation);
    static Matrix3 Scale(const Matrix3& matrix, const Vector2& scale);
    static Matrix3 Transpose(const Matrix3 &matrix);
    static bool DecomposeTransform(const Matrix3 &matrix, Vector2& translation, float& rotation, Vector2& scale);
    static float Determinant(const Matrix3& matrix);
  
  
  
  public:
    /// @returns The column at the specified index.
    Vector3& operator[](int index);
    
    /// @returns The column at the specified index.
    Vector3 operator[](int index)const;
    
    /// @returns The entry stored at the specified row and column.
    float& operator[](int row, int column);
    
    /// @returns The entry stored at the specified row and column.
    float operator[](int row, int column)const;
    
    bool operator==(const Matrix3& other)const;
    bool operator!=(const Matrix3& other)const;
    Vector2 operator*(const Vector2& vec)const;
    Vector3 operator*(const Vector3& vec)const;
    Matrix3 operator*(const Matrix3& other)const;
    
    void operator+=(const Matrix3& other);
    void operator-=(const Matrix3& other);
    void operator*=(const Matrix3& other);
  
  
  public:
    /// @returns The entry stored at the specified index. @note The internal array is column major.
    float& Entry(int index);
    
    /// @returns The entry stored at the specified index. @note The internal array is column major.
    [[nodiscard]] float Entry(int index)const;
    
    /// @returns The entry stored at the specified row and column.
    float& Entry(int row, int column);
    /// @returns The entry stored at the specified row and column.
    [[nodiscard]] float Entry(int row, int column)const;
    
    /// @returns The column at the specified index.
    Vector3& GetColumn(int index);
    
    /// @returns The column at the specified index.
    [[nodiscard]] const Vector3& GetColumn(int index)const;
    
    /// @returns The row at the specified index. @note Can't modify the row. The returned row is a copy.
    [[nodiscard]] Vector3 GetRow(int index)const;
    
    /// @returns The translation part of the matrix.
    [[nodiscard]] Vector2 GetTranslation()const;
    
    /// @returns The scale part of the matrix.
    [[nodiscard]] Vector2 GetScale()const;
    
    /// @returns The rotation part of the matrix.
    [[nodiscard]] float GetRotation()const;
    
    /// @returns A pointer to the underlying data, laid out as a column major array of 9 floats.
    [[nodiscard]] const float* Data()const;
    
    /// @returns A pointer to the underlying data, laid out as a column major array of 9 floats.
    float* Data();
    
    
  };
}

template<>
struct fmt::formatter<Candy::Math::Matrix3> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::Matrix3& matrix, FormatContext& ctx) {
    return format_to(ctx.out(), "{0}\n{1}\n{2}",
                     Candy::Math::Vector3(matrix.Entry(0), matrix.Entry(3), matrix.Entry(6)),
                     Candy::Math::Vector3(matrix.Entry(1), matrix.Entry(4), matrix.Entry(7)),
                     Candy::Math::Vector3(matrix.Entry(2), matrix.Entry(5), matrix.Entry(8)));
  }
};

std::ostream &operator<<(std::ostream &ostream, const Candy::Math::Matrix3 &mat);