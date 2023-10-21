#include <candy/math/matrix/specialization/Matrix3.hpp>
#include "CandyPch.hpp"
namespace Candy::Math
{
  static constexpr int AccessIndex(int row, int column){return row+column*3;}
  const Matrix3 Matrix3::IDENTITY = Diagonal(1.0f);
  Matrix3::Matrix3()
  {
    data.fill(0.0f);
  }
  
  Matrix3::Matrix3(float diagonal)
  {
    data.fill(0.0f);
    data[0] = diagonal;
    data[4] = diagonal;
    data[8] = diagonal;
  }
  
  Matrix3::Matrix3(const Vector3& diagonal)
  {
    data.fill(0.0f);
    data[0] = diagonal[0];
    data[4] = diagonal[1];
    data[8] = diagonal[2];
  }
  
  Matrix3::Matrix3(const Matrix3& other) : data(other.data)
  {
    
  }
  
  Matrix3::Matrix3(std::initializer_list<float> elements)
  {
    int count=0;
    for (float element : elements)
    {
      data[count]=element;
      count++;
    }
  }
  
  Matrix3::Matrix3(Vector3 column0, Vector3 column1, Vector3 column2) : columns{column0, column1, column2}
  {
    
  }
  
  Matrix3 Matrix3::Diagonal(float diagonal)
  {
    return Matrix3(diagonal);
  }
  Matrix3 Matrix3::Diagonal(const Vector3& value)
  {
    return Matrix3(value);
  }
  Matrix3 Matrix3::Diagonal(float v0, float v1, float v2)
  {
    return Matrix3(Vector3(v0, v1, v2));
  }
  Matrix3 Matrix3::Inverse(const Matrix3 &matrix)
  {
    Matrix3 result;
    
    result.data[0] = matrix.data[4] * matrix.data[8] - matrix.data[5] * matrix.data[7];
    result.data[1] = matrix.data[2] * matrix.data[7] - matrix.data[1] * matrix.data[8];
    result.data[2] = matrix.data[1] * matrix.data[5] - matrix.data[2] * matrix.data[4];
    
    result.data[3] = matrix.data[5] * matrix.data[6] - matrix.data[3] * matrix.data[8];
    result.data[4] = matrix.data[0] * matrix.data[8] - matrix.data[2] * matrix.data[6];
    result.data[5] = matrix.data[2] * matrix.data[3] - matrix.data[0] * matrix.data[5];
    
    result.data[6] = matrix.data[3] * matrix.data[7] - matrix.data[4] * matrix.data[6];
    result.data[7] = matrix.data[1] * matrix.data[6] - matrix.data[0] * matrix.data[7];
    result.data[8] = matrix.data[0] * matrix.data[4] - matrix.data[1] * matrix.data[3];
    
    float det = matrix.data[0] * result.data[0] + matrix.data[1] * result.data[3] + matrix.data[2] * result.data[6];
    
    // check if determinant is near zero (within epsilon)
    CANDY_CORE_ASSERT(Math::Abs(det) < Math::Epsilon<float>(), "Matrix3 is not invertible");
    
    
    det = 1.0f / det;
    
    for (int i = 0; i < 9; i++)
      result.data[i] *= det;
    
    return result;
  }
  
  
  Matrix3 Matrix3::CreateFromRows(const Vector3& r0, const Vector3& r1, const Vector3& r2)
  {
    CANDY_PROFILE_FUNCTION();
    return {Vector4(r0.x, r1.x, r2.x), Vector4(r0.y, r1.y, r2.y), Vector4(r0.z, r1.z, r2.z)};
  }
  
  Matrix3 Matrix3::CreateFromColumns(const Vector3& c0, const Vector3& c1, const Vector3& c2)
  {
    CANDY_PROFILE_FUNCTION();
    return {c0, c1, c2};
  }
  Matrix3 Matrix3::Orthographic(float left, float right, float bottom, float top)
  {
    Matrix3 ortho = Matrix3::IDENTITY;
    
    ortho[0][0] = 2.0f / (right - left);
    ortho[1][1] = 2.0f / (top - bottom);
    ortho[2][0] = -(right + left) / (right - left);
    ortho[2][1] = -(top + bottom) / (top - bottom);
    
    return ortho;
  }
  
  Matrix3 Matrix3::Translate(const Matrix3& matrix, const Vector2& translation)
  {
    Matrix3 result = matrix;
    result.data[0] = 1;
    result.data[4] = 1;
    result.data[6] = translation.x;
    result.data[7] = translation.y;
    result.data[8] = 1;
    
    return result;
  }
  Matrix3 Matrix3::Rotate(const Matrix3& matrix, float rotation)
  {
    Matrix3 result = matrix;
    
    float cosTheta = Math::Cos(rotation);
    float sinTheta = Math::Sin(rotation);
    
    result.data[0] = cosTheta;
    result.data[1] = -sinTheta;
    result.data[3] = sinTheta;
    result.data[4] = cosTheta;
    
    return result;
  }
  Matrix3 Matrix3::Scale(const Matrix3& matrix, const Vector2& scale)
  {
    Matrix3 result = matrix;
    
    result.data[0] = scale.x;
    result.data[4] = scale.y;
    
    return result;
  }
  
  
  Matrix3 Matrix3::Transpose(const Matrix3 &matrix)
  {
    Matrix3 result = matrix;
    result.data[1] = matrix.data[3];
    result.data[2] = matrix.data[6];
    result.data[3] = matrix.data[1];
    result.data[5] = matrix.data[7];
    result.data[6] = matrix.data[2];
    result.data[7] = matrix.data[5];
    return result;
  }
  
  bool Matrix3::DecomposeTransform(const Matrix3 &m, Vector2 &translation, float &rotation, Vector2 &scale)
  {
    Matrix3 localMatrix = m;
    // Check if the matrix is not usable
    if (EpsilonEqual(localMatrix.data[8], 0.0f, Epsilon<float>()))
    {
      CANDY_CORE_ERROR("Last element in matrix is 0! Cannot decompose.");
      return false;
    }
    
    // Normalize matrix
    float factor = localMatrix.data[8];
    localMatrix.data[0] /= factor;
    localMatrix.data[1] /= factor;
    localMatrix.data[2] /= factor;
    localMatrix.data[3] /= factor;
    localMatrix.data[4] /= factor;
    localMatrix.data[5] /= factor;
    localMatrix.data[6] /= factor;
    localMatrix.data[7] /= factor;
    localMatrix.data[8] = 1.0f; // it will be 1 after division by itself
    
    // Extract translation
    translation = Vector2(localMatrix.data[6], localMatrix.data[7]);
    localMatrix.data[6] = localMatrix.data[7] = 0.0f;
    
    // Compute scaling factors
    scale.x = Sqrt(localMatrix.data[0] * localMatrix.data[0] + localMatrix.data[3] * localMatrix.data[3]); // Assuming the matrix is in the orthogonal basis
    scale.y = Sqrt(localMatrix.data[1] * localMatrix.data[1] + localMatrix.data[4] * localMatrix.data[4]);
    
    if (scale.x == 0 || scale.y == 0)
    {
      CANDY_CORE_ERROR("One of the scale factors is 0! Cannot decompose.");
      return false;
    }
    
    localMatrix.data[0] /= scale.x; // Remove scaling from matrix
    localMatrix.data[3] /= scale.x;
    
    localMatrix.data[1] /= scale.y;
    localMatrix.data[4] /= scale.y;
    
    rotation = Atan2(localMatrix.data[1], localMatrix.data[0]); // Compute rotation (assuming orthogonal matrix)
    return true;
  }
  
  float Matrix3::Determinant(const Matrix3& matrix)
  {
    float det = matrix.data[0]*(matrix.data[4]*matrix.data[8] - matrix.data[5]*matrix.data[7]) -
          matrix.data[1]*(matrix.data[3]*matrix.data[8] - matrix.data[5]*matrix.data[6]) +
          matrix.data[2]*(matrix.data[3]*matrix.data[7] - matrix.data[4]*matrix.data[6]);
    
    return det;
  }
  
  
  Vector3& Matrix3::operator[](int index)
  {
    CANDY_CORE_ASSERT(index<3, "Matrix3 index is out of range!");
    return columns[index];
  }
  
  Vector3 Matrix3::operator[](int index) const
  {
    CANDY_CORE_ASSERT(index<3, "Matrix3 index is out of range!");
    return columns[index];
  }
  
  float& Matrix3::operator[](int row, int column)
  {
    CANDY_CORE_ASSERT(row < 3 && column < 3, "Matrix3 index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  float Matrix3::operator[](int row, int column) const
  {
    CANDY_CORE_ASSERT(row < 3 && column < 3, "Matrix3 index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  bool Matrix3::operator==(const Matrix3& other) const
  {
    for (int i = 0; i < 9; i++)
      if (data[i] != other.data[i])
        return false;
    return true;
  }
  
  bool Matrix3::operator!=(const Matrix3& other) const
  {
    return !((*this)==other);
  }
  
  Vector2 Matrix3::operator*(const Vector2& vec) const
  {
    Vector2 result{};
    for (int i=0; i<2; i++)
    {
      result[i] = data[i] * vec.x + data[i+3] * vec.y + data[i+6];
    }
    return result;
  }
  
  Vector3 Matrix3::operator*(const Vector3& vec) const
  {
    Vector3 result{};
    for (int i=0; i<3; i++)
    {
      result[i] = data[i] * vec.x + data[i+3] * vec.y + data[i+6] * vec.z;
    }
    return result;
  }
  
  Matrix3 Matrix3::operator*(const Matrix3& other) const
  {
    Matrix3 result;
    result.data[0] = data[0] * other.data[0] + data[3] * other.data[1] + data[6] * other.data[2];
    result.data[1] = data[1] * other.data[0] + data[4] * other.data[1] + data[7] * other.data[2];
    result.data[2] = data[2] * other.data[0] + data[5] * other.data[1] + data[8] * other.data[2];
    result.data[3] = data[0] * other.data[3] + data[3] * other.data[4] + data[6] * other.data[5];
    result.data[4] = data[1] * other.data[3] + data[4] * other.data[4] + data[7] * other.data[5];
    result.data[5] = data[2] * other.data[3] + data[5] * other.data[4] + data[8] * other.data[5];
    result.data[6] = data[0] * other.data[6] + data[3] * other.data[7] + data[6] * other.data[8];
    result.data[7] = data[1] * other.data[6] + data[4] * other.data[7] + data[7] * other.data[8];
    result.data[8] = data[2] * other.data[6] + data[5] * other.data[7] + data[8] * other.data[8];
    return result;
  }
  
  void Matrix3::operator+=(const Matrix3& other)
  {
    for(int i = 0; i < 9; i++)
      data[i] += other.data[i];
  }
  
  void Matrix3::operator-=(const Matrix3& other)
  {
    for(int i = 0; i < 9; i++)
      data[i] -= other.data[i];
  }
  
  void Matrix3::operator*=(const Matrix3& other)
  {
    *this = *this * other;
  }
  
  float& Matrix3::Entry(int index)
  {
    CANDY_CORE_ASSERT(index < 9, "Matrix3 entry index is out of range!");
    return data[index];
  }
  
  float Matrix3::Entry(int index) const
  {
    CANDY_CORE_ASSERT(index < 9, "Matrix3 entry index is out of range!");
    return data[index];
  }
  
  float& Matrix3::Entry(int row, int column)
  {
    CANDY_CORE_ASSERT(row<3 && column<3, "Matrix3 entry index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  float Matrix3::Entry(int row, int column) const
  {
    CANDY_CORE_ASSERT(row<3 && column<3, "Matrix3 entry index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  Vector3& Matrix3::GetColumn(int index)
  {
    CANDY_CORE_ASSERT(index < 3, "Matrix3 column index is out of range!");
    return columns[index];
  }
  
  const Vector3& Matrix3::GetColumn(int index) const
  {
    CANDY_CORE_ASSERT(index < 3, "Matrix3 column index is out of range!");
    return columns[index];
  }
  
  Vector3 Matrix3::GetRow(int index) const
  {
    CANDY_CORE_ASSERT(index < 3, "Matrix3 row index is out of range!");
    return Vector3(data[index], data[index+3], data[index+6]);
  }
  
  Vector2 Matrix3::GetTranslation() const
  {
    return Vector2(data[6], data[7]);
  }
  
  Vector2 Matrix3::GetScale() const
  {
    float sx = Sqrt(data[0] * data[0] + data[3] * data[3]);
    float sy = Sqrt(data[1] * data[1] + data[4] * data[4]);
    return Vector2(sx, sy);
  }
  
  float Matrix3::GetRotation() const
  {
    // Assuming the matrix is orthogonal, the element at the first row and first column gives the cos(θ) of rotation.
    return Acos(data[0]);
  }
  
  const float* Matrix3::Data() const
  {
    return data.data();
  }
  
  float* Matrix3::Data()
  {
    return data.data();
  }
}
