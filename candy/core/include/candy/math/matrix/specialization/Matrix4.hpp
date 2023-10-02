#pragma once
#include <cstdint>
#include <array>
#include <candy/math/Vector.hpp>
#include "../base/MatrixExpression.hpp"
#include "xmmintrin.h"
namespace Candy::Math
{
  struct Quaternion;
  
  class Matrix4 : public MatrixExpression<float, Matrix4>
  {
  private:
    static constexpr int TOTAL_SIZE = 16;
    static constexpr int ROWS = 4;
    static constexpr int COLUMNS = 4;
  
  public:
    static const Matrix4 IDENTITY;
    
  private:
    union
    {
      alignas(16) std::array<float, 16> data{};
      alignas(16) std::array<Vector4, 4> columns;
      alignas(16) __m128 m128[4];
    };
    
  
    
    
  public:
    Matrix4();
    explicit Matrix4(float diagonal);
    explicit Matrix4(const Vector4& diagonal);
    Matrix4(const Matrix4& other);
    
    Matrix4(Vector4 col0, Vector4 col1, Vector4 col2, Vector4 col3);
    
    Matrix4(__m128 m0, __m128 m1, __m128 m2, __m128 m3);
    
    
    
    Matrix4(std::initializer_list<float> elements);
    
    template<typename U, typename E>
    requires(std::is_arithmetic_v<U>)
    Matrix4(const MatrixExpression<U, E> &expr)
    {
      for (int i=0; i<TOTAL_SIZE; ++i)
      {
        data[i] = expr[i];
      }
      
    }
  
  public:
    static Matrix4 Random(float min=0.0f, float max=1.0f);
    static Matrix4 Diagonal(float diagonal);
    static Matrix4 Diagonal(const Vector4& value);
    static Matrix4 Diagonal(float v0, float v1, float v2, float v3);
    static Matrix4 Inverse(const Matrix4 &matrix);
    static Matrix4 FastInverse(const Matrix4& matrix);
    static Matrix4 CreateFromRows(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3);
    static Matrix4 CreateFromColumns(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3);
    static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
    static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);
    static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
    static Matrix4 Translate(const Matrix4& matrix, const Vector3& translation);
    static Matrix4 Rotate(const Matrix4& matrix, float angle, const Vector3& axis);
    static Matrix4 Rotate(const Matrix4& matrix, const Quaternion& quaternion);
    static Matrix4 Scale(const Matrix4& matrix, const Vector3& scale);
    
    
    /**
    * Create a perspective matrix typically used when setting up the camera's projection transformation.
    * @param left The left edge of the viewing frustum.
    * @param right The right edge of the viewing frustum.
    * @param bottom The bottom edge of the viewing frustum.
    * @param top The top edge of the viewing frustum.
    * @param near The distance to the near clipping plane.
    * @param far The distance to the far clipping plane.
    * @returns A perspective matrix.*/
    static Matrix4 Frustum(float left, float right, float bottom, float top, float near, float far);
    
    
    /** When you don't know the far plane or want to set it to infinity.
     * @param fov Field of view (In radians)
     * @param aspectRatio The aspect ratio of the view port.
     * @param near The distance to the near clipping plane.
     * @return The perspective matrix (Usually the camera's projection transformation).*/
    static Matrix4 InfinitePerspective(float fov, float aspectRatio, float near);
    static Matrix4 Transpose(const Matrix4 &matrix);
    static bool DecomposeTransform(const Matrix4 &matrix, Vector3& translation, Quaternion& rotation, Vector3& scale);
    
    
     
    /** The pick matrix is used in selection/picking computations to create a projection matrix that magnifies a
     * small region of the screen (defined by center and delta) to the entire viewport.
     * This is useful in picking scenarios where you want to select scene objects located around a certain point.
     * @brief Create a picking region for selection.
     * @param center The center point of the picking region in the viewport.
     * @param delta The size (in pixels) of the picking region around the center point.
     * @param viewportPosition The coordinates of the bottom-left corner of the viewport.
     * @param viewportSize The size (width and height in pixels) of the viewport.
     * @return A matrix that defines a projection that scales and translates the picking region to match the viewport.*/
    static Matrix4 PickMatrix(const Vector2& center, const Vector2& delta, const Vector2& viewportPosition, const Vector2& viewportSize);
    
    
    /** Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
     * @brief Maps object coordinates to window coordinates.
     * @param obj The object coordinates to map.
     * @param model The model matrix used for the transformation.
     * @param projection The projection matrix used for the transformation.
     * @param viewport The viewport coordinates and dimensions (x, y, width, height).
     * @return The window coordinates corresponding to the given object coordinates.*/
    static Vector3 Project(const Vector3& obj, const Matrix4& model, const Matrix4& projection, const Vector4& viewport);
    
    
    /** Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
     * @brief Maps window coordinates to object coordinates.
     * @param windowCoords The window coordinates to map.
     * @param model The model matrix used for the transformation.
     * @param projection The projection matrix used for the transformation.
     * @param viewport The viewport coordinates and dimensions (x, y, width, height).
     * @return The object coordinates corresponding to the given window coordinates.*/
    static Vector3 UnProject(const Vector3& windowCoords, const Matrix4& model, const Matrix4& projection, const Vector4& viewport);
    
    static float Determinant(const Matrix4& matrix);
  
  
  
  public:
    /// @returns The column at the specified index.
    Vector4& operator[](int index);
    
    /// @returns The column at the specified index.
    Vector4 operator[](int index)const;
    
    /// @returns The entry stored at the specified row and column.
    float& operator[](int row, int column);
    
    /// @returns The entry stored at the specified row and column.
    float operator[](int row, int column)const;
    
    bool operator==(const Matrix4& other)const;
    bool operator!=(const Matrix4& other)const;
    Vector3 operator*(const Vector3& vec)const;
    Vector4 operator*(const Vector4& vec)const;
    Matrix4 operator*(const Matrix4& other)const;
    
    void operator+=(const Matrix4& other);
    void operator-=(const Matrix4& other);
    void operator*=(const Matrix4& other);
  
  
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
    Vector4& GetColumn(int index);
    
    /// @returns The column at the specified index.
    [[nodiscard]] const Vector4& GetColumn(int index)const;
    
    /// @returns The row at the specified index. @note Can't modify the row. The returned row is a copy.
    [[nodiscard]] Vector4 GetRow(int index)const;
    
    /// @returns The translation part of the matrix.
    [[nodiscard]] Vector3 GetTranslation()const;
    
    /// @returns The scale part of the matrix.
    [[nodiscard]] Vector3 GetScale()const;
    
    /// @returns The rotation part of the matrix.
    [[nodiscard]] Vector3 GetRotation()const;
    
    /// @returns A pointer to the underlying data, laid out as a column major array of 16 floats.
    [[nodiscard]] const float* Data()const;
    
    /// @returns A pointer to the underlying data, laid out as a column major array of 16 floats.
    float* Data();
    
    
  };
}

template<>
struct fmt::formatter<Candy::Math::Matrix4> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::Matrix4& matrix, FormatContext& ctx) {
    return format_to(ctx.out(), "{0}\n{1}\n{2}\n{3}",
                     Candy::Math::Vector4(matrix.Entry(0), matrix.Entry(4), matrix.Entry(8), matrix.Entry(12)),
                     Candy::Math::Vector4(matrix.Entry(1), matrix.Entry(5), matrix.Entry(9), matrix.Entry(13)),
                     Candy::Math::Vector4(matrix.Entry(2), matrix.Entry(6), matrix.Entry(10), matrix.Entry(14)),
                     Candy::Math::Vector4(matrix.Entry(3), matrix.Entry(7), matrix.Entry(11), matrix.Entry(15)));
  }
};

std::ostream &operator<<(std::ostream &ostream, const Candy::Math::Matrix4 &mat);