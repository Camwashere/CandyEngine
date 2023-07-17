#include <candy/math/matrix/specialization/Matrix3.hpp>

namespace Candy::Math
{
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase()
  {
    memset(data, 0, sizeof(data));
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase(float diagonal)
  {
    memset(data, 0, sizeof(data));
    data[0] = diagonal;
    data[4] = diagonal;
    data[8] = diagonal;
  }
  
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase(const VectorBase<float, COLUMNS>& diagonal)
  {
    memset(data, 0, sizeof(data));
    data[0] = diagonal.x;
    data[4] = diagonal.y;
    data[8] = diagonal.z;
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)
  {
    memcpy(data, other.data, sizeof(data));
  }
  
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase(VectorBase<float, COLUMNS> row0, VectorBase<float, COLUMNS> row1, VectorBase<float, COLUMNS> row2) : rows{row0, row1, row2}
  {
  
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::AbstractMatrixBase(float r0c0, float r0c1, float r0c2,
                                                                               float r1c0, float r1c1, float r1c2,
                                                                               float r2c0, float r2c1, float r2c2) : data{r0c0, r0c1, r0c2,
                                                                                                                           r1c0, r1c1, r1c2,
                                                                                                                           r2c0, r2c1, r2c2}
  {
  
  }
  
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::Diagonal(float diagonal)
  {
    return AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>(diagonal);
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::Diagonal(const VectorBase<float, 3>& value)
  {
    return AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>(value);
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::Diagonal(float v0, float v1, float v2)
  {
    return AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>(VectorBase<float, 3>(v0, v1, v2));
  }
  
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::CreateFromRows(const VectorBase<float, 3>& r0, const VectorBase<float, 3>& r1, const VectorBase<float, 3>& r2)
  {
    return {r0, r1, r2};
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::CreateFromColumns(const VectorBase<float, 3>& c0, const VectorBase<float, 3>& c1, const VectorBase<float, 3>& c2)
  {
    return {c0.x, c1.x, c2.x,
            c0.y, c1.y, c2.y,
            c0.z, c1.z, c2.z};
  }
  
  float& AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator[](index_t index){return data[index]; }
  float& AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator[](index_t row, index_t column){return data[AccessIndex(row, column)];}
  float AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator[](index_t index)const{return data[index];}
  float AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator[](index_t row, index_t column)const{return data[AccessIndex(row, column)];}
  
  bool AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator==(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const
  {
    return memcmp(data, other.data, sizeof(data)) == 0;
  }
  bool AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator!=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const
  {
    return memcmp(data, other.data, sizeof(data)) != 0;
  }
  
  VectorBase<float, 3> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator*(const VectorBase<float, 3>& vec)const
  {
    return {rows[0].Dot(vec), rows[1].Dot(vec), rows[2].Dot(vec)};
  }
  AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator*(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)const
  {
    const int N = 3;
    AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight> result;
    
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
  
  void AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator+=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)
  {
    m128[0] = _mm_add_ps(m128[0], other.m128[0]);
    m128[1] = _mm_add_ps(m128[1], other.m128[1]);
    m128[2] = _mm_add_ps(m128[2], other.m128[2]);
  }
  void AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator-=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)
  {
    m128[0] = _mm_sub_ps(m128[0], other.m128[0]);
    m128[1] = _mm_sub_ps(m128[1], other.m128[1]);
    m128[2] = _mm_sub_ps(m128[2], other.m128[2]);
  }
  void AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>::operator*=(const AbstractMatrixBase<float, 3, 3, LayoutPolicyLeftToRight>& other)
  {
    const int N = 3;
    
    
    for (int i = 0; i < N; i++)
    {
      m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[0][i]), m128[0]);
      for (int j = 1; j < N; j++)
      {
        m128[i] = _mm_add_ps(m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[j][i]), m128[j]));
      }
    }
    
    
  }
}