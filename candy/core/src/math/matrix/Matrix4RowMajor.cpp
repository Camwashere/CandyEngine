#include <candy/math/matrix/specialization/Matrix4RowMajor.hpp>
#include <candy/math/MathOps.hpp>
#include "CandyPch.hpp"
namespace Candy::Math
{
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase()
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase(float diagonal)
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
    data[0] = diagonal;
    data[5] = diagonal;
    data[10] = diagonal;
    data[15] = diagonal;
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase(const VectorBase<float, COLUMNS>& diagonal)
  {
    data.fill(0.0f);
    //memset(data, 0, TOTAL_SIZE);
    data[0] = diagonal[0];
    data[5] = diagonal[1];
    data[10] = diagonal[2];
    data[15] = diagonal[3];
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)
  {
    data.fill(0.0f);
    //memcpy(data, other.data, TOTAL_SIZE);
  }
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase(VectorBase<float, COLUMNS> row0, VectorBase<float, COLUMNS> row1, VectorBase<float, COLUMNS> row2, VectorBase<float, COLUMNS> row3) : rows{row0, row1, row2, row3}
  {
  
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::AbstractMatrixBase(float r0c0, float r0c1, float r0c2, float r0c3,
                                                                               float r1c0, float r1c1, float r1c2, float r1c3,
                                                                               float r2c0, float r2c1, float r2c2, float r2c3,
                                                                               float r3c0, float r3c1, float r3c2, float r3c3) : data{r0c0, r0c1, r0c2, r0c3, r1c0, r1c1, r1c2, r1c3, r2c0, r2c1, r2c2, r2c3, r3c0, r3c1, r3c2, r3c3}
  {
  
  }
  
  
  
  const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::IDENTITY = Diagonal(1.0f);
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Diagonal(float diagonal) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>(diagonal);}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Diagonal(const VectorBase<float, 4> &value) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>(value);}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Diagonal(float v0, float v1, float v2, float v3) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>(VectorBase<float, 4>(v0, v1, v2, v3));}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Inverse(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    
    
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
    
    // TODO: THROW ERROR IF DET==0
    if (det == 0)
    {
      CANDY_CORE_ERROR("Matrix4::Inverse() - Matrix is not invertible");
      CANDY_CORE_ASSERT(false);
      return {};
    }
    
    
    det = 1.0f / det;
    
    for (index_t i = 0; i < 16; i++)
      result[i] *= det;
    
    return result;
    
  }
  
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::CreateFromRows(const VectorBase<float, 4> &r0, const VectorBase<float, 4> &r1, const VectorBase<float, 4> &r2, const VectorBase<float, 4> &r3) {return AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>(r0, r1, r2, r3);}
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::CreateFromColumns(const VectorBase<float, 4> &c0, const VectorBase<float, 4> &c1, const VectorBase<float, 4> &c2, const VectorBase<float, 4> &c3)
  {
    return {c0[0], c1[0], c2[0], c3[0],
            c0[1], c1[1], c2[1], c3[1],
            c0[2], c1[2], c2[2], c3[2],
            c0[3], c1[3], c2[3], c3[3]};
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Orthographic(float left, float right, float bottom, float top, float near, float far)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    
    result[0,0] = 2 / (right - left);
    result[1,1] = 2 / (top - bottom);
    result[2,2] = -2 / (far - near);
    result[3,0] = -(right + left) / (right - left);
    result[3,1] = -(top + bottom) / (top - bottom);
    result[3,2] = -(far + near) / (far - near);
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Perspective(float fov, float aspectRatio, float near, float far)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    float tanHalfFov = Math::Tan(fov / 2);
    result[0,0] = 1 / (aspectRatio * tanHalfFov);
    result[1,1] = 1 / tanHalfFov;
    result[2,2] = -(far + near) / (far - near);
    result[2,3] = -1;
    result[3,2] = -(2 * far * near) / (far - near);
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::LookAt(const VectorBase<float, 3> &eye, const VectorBase<float, 3> &target, const VectorBase<float, 3> &up)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    VectorBase<float, 3> f = VectorBase<float, 3>::Normalize(target - eye);
    VectorBase<float, 3> s = f.Cross(up).Normalized();
    VectorBase<float, 3> u = s.Cross(f);
    result[0,0] = s.x;
    result[1,0] = s.y;
    result[2,0] = s.z;
    result[0,1] = u.x;
    result[1,1] = u.y;
    result[2,1] = u.z;
    result[0,2] = -f.x;
    result[1,2] = -f.y;
    result[2,2] = -f.z;
    result[3,0] = -s.Dot(eye);
    result[3,1] = -u.Dot(eye);
    result[3,2] = f.Dot(eye);
    
    return result;
    
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Translate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix, const VectorBase<float, 3> &translation)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result(matrix);
    
    result[3,0] += translation.x;
    result[3,1] += translation.y;
    result[3,2] += translation.z;
    
    return result;
    
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Rotate(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix, float angle, const VectorBase<float, 3> &axis)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    float omc = 1 - c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    result[0,0] = x * x * omc + c;
    result[1,0] = y * x * omc + z * s;
    result[2,0] = x * z * omc - y * s;
    result[0,1] = x * y * omc - z * s;
    result[1,1] = y * y * omc + c;
    result[2,1] = y * z * omc + x * s;
    result[0,2] = x * z * omc + y * s;
    result[1,2] = y * z * omc - x * s;
    result[2,2] = z * z * omc + c;
    result[3,0] = matrix[3,0];
    result[3,1] = matrix[3,1];
    result[3,2] = matrix[3,2];
    
    return matrix*result;
    
  }
 
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Scale(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix, const VectorBase<float, 3> &scale)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result(matrix);
    result[0,0] *= scale.x;
    result[1,0] *= scale.x;
    result[2,0] *= scale.x;
    result[0,1] *= scale.y;
    result[1,1] *= scale.y;
    result[2,1] *= scale.y;
    result[0,2] *= scale.z;
    result[1,2] *= scale.z;
    result[2,2] *= scale.z;
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Frustum(float left, float right, float bottom, float top, float near, float far)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    result[0,0] = (2 * near) / (right - left);
    result[1,1] = (2 * near) / (top - bottom);
    result[2,0] = (right + left) / (right - left);
    result[2,1] = (top + bottom) / (top - bottom);
    result[2,2] = -(far + near) / (far - near);
    result[2,3] = -1;
    result[3,2] = -(2 * far * near) / (far - near);
    
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::InfinitePerspective(float fov, float aspectRatio, float near)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    float range = Math::Tan(fov / 2) * near;
    float left = -range * aspectRatio;
    float right = range * aspectRatio;
    float bottom = -range;
    float top = range;
    result[0,0] = (2 * near) / (right - left);
    result[1,1] = (2 * near) / (top - bottom);
    result[2,2] = -1;
    result[2,3] = -1;
    result[3,2] = -2 * near;
    
    return result;
  }
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Transpose(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result = matrix;
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
  
  std::array<float, 16> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::ValuePtr(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& matrix)
  {
    std::array<float, 16> result{};
    for (int i=0; i<4; i++)
    {
      int a = i*4;
      result[a] = matrix.rows[0][i];
      result[a+1] = matrix.rows[1][i];
      result[a+2] = matrix.rows[2][i];
      result[a+3] = matrix.rows[3][i];
    }
    
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::PickMatrix(const VectorBase<float, 2> &center, const VectorBase<float, 2> &delta, const VectorBase<float, 4> &viewport)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    
    float tempX = (viewport.z - 2 * (center.x - viewport.x)) / delta.x;
    float tempY = (viewport.w - 2 * (center.y - viewport.y)) / delta.y;
    result[0,0] = viewport.z / delta.x;
    result[3,0] = tempX;
    result[1,1] = viewport.w / delta.y;
    result[3,1] = tempY;
    
    
    return result;
    
  }
  
  
  VectorBase<float, 3> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Project(const VectorBase<float, 3> &obj, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &projection, const VectorBase<float, 4> &viewport)
  {
    VectorBase<float, 4> tmp(obj.x, obj.y, obj.z, 1);
    tmp = model * tmp;
    tmp = projection * tmp;
    
    tmp /= tmp.w;
    tmp = tmp * 0.5f;
    tmp.AddToAll(0.5f);
    tmp.x = tmp.x * viewport.z + viewport.x;
    tmp.y = tmp.y * viewport.w + viewport.y;
    
    return {tmp.x, tmp.y, tmp.z};
  }
  
  
  VectorBase<float, 3> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::UnProject(const VectorBase<float, 3> &windowCoords, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &model, const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &projection, const VectorBase<float, 4> &viewport)
  {
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> inverse = AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Inverse(projection * model);
    
    VectorBase<float, 4> tmp(windowCoords.x, windowCoords.y, windowCoords.z, 1);
    tmp.x = (tmp.x - viewport.x) / viewport.z;
    tmp.y = (tmp.y - viewport.y) / viewport.w;
    tmp = tmp * 2;
    tmp.SubtractFromAll(1);
    
    VectorBase<float, 4> obj = inverse * tmp;
    obj /= obj.w;
    
    return {obj.x, obj.y, obj.z};
  }
  
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Determinant(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> &matrix)
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
  
  
  
  
  float& AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator[](index_t index){return data[index];}
  
  float& AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator[](index_t row, index_t column){return data[AccessIndex(row, column)];}
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator[](index_t index)const{return data[index];}
  
  float AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator[](index_t row, index_t column)const{return data[AccessIndex(row, column)];}
  
  bool AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator==(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const
  {
    for (int i=0; i<TOTAL_SIZE; i++)
    {
      if (data[i] != other.data[i])
      {
        return false;
      }
    }
    return true;
  }
  
  bool AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator!=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const{return !((*this)==other);}
  
  
  VectorBase<float, 4> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator*(const VectorBase<float, 4>& vec)const
  {
    VectorBase<float, 4> result;
    result.x = (*this)[0,0] * vec.x + (*this)[1,0] * vec.y + (*this)[2,0] * vec.z + (*this)[3,0] * vec.w;
    result.y = (*this)[0,1] * vec.x + (*this)[1,1] * vec.y + (*this)[2,1] * vec.z + (*this)[3,1] * vec.w;
    result.z = (*this)[0,2] * vec.x + (*this)[1,2] * vec.y + (*this)[2,2] * vec.z + (*this)[3,2] * vec.w;
    result.w = (*this)[0,3] * vec.x + (*this)[1,3] * vec.y + (*this)[2,3] * vec.z + (*this)[3,3] * vec.w;
    return result;
  }
  
  
  AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator*(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)const
  {
    const int N = 4;
    AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight> result;
    
    for (int i = 0; i < N; i++)
    {
      result.m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[0][i]), m128[0]);
      for (int j = 1; j < N; j++)
      {
        result.m128[i] = _mm_add_ps(result.m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[j][i]), m128[j]));
      }
    }
    
    return result;
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator+=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)
  {
    for(index_t i = 0; i < TOTAL_SIZE; i++)
      data[i] += other.data[i];
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator-=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)
  {
    for(index_t i = 0; i < TOTAL_SIZE; i++)
      data[i] -= other.data[i];
  }
  
  void AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::operator*=(const AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>& other)
  {
    const int N = 4;
    
    for (int i = 0; i < N; i++)
    {
      m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[0][i]), m128[0]);
      for (int j = 1; j < N; j++)
      {
        m128[i] = _mm_add_ps(m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[j][i]), m128[j]));
      }
    }
  }
  
  VectorBase<float, 4>& AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Row(index_t index)&{return rows[index];}
  [[nodiscard]] const VectorBase<float, 4>& AbstractMatrixBase<float, 4, 4, LayoutPolicyLeftToRight>::Row(index_t index)const&{return rows[index];}
  
}


std::ostream &operator<<(std::ostream &ostream, const Candy::Math::AbstractMatrixBase<float, 4, 4, Candy::Math::LayoutPolicyLeftToRight> &mat)
{
  ostream << std::fixed << std::setprecision(1);
  ostream << mat.Row(0) << '\n' << mat.Row(1) << '\n' << mat.Row(2) << '\n' << mat.Row(3) << '\n';
  return ostream;
}