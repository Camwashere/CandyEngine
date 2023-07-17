#include <candy/math/matrix/specialization/Matrix4ColumnMajor.hpp>
#include <candy/math/quaternion/QuaternionBase.hpp>
#include <candy/math/MathOps.hpp>

namespace Candy::Math
{
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase()
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase(float diagonal)
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
    data[0] = diagonal;
    data[5] = diagonal;
    data[10] = diagonal;
    data[15] = diagonal;
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase(const VectorBase<float, COLUMNS>& diagonal)
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
    data[0] = diagonal[0];
    data[5] = diagonal[1];
    data[10] = diagonal[2];
    data[15] = diagonal[3];
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other) : data(other.data)
  {
    
    //memcpy(data, other.data, TOTAL_SIZE);
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase(std::initializer_list<float> elements)
  {
    int count=0;
    for (float element : elements)
    {
      data[count]=element;
      count++;
    }
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::AbstractMatrixBase(VectorBase<float, COLUMNS> column0, VectorBase<float, COLUMNS> column1, VectorBase<float, COLUMNS> column2, VectorBase<float, COLUMNS> column3) : columns{column0, column1, column2, column3}
  {
    
  }
  
  
  
  
  const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::IDENTITY = Diagonal(1.0f);
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Diagonal(float diagonal) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>(diagonal);}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Diagonal(const VectorBase<float, 4> &value) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>(value);}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Diagonal(float v0, float v1, float v2, float v3) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>(VectorBase<float, 4>(v0, v1, v2, v3));}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Inverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result;
    
    
    result[0] = matrix[5]  * matrix[10] * matrix[15] -
                matrix[5]  * matrix[11] * matrix[14] -
                matrix[9]  * matrix[6]  * matrix[15] +
                matrix[9]  * matrix[7]  * matrix[14] +
                matrix[13] * matrix[6]  * matrix[11] -
                matrix[13] * matrix[7]  * matrix[10];
    
    result[4] = -matrix[4]  * matrix[10] * matrix[15] +
                matrix[4]  * matrix[11] * matrix[14] +
                matrix[8]  * matrix[6]  * matrix[15] -
                matrix[8]  * matrix[7]  * matrix[14] -
                matrix[12] * matrix[6]  * matrix[11] +
                matrix[12] * matrix[7]  * matrix[10];
    
    result[8] = matrix[4]  * matrix[9] * matrix[15] -
                matrix[4]  * matrix[11] * matrix[13] -
                matrix[8]  * matrix[5] * matrix[15] +
                matrix[8]  * matrix[7] * matrix[13] +
                matrix[12] * matrix[5] * matrix[11] -
                matrix[12] * matrix[7] * matrix[9];
    
    result[12] = -matrix[4]  * matrix[9] * matrix[14] +
                 matrix[4]  * matrix[10] * matrix[13] +
                 matrix[8]  * matrix[5] * matrix[14] -
                 matrix[8]  * matrix[6] * matrix[13] -
                 matrix[12] * matrix[5] * matrix[10] +
                 matrix[12] * matrix[6] * matrix[9];
    
    result[1] = -matrix[1]  * matrix[10] * matrix[15] +
                matrix[1]  * matrix[11] * matrix[14] +
                matrix[9]  * matrix[2] * matrix[15] -
                matrix[9]  * matrix[3] * matrix[14] -
                matrix[13] * matrix[2] * matrix[11] +
                matrix[13] * matrix[3] * matrix[10];
    
    result[5] = matrix[0]  * matrix[10] * matrix[15] -
                matrix[0]  * matrix[11] * matrix[14] -
                matrix[8]  * matrix[2] * matrix[15] +
                matrix[8]  * matrix[3] * matrix[14] +
                matrix[12] * matrix[2] * matrix[11] -
                matrix[12] * matrix[3] * matrix[10];
    
    result[9] = -matrix[0]  * matrix[9] * matrix[15] +
                matrix[0]  * matrix[11] * matrix[13] +
                matrix[8]  * matrix[1] * matrix[15] -
                matrix[8]  * matrix[3] * matrix[13] -
                matrix[12] * matrix[1] * matrix[11] +
                matrix[12] * matrix[3] * matrix[9];
    
    result[13] = matrix[0]  * matrix[9] * matrix[14] -
                 matrix[0]  * matrix[10] * matrix[13] -
                 matrix[8]  * matrix[1] * matrix[14] +
                 matrix[8]  * matrix[2] * matrix[13] +
                 matrix[12] * matrix[1] * matrix[10] -
                 matrix[12] * matrix[2] * matrix[9];
    
    result[2] = matrix[1]  * matrix[6] * matrix[15] -
                matrix[1]  * matrix[7] * matrix[14] -
                matrix[5]  * matrix[2] * matrix[15] +
                matrix[5]  * matrix[3] * matrix[14] +
                matrix[13] * matrix[2] * matrix[7] -
                matrix[13] * matrix[3] * matrix[6];
    
    result[6] = -matrix[0]  * matrix[6] * matrix[15] +
                matrix[0]  * matrix[7] * matrix[14] +
                matrix[4]  * matrix[2] * matrix[15] -
                matrix[4]  * matrix[3] * matrix[14] -
                matrix[12] * matrix[2] * matrix[7] +
                matrix[12] * matrix[3] * matrix[6];
    
    result[10] = matrix[0]  * matrix[5] * matrix[15] -
                 matrix[0]  * matrix[7] * matrix[13] -
                 matrix[4]  * matrix[1] * matrix[15] +
                 matrix[4]  * matrix[3] * matrix[13] +
                 matrix[12] * matrix[1] * matrix[7] -
                 matrix[12] * matrix[3] * matrix[5];
    
    result[14] = -matrix[0]  * matrix[5] * matrix[14] +
                 matrix[0]  * matrix[6] * matrix[13] +
                 matrix[4]  * matrix[1] * matrix[14] -
                 matrix[4]  * matrix[2] * matrix[13] -
                 matrix[12] * matrix[1] * matrix[6] +
                 matrix[12] * matrix[2] * matrix[5];
    
    result[3] = -matrix[1] * matrix[6] * matrix[11] +
                matrix[1] * matrix[7] * matrix[10] +
                matrix[5] * matrix[2] * matrix[11] -
                matrix[5] * matrix[3] * matrix[10] -
                matrix[9] * matrix[2] * matrix[7] +
                matrix[9] * matrix[3] * matrix[6];
    
    result[7] = matrix[0] * matrix[6] * matrix[11] -
                matrix[0] * matrix[7] * matrix[10] -
                matrix[4] * matrix[2] * matrix[11] +
                matrix[4] * matrix[3] * matrix[10] +
                matrix[8] * matrix[2] * matrix[7] -
                matrix[8] * matrix[3] * matrix[6];
    
    result[11] = -matrix[0] * matrix[5] * matrix[11] +
                 matrix[0] * matrix[7] * matrix[9] +
                 matrix[4] * matrix[1] * matrix[11] -
                 matrix[4] * matrix[3] * matrix[9] -
                 matrix[8] * matrix[1] * matrix[7] +
                 matrix[8] * matrix[3] * matrix[5];
    
    result[15] = matrix[0] * matrix[5] * matrix[10] -
                 matrix[0] * matrix[6] * matrix[9] -
                 matrix[4] * matrix[1] * matrix[10] +
                 matrix[4] * matrix[2] * matrix[9] +
                 matrix[8] * matrix[1] * matrix[6] -
                 matrix[8] * matrix[2] * matrix[5];
    
    float det = matrix[0] * result[0] + matrix[1] * result[4] + matrix[2] * result[8] + matrix[3] * result[12];
    
    det = 1.0f / det;
    
    for (index_t i = 0; i < 16; i++)
      result[i] *= det;
    
    return result;
    
  }
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::CreateFromRows(const VectorBase<float, 4> &r0, const VectorBase<float, 4> &r1, const VectorBase<float, 4> &r2, const VectorBase<float, 4> &r3)
  {
    return {Vector4(r0.x, r1.x, r2.x, r3.x), Vector4(r0.y, r1.y, r2.y, r3.y), Vector4(r0.z, r1.z, r2.z, r3.z), Vector4(r0.w, r1.w, r2.w, r3.w)};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::CreateFromColumns(const VectorBase<float, 4> &c0, const VectorBase<float, 4> &c1, const VectorBase<float, 4> &c2, const VectorBase<float, 4> &c3)
  {
    return {c0, c1, c2, c3};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Orthographic(float left, float right, float bottom, float top, float near, float far)
  {
    
    
    float tx = - (right + left) / (right - left);
    float ty = - (top + bottom) / (top - bottom);
    float tz = - (far + near) / (far - near);
    return {2.0f / (right - left), 0.0f, 0.0f, 0.0f,
                   0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
                   0.0f, 0.0f, -2.0f / (far - near), 0.0f,
                   tx, ty, tz, 1.0f};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Perspective(float fov, float aspectRatio, float near, float far)
  {
    float f = 1.0f / Tan(fov / 2.0f);
    float zRange = near - far;
    
    return {
    f / aspectRatio, 0.0f, 0.0f, 0.0f,
    0.0f, f, 0.0f, 0.0f,
    0.0f, 0.0f, (far + near) / zRange, -1.0f,
    0.0f, 0.0f, 2.0f * far * near / zRange, 0.0f};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::LookAt(const VectorBase<float, 3> &eye, const VectorBase<float, 3> &target, const VectorBase<float, 3> &up)
  {
    Vector3 zaxis = Vector3::Normalize(eye - target);
    Vector3 xaxis = Vector3::Cross(up, zaxis).Normalized();
    Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
    
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result;
    result[0] = xaxis.x;
    result[1] = yaxis.x;
    result[2] = zaxis.x;
    result[4] = xaxis.y;
    result[5] = yaxis.y;
    result[6] = zaxis.y;
    result[8] = xaxis.z;
    result[9] = yaxis.z;
    result[10] = zaxis.z;
    result[12] = -xaxis.Dot(eye);
    result[13] = -yaxis.Dot(eye);
    result[14] = -zaxis.Dot(eye);
    result[15] = 1;
    
    return result;
    
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Translate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix, const VectorBase<float, 3> &translation)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result = matrix;
    result[0] = 1;
    result[5] = 1;
    result[10] = 1;
    result[12] = translation.x;
    result[13] = translation.y;
    result[14] = translation.z;
    result[15] = 1;
    
    return result;
    
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix, float angle, const VectorBase<float, 3> &axis)
  {
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    float t = 1.0f - c;
    
    Vector3 naxis = axis.Normalized();
    
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result = matrix;
    result[0] = c + naxis.x * naxis.x * t;
    result[1] = naxis.x * naxis.y * t - naxis.z * s;
    result[2] = naxis.x * naxis.z * t + naxis.y * s;
    result[4] = naxis.y * naxis.x * t + naxis.z * s;
    result[5] = c + naxis.y * naxis.y * t;
    result[6] = naxis.y * naxis.z * t - naxis.x * s;
    result[8] = naxis.z * naxis.x * t - naxis.y * s;
    result[9] = naxis.z * naxis.y * t + naxis.x * s;
    result[10] = c + naxis.z * naxis.z * t;
    result[15] = 1;
    
    return result;
    
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& matrix, const QuaternionBase<float>& quaternion)
  {
    float xx = quaternion.x * quaternion.x;
    float xy = quaternion.x * quaternion.y;
    float xz = quaternion.x * quaternion.z;
    float xw = quaternion.x * quaternion.w;
    float yy = quaternion.y * quaternion.y;
    float yz = quaternion.y * quaternion.z;
    float yw = quaternion.y * quaternion.w;
    float zz = quaternion.z * quaternion.z;
    float zw = quaternion.z * quaternion.w;
    
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result = matrix;
    result[0] = 1.0f - 2.0f * (yy + zz);
    result[1] = 2.0f * (xy - zw);
    result[2] = 2.0f * (xz + yw);
    result[4] = 2.0f * (xy + zw);
    result[5] = 1.0f - 2 * (xx + zz);
    result[6] = 2.0f * (yz - xw);
    result[8] = 2.0f * (xz - yw);
    result[9] = 2.0f * (yz + xw);
    result[10] = 1.0f - 2.0f * (xx + yy);
    result[15] = 1.0f;
    
    return result;
  }
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Scale(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix, const VectorBase<float, 3> &scale)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result = matrix;
    
    result[0] = scale.x;
    result[5] = scale.y;
    result[10] = scale.z;
    return result;
  }
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Transpose(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result = matrix;
    result[1] = matrix[4];
    result[2] = matrix[8];
    result[3] = matrix[12];
    result[4] = matrix[1];
    result[6] = matrix[9];
    result[7] = matrix[13];
    result[8] = matrix[2];
    result[9] = matrix[6];
    result[11] = matrix[14];
    result[12] = matrix[3];
    result[13] = matrix[7];
    result[14] = matrix[11];
    
    return result;
  }
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Determinant(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> &matrix)
  {
    float det;
    float subFactor00 = matrix[2] * matrix[7] - matrix[6] * matrix[3];
    float subFactor01 = matrix[2] * matrix[11] - matrix[10] * matrix[3];
    float subFactor02 = matrix[2] * matrix[15] - matrix[14] * matrix[3];
    float subFactor03 = matrix[6] * matrix[11] - matrix[10] * matrix[7];
    float subFactor04 = matrix[6] * matrix[15] - matrix[14] * matrix[7];
    float subFactor05 = matrix[10] * matrix[15] - matrix[14] * matrix[11];
    
    VectorBase<float, 4> detCof(
    +(matrix[5] * subFactor05 - matrix[9] * subFactor04 + matrix[13] * subFactor03),
    -(matrix[1] * subFactor05 - matrix[9] * subFactor02 + matrix[13] * subFactor01),
    +(matrix[1] * subFactor04 - matrix[5] * subFactor02 + matrix[13] * subFactor00),
    -(matrix[1] * subFactor03 - matrix[5] * subFactor01 + matrix[9] * subFactor00)
    );
    
    det = matrix[0]*detCof.x + 	matrix[4]*detCof.y + 	matrix[8]*detCof.z + 	matrix[12]*detCof.w;
    
    return det;
  }
  
  
  
  
  float& AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator[](index_t index){return data[index];}
  
  float& AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator[](index_t row, index_t column){return data[AccessIndex(row, column)];}
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator[](index_t index)const{return data[index];}
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator[](index_t row, index_t column)const{return data[AccessIndex(row, column)];}
  
  bool AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator==(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const
  {
    for (int i=0; i<TOTAL_SIZE; i++)
    {
      if (data[i] != other.data[i])
        return false;
    }
    return true;
  }
  
  bool AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator!=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const{return !((*this)==other);}
  
  
  VectorBase<float, 4> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator*(const VectorBase<float, 4>& vec)const
  {
    return {data[0] * vec.x + data[1] * vec.y + data[2] * vec.z + data[3] * vec.w,
            data[4] * vec.x + data[5] * vec.y + data[6] * vec.z + data[7] * vec.w,
            data[8] * vec.x + data[9] * vec.y + data[10] * vec.z + data[11] * vec.w,
            data[12] * vec.x + data[13] * vec.y + data[14] * vec.z + data[15] * vec.w};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator*(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)const
  {
    const int N=4;
    AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom> result;
    for (int i = 0; i < N; i++) {
      result.m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[i][0]), m128[0]);
      for (int j = 1; j < N; j++) {
        result.m128[i] = _mm_add_ps(result.m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[i][j]), m128[j]));
      }
    }
    
    return result;
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator+=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)
  {
    for(index_t i = 0; i < TOTAL_SIZE; i++)
      data[i] += other.data[i];
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator-=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)
  {
    for(index_t i = 0; i < TOTAL_SIZE; i++)
      data[i] -= other.data[i];
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::operator*=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>& other)
  {
    const int N=4;
    
    for (int i = 0; i < N; i++) {
      m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[i][0]), m128[0]);
      for (int j = 1; j < N; j++) {
        m128[i] = _mm_add_ps(m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[i][j]), m128[j]));
      }
    }
    
    
  }
  
  VectorBase<float, 4>& AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Column(index_t index){return columns[index];}
  [[nodiscard]] const VectorBase<float, 4>& AbstractMatrixBase<float, 4, 4, LayoutPolicyTopToBottom>::Column(index_t index)const{return columns[index];}
  
}


std::ostream &operator<<(std::ostream &ostream, const Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyTopToBottom> &mat)
{
  ostream << std::fixed << std::setprecision(1);
  ostream << mat.Column(0) << '\n' << mat.Column(1) << '\n' << mat.Column(2) << '\n' << mat.Column(3) << '\n';
  return ostream;
}