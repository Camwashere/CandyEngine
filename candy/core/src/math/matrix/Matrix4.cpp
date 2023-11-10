#include <candy/math/matrix/specialization/Matrix4.hpp>
#include <candy/base/Assert.hpp>
#include <candy/math/Quaternion.hpp>
#include <candy/math/Random.hpp>

#ifdef CANDY_PLATFORM_WINDOWS
#pragma GCC target("sse4.1")
#endif

#include <immintrin.h>
#include <emmintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>

#include "CandyPch.hpp"
#define MakeShuffleMask(x,y,z,w)           (x | (y<<2) | (z<<4) | (w<<6))

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzleMask(vec, mask)          _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vec), mask))
#define VecSwizzle(vec, x, y, z, w)        VecSwizzleMask(vec, MakeShuffleMask(x,y,z,w))
//#define VecSwizzle1(vec, x)                VecSwizzleMask(vec, MakeShuffleMask(x,x,x,x))
#define VecSwizzle1(vec, x) _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(x,x,x,x))
// special swizzle
#define VecSwizzle_0022(vec)               _mm_moveldup_ps(vec)
#define VecSwizzle_1133(vec)               _mm_movehdup_ps(vec)

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x,y,z,w)    _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x,y,z,w))
// special shuffle
#define VecShuffle_0101(vec1, vec2)        _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2)        _mm_movehl_ps(vec2, vec1)
namespace Candy::Math
{
  static constexpr int AccessIndex(int row, int column){return row+column*4;}
  
  Matrix4::Matrix4()
  {
    CANDY_PROFILE_FUNCTION();
    data.fill(0.0f);
  }
  
  Matrix4::Matrix4(float diagonal)
  {
    CANDY_PROFILE_FUNCTION();
    data.fill(0.0f);
    data[0] = diagonal;
    data[5] = diagonal;
    data[10] = diagonal;
    data[15] = diagonal;
  }
  
  Matrix4::Matrix4(const Vector4& diagonal)
  {
    CANDY_PROFILE_FUNCTION();
    data.fill(0.0f);
    data[0] = diagonal[0];
    data[5] = diagonal[1];
    data[10] = diagonal[2];
    data[15] = diagonal[3];
  }
  
  Matrix4::Matrix4(const Matrix4& other) : data(other.data)
  {
    CANDY_PROFILE_FUNCTION();
  }
  
  Matrix4::Matrix4(std::initializer_list<float> elements)
  {
    CANDY_PROFILE_FUNCTION();
    int count=0;
    for (float element : elements)
    {
      data[count]=element;
      count++;
    }
  }
  
  Matrix4::Matrix4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3) : columns{column0, column1, column2, column3}
  {
    CANDY_PROFILE_FUNCTION();
  }
  
  Matrix4::Matrix4(__m128 m0, __m128 m1, __m128 m2, __m128 m3) : m128{m0, m1, m2, m3}
  {
    CANDY_PROFILE_FUNCTION();
  }
  
  
  const Matrix4 Matrix4::IDENTITY = Diagonal(1.0f);
  
  Matrix4 Matrix4::Random(float min, float max)
  {
    Matrix4 result;
    for (int i=0; i<16; ++i)
    {
      result.data[i] = RandomF::Range(min, max);
    }
    
    return result;
    
  }
  Matrix4 Matrix4::Diagonal(float diagonal) {return Matrix4(diagonal);}
  
  
  Matrix4 Matrix4::Diagonal(const Vector4 &value) {return Matrix4(value);}
  
  
  Matrix4 Matrix4::Diagonal(float v0, float v1, float v2, float v3) {return Matrix4(Vector4(v0, v1, v2, v3));}
  
  
  Matrix4 Matrix4::Inverse(const Matrix4 &matrix)
  {
    CANDY_PROFILE_FUNCTION();
    return FastInverse(matrix);
    /*Matrix4 result;
    
    
    result.data[0] = matrix.data[5]  * matrix.data[10] * matrix.data[15] -
                matrix.data[5]  * matrix.data[11] * matrix.data[14] -
                matrix.data[9]  * matrix.data[6]  * matrix.data[15] +
                matrix.data[9]  * matrix.data[7]  * matrix.data[14] +
                matrix.data[13] * matrix.data[6]  * matrix.data[11] -
                matrix.data[13] * matrix.data[7]  * matrix.data[10];
    
    result.data[4] = -matrix.data[4]  * matrix.data[10] * matrix.data[15] +
                matrix.data[4]  * matrix.data[11] * matrix.data[14] +
                matrix.data[8]  * matrix.data[6]  * matrix.data[15] -
                matrix.data[8]  * matrix.data[7]  * matrix.data[14] -
                matrix.data[12] * matrix.data[6]  * matrix.data[11] +
                matrix.data[12] * matrix.data[7]  * matrix.data[10];
    
    result.data[8] = matrix.data[4]  * matrix.data[9] * matrix.data[15] -
                matrix.data[4]  * matrix.data[11] * matrix.data[13] -
                matrix.data[8]  * matrix.data[5] * matrix.data[15] +
                matrix.data[8]  * matrix.data[7] * matrix.data[13] +
                matrix.data[12] * matrix.data[5] * matrix.data[11] -
                matrix.data[12] * matrix.data[7] * matrix.data[9];
    
    result.data[12] = -matrix.data[4]  * matrix.data[9] * matrix.data[14] +
                 matrix.data[4]  * matrix.data[10] * matrix.data[13] +
                 matrix.data[8]  * matrix.data[5] * matrix.data[14] -
                 matrix.data[8]  * matrix.data[6] * matrix.data[13] -
                 matrix.data[12] * matrix.data[5] * matrix.data[10] +
                 matrix.data[12] * matrix.data[6] * matrix.data[9];
    
    result.data[1] = -matrix.data[1]  * matrix.data[10] * matrix.data[15] +
                matrix.data[1]  * matrix.data[11] * matrix.data[14] +
                matrix.data[9]  * matrix.data[2] * matrix.data[15] -
                matrix.data[9]  * matrix.data[3] * matrix.data[14] -
                matrix.data[13] * matrix.data[2] * matrix.data[11] +
                matrix.data[13] * matrix.data[3] * matrix.data[10];
    
    result.data[5] = matrix.data[0]  * matrix.data[10] * matrix.data[15] -
                matrix.data[0]  * matrix.data[11] * matrix.data[14] -
                matrix.data[8]  * matrix.data[2] * matrix.data[15] +
                matrix.data[8]  * matrix.data[3] * matrix.data[14] +
                matrix.data[12] * matrix.data[2] * matrix.data[11] -
                matrix.data[12] * matrix.data[3] * matrix.data[10];
    
    result.data[9] = -matrix.data[0]  * matrix.data[9] * matrix.data[15] +
                matrix.data[0]  * matrix.data[11] * matrix.data[13] +
                matrix.data[8]  * matrix.data[1] * matrix.data[15] -
                matrix.data[8]  * matrix.data[3] * matrix.data[13] -
                matrix.data[12] * matrix.data[1] * matrix.data[11] +
                matrix.data[12] * matrix.data[3] * matrix.data[9];
    
    result.data[13] = matrix.data[0]  * matrix.data[9] * matrix.data[14] -
                 matrix.data[0]  * matrix.data[10] * matrix.data[13] -
                 matrix.data[8]  * matrix.data[1] * matrix.data[14] +
                 matrix.data[8]  * matrix.data[2] * matrix.data[13] +
                 matrix.data[12] * matrix.data[1] * matrix.data[10] -
                 matrix.data[12] * matrix.data[2] * matrix.data[9];
    
    result.data[2] = matrix.data[1]  * matrix.data[6] * matrix.data[15] -
                matrix.data[1]  * matrix.data[7] * matrix.data[14] -
                matrix.data[5]  * matrix.data[2] * matrix.data[15] +
                matrix.data[5]  * matrix.data[3] * matrix.data[14] +
                matrix.data[13] * matrix.data[2] * matrix.data[7] -
                matrix.data[13] * matrix.data[3] * matrix.data[6];
    
    result.data[6] = -matrix.data[0]  * matrix.data[6] * matrix.data[15] +
                matrix.data[0]  * matrix.data[7] * matrix.data[14] +
                matrix.data[4]  * matrix.data[2] * matrix.data[15] -
                matrix.data[4]  * matrix.data[3] * matrix.data[14] -
                matrix.data[12] * matrix.data[2] * matrix.data[7] +
                matrix.data[12] * matrix.data[3] * matrix.data[6];
    
    result.data[10] = matrix.data[0]  * matrix.data[5] * matrix.data[15] -
                 matrix.data[0]  * matrix.data[7] * matrix.data[13] -
                 matrix.data[4]  * matrix.data[1] * matrix.data[15] +
                 matrix.data[4]  * matrix.data[3] * matrix.data[13] +
                 matrix.data[12] * matrix.data[1] * matrix.data[7] -
                 matrix.data[12] * matrix.data[3] * matrix.data[5];
    
    result.data[14] = -matrix.data[0]  * matrix.data[5] * matrix.data[14] +
                 matrix.data[0]  * matrix.data[6] * matrix.data[13] +
                 matrix.data[4]  * matrix.data[1] * matrix.data[14] -
                 matrix.data[4]  * matrix.data[2] * matrix.data[13] -
                 matrix.data[12] * matrix.data[1] * matrix.data[6] +
                 matrix.data[12] * matrix.data[2] * matrix.data[5];
    
    result.data[3] = -matrix.data[1] * matrix.data[6] * matrix.data[11] +
                matrix.data[1] * matrix.data[7] * matrix.data[10] +
                matrix.data[5] * matrix.data[2] * matrix.data[11] -
                matrix.data[5] * matrix.data[3] * matrix.data[10] -
                matrix.data[9] * matrix.data[2] * matrix.data[7] +
                matrix.data[9] * matrix.data[3] * matrix.data[6];
    
    result.data[7] = matrix.data[0] * matrix.data[6] * matrix.data[11] -
                matrix.data[0] * matrix.data[7] * matrix.data[10] -
                matrix.data[4] * matrix.data[2] * matrix.data[11] +
                matrix.data[4] * matrix.data[3] * matrix.data[10] +
                matrix.data[8] * matrix.data[2] * matrix.data[7] -
                matrix.data[8] * matrix.data[3] * matrix.data[6];
    
    result.data[11] = -matrix.data[0] * matrix.data[5] * matrix.data[11] +
                 matrix.data[0] * matrix.data[7] * matrix.data[9] +
                 matrix.data[4] * matrix.data[1] * matrix.data[11] -
                 matrix.data[4] * matrix.data[3] * matrix.data[9] -
                 matrix.data[8] * matrix.data[1] * matrix.data[7] +
                 matrix.data[8] * matrix.data[3] * matrix.data[5];
    
    result.data[15] = matrix.data[0] * matrix.data[5] * matrix.data[10] -
                 matrix.data[0] * matrix.data[6] * matrix.data[9] -
                 matrix.data[4] * matrix.data[1] * matrix.data[10] +
                 matrix.data[4] * matrix.data[2] * matrix.data[9] +
                 matrix.data[8] * matrix.data[1] * matrix.data[6] -
                 matrix.data[8] * matrix.data[2] * matrix.data[5];
    
    float det = matrix.data[0] * result.data[0] + matrix.data[1] * result.data[4] + matrix.data[2] * result.data[8] + matrix.data[3] * result.data[12];
    // check if determinant is near zero (within epsilon)
    CANDY_CORE_ASSERT(Math::Abs(det) < Math::Epsilon<float>(), "Matrix4 is not invertible");
    det = 1.0f / det;
    
    for (int i = 0; i < 16; i++)
      result.data[i] *= det;
    
    return result;*/
    
  }
  
  
  
  #define SMALL_NUMBER		(1.e-8f)
  Matrix4 Matrix4::FastInverse(const Matrix4& matrix)
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 r;
    
    // transpose 3x3, we know m03 = m13 = m23 = 0
    __m128 t0 = VecShuffle_0101(matrix.m128[0], matrix.m128[1]); // 00, 01, 10, 11
    __m128 t1 = VecShuffle_2323(matrix.m128[0], matrix.m128[1]); // 02, 03, 12, 13
    r.m128[0] = VecShuffle(t0, matrix.m128[2], 0,2,0,3); // 00, 10, 20, 23(=0)
    r.m128[1] = VecShuffle(t0, matrix.m128[2], 1,3,1,3); // 01, 11, 21, 23(=0)
    r.m128[2] = VecShuffle(t1, matrix.m128[2], 0,2,2,3); // 02, 12, 22, 23(=0)
    
    // (SizeSqr(m128[0]), SizeSqr(m128[1]), SizeSqr(m128[2]), 0)
    __m128 sizeSqr;
    sizeSqr =                     _mm_mul_ps(r.m128[0], r.m128[0]);
    sizeSqr = _mm_add_ps(sizeSqr, _mm_mul_ps(r.m128[1], r.m128[1]));
    sizeSqr = _mm_add_ps(sizeSqr, _mm_mul_ps(r.m128[2], r.m128[2]));
    
    // optional test to avoid divide by 0
    __m128 one = _mm_set1_ps(1.f);
    // for each component, if(sizeSqr < SMALL_NUMBER) sizeSqr = 1;
    __m128 rSizeSqr = _mm_blendv_ps(
    _mm_div_ps(one, sizeSqr),
    one,
    _mm_cmplt_ps(sizeSqr, _mm_set1_ps(SMALL_NUMBER))
    );
    
    r.m128[0] = _mm_mul_ps(r.m128[0], rSizeSqr);
    r.m128[1] = _mm_mul_ps(r.m128[1], rSizeSqr);
    r.m128[2] = _mm_mul_ps(r.m128[2], rSizeSqr);
    
    // last line
    r.m128[3] =                       _mm_mul_ps(r.m128[0], VecSwizzle1(matrix.m128[3], 0));
    r.m128[3] = _mm_add_ps(r.m128[3], _mm_mul_ps(r.m128[1], VecSwizzle1(matrix.m128[3], 1)));
    r.m128[3] = _mm_add_ps(r.m128[3], _mm_mul_ps(r.m128[2], VecSwizzle1(matrix.m128[3], 2)));
    r.m128[3] = _mm_sub_ps(_mm_setr_ps(0.f, 0.f, 0.f, 1.f), r.m128[3]);
    
    return r;
    
    
  }
  
  
  
  Matrix4 Matrix4::CreateFromRows(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
  {
    CANDY_PROFILE_FUNCTION();
    return {Vector4(r0.x, r1.x, r2.x, r3.x), Vector4(r0.y, r1.y, r2.y, r3.y), Vector4(r0.z, r1.z, r2.z, r3.z), Vector4(r0.w, r1.w, r2.w, r3.w)};
  }
  
  
  Matrix4 Matrix4::CreateFromColumns(const Vector4 &c0, const Vector4 &c1, const Vector4 &c2, const Vector4 &c3)
  {
    CANDY_PROFILE_FUNCTION();
    return {c0, c1, c2, c3};
  }
  
  
  Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 ortho = Matrix4::IDENTITY;
    
    ortho[0,0] = 2.0f / (right - left);
    ortho[1,1] = 2.0f / (top - bottom);
    ortho[2,2] = 1.0f / (far - near);
    ortho[3,0] = -(right + left) / (right - left);
    ortho[3,1] = -(top + bottom) / (top - bottom);
    ortho[3,2] = -near / (far - near);
    return ortho;
  }
  
  
  Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far)
  {
    CANDY_PROFILE_FUNCTION();
    float f = 1.0f / Tan(fov / 2.0f);
    float zRange = near - far;
    
    
    return {
    f / aspectRatio, 0.0f, 0.0f, 0.0f,
    0.0f, f, 0.0f, 0.0f,
    0.0f, 0.0f, (far + near) / zRange, -1.0f,
    0.0f, 0.0f, 2.0f * far * near / zRange, 0.0f};
  }
  
  
  Matrix4 Matrix4::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
  {
    CANDY_PROFILE_FUNCTION();
    Vector3 zaxis = Vector3::Normalize(eye - target);
    Vector3 xaxis = Vector3::Cross(up, zaxis).Normalized();
    Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
    
    Matrix4 result;
    result.data[0] = xaxis.x;
    result.data[1] = yaxis.x;
    result.data[2] = zaxis.x;
    result.data[4] = xaxis.y;
    result.data[5] = yaxis.y;
    result.data[6] = zaxis.y;
    result.data[8] = xaxis.z;
    result.data[9] = yaxis.z;
    result.data[10] = zaxis.z;
    result.data[12] = -xaxis.Dot(eye);
    result.data[13] = -yaxis.Dot(eye);
    result.data[14] = -zaxis.Dot(eye);
    result.data[15] = 1;
    
    return result;
    
  }
  
  
  Matrix4 Matrix4::Translate(const Matrix4 &matrix, const Vector3 &translation)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 result = matrix;
    result.data[0] = 1;
    result.data[5] = 1;
    result.data[10] = 1;
    result.data[12] = translation.x;
    result.data[13] = translation.y;
    result.data[14] = translation.z;
    result.data[15] = 1;
    
    return result;
    
  }
  
  
  Matrix4 Matrix4::Rotate(const Matrix4 &matrix, float angle, const Vector3 &axis)
  {
    CANDY_PROFILE_FUNCTION();
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    float t = 1.0f - c;
    
    Vector3 naxis = axis.Normalized();
    
    Matrix4 result = matrix;
    result.data[0] = c + naxis.x * naxis.x * t;
    result.data[1] = naxis.x * naxis.y * t - naxis.z * s;
    result.data[2] = naxis.x * naxis.z * t + naxis.y * s;
    result.data[4] = naxis.y * naxis.x * t + naxis.z * s;
    result.data[5] = c + naxis.y * naxis.y * t;
    result.data[6] = naxis.y * naxis.z * t - naxis.x * s;
    result.data[8] = naxis.z * naxis.x * t - naxis.y * s;
    result.data[9] = naxis.z * naxis.y * t + naxis.x * s;
    result.data[10] = c + naxis.z * naxis.z * t;
    result.data[15] = 1;
    
    return result;
    
  }
  
  Matrix4 Matrix4::Rotate(const Matrix4& matrix, const Quaternion& quaternion)
  {
    CANDY_PROFILE_FUNCTION();
    float xx = quaternion.x * quaternion.x;
    float xy = quaternion.x * quaternion.y;
    float xz = quaternion.x * quaternion.z;
    float xw = quaternion.x * quaternion.w;
    float yy = quaternion.y * quaternion.y;
    float yz = quaternion.y * quaternion.z;
    float yw = quaternion.y * quaternion.w;
    float zz = quaternion.z * quaternion.z;
    float zw = quaternion.z * quaternion.w;
    
    Matrix4 result = matrix;
    result.data[0] = 1.0f - 2.0f * (yy + zz);
    result.data[1] = 2.0f * (xy - zw);
    result.data[2] = 2.0f * (xz + yw);
    result.data[4] = 2.0f * (xy + zw);
    result.data[5] = 1.0f - 2 * (xx + zz);
    result.data[6] = 2.0f * (yz - xw);
    result.data[8] = 2.0f * (xz - yw);
    result.data[9] = 2.0f * (yz + xw);
    result.data[10] = 1.0f - 2.0f * (xx + yy);
    result.data[15] = 1.0f;
    
    return result;
  }
  Matrix4 Matrix4::Scale(const Matrix4 &matrix, const Vector3 &scale)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 result = matrix;
    
    result.data[0] = scale.x;
    result.data[5] = scale.y;
    result.data[10] = scale.z;
    return result;
  }
  
  Matrix4 Matrix4::Frustum(float left, float right, float bottom, float top, float near, float far)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 frustum;
    
    frustum.data[0] = (2.0f * near) / (right - left);
    frustum.data[5] = -(2.0f * near) / (top - bottom); // Y coordinate is flipped
    frustum.data[8] = (right + left) / (right - left);
    frustum.data[9] = (top + bottom) / (top - bottom);
    frustum.data[10] = -((far + near) / (far - near));
    frustum.data[11] = -1;
    frustum.data[14] = -((2.0f * far * near) / (far - near));
    frustum.data[15] = 0.0f;
    
    return frustum;
  }
  Matrix4 Matrix4::InfinitePerspective(float fov, float aspectRatio, float near)
  {
    CANDY_PROFILE_FUNCTION();
    float range = Tan(fov * 0.5f);
    Matrix4 infinitePerspective;
    
    infinitePerspective.data[0] = 1.0f / (range * aspectRatio);
    infinitePerspective.data[5] = 1.0f / range;
    infinitePerspective.data[10] = -1.0f;
    infinitePerspective.data[11] = -1.0f;
    infinitePerspective.data[14] = -2.0f * near;
    infinitePerspective.data[15] = 0.0f;
    
    return infinitePerspective;
  }
  
  Matrix4 Matrix4::PickMatrix(const Vector2& center, const Vector2& delta, const Vector2& viewportPosition, const Vector2& viewportSize)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 pickMatrix = IDENTITY; // start with an identity matrix
    
    if (!(delta.x > 0 && delta.y > 0)) {
      return pickMatrix;
    }
    
    Vector3 translate((viewportSize.width - 2 * (center.x - viewportPosition.x)) / delta.x,
                      (viewportSize.height - 2 * (center.y - viewportPosition.y)) / delta.y, 0);
    
    Vector3 scale(viewportSize.width / delta.x, viewportSize.height / delta.y, 1);
    
    // Translate and then scale to map the picked region to the viewport
    pickMatrix.data[0] = scale.x;
    pickMatrix.data[5] = scale.y;
    pickMatrix.data[12] = translate.x;
    pickMatrix.data[13] = translate.y;
    
    return pickMatrix;
  }
  
  
  Vector3 Matrix4::Project(const Vector3& obj, const Matrix4& model, const Matrix4& projection, const Vector4& viewport)
  {
    CANDY_PROFILE_FUNCTION();
    // Make obj a 4D point for multiplication with a 4x4 matrix
    Vector4 temp(obj.x, obj.y, obj.z, 1.0f);
    
    // Transform obj by the model matrix
    temp = model * temp;
    
    // Now transform the point from model space to clip space
    temp = projection * temp;
    
    // Perspective division
    if (temp.w != 0) {
      temp.x /= temp.w;
      temp.y /= temp.w;
      temp.z /= temp.w;
    }
    
    // Viewport transformation
    // Map x, y to range 0 - 1 and z to range 0 - 1
    temp.x = temp.x * 0.5f + 0.5f;
    temp.y = temp.y * 0.5f + 0.5f;
    temp.z = temp.z * 0.5f + 0.5f;
    
    // Map x, y to viewport
    temp.x = temp.x * viewport.z + viewport.x;
    temp.y = temp.y * viewport.w + viewport.y;
    
    return Vector3{temp.x, temp.y, temp.z};
  }
  
  
  Vector3 Matrix4::UnProject(const Vector3& windowCoords, const Matrix4& model, const Matrix4& projection, const Vector4& viewport)
  {
    CANDY_PROFILE_FUNCTION();
    // Compute the inverse transform matrix
    Matrix4 inverseTransform = Matrix4::Inverse(projection * model);
    
    // Transfer window coordinates to normalized device coordinates
    Vector4 temp;
    temp.x = (windowCoords.x - viewport.x) / viewport.z * 2.0f - 1.0f;
    temp.y = (windowCoords.y - viewport.y) / viewport.w * 2.0f - 1.0f;
    temp.z = windowCoords.z * 2.0f - 1.0f;
    temp.w = 1.0f;
    
    // Transform the point from normalized device coordinates to object coordinates
    Vector4 objCoords = inverseTransform * temp;
    
    // If the w component is not 0 or near 0,
    // then divide x,y,z components by it to project the point back to 3D object space
    if (Math::Abs(objCoords.w) > 1e-4)
    {
      return Vector3{objCoords.x / objCoords.w, objCoords.y / objCoords.w, objCoords.z / objCoords.w};
    }
    
    // if w component is 0, the point is located on a line directed from the origin through (x/w,y/w,z/w)
    return Vector3{objCoords.x, objCoords.y, objCoords.z};
  }
  
  Matrix4 Matrix4::Transpose(const Matrix4 &matrix)
  {
    CANDY_PROFILE_FUNCTION();
    // Option 1
    Matrix4 result;
    __m128 temp1 = _mm_unpacklo_ps(matrix.m128[0], matrix.m128[1]); // x0,y0,x1,y1
    __m128 temp2 = _mm_unpacklo_ps(matrix.m128[2], matrix.m128[3]); // z0,w0,z1,w1
    __m128 temp3 = _mm_unpackhi_ps(matrix.m128[0], matrix.m128[1]); // x2,y2,x3,y3
    __m128 temp4 = _mm_unpackhi_ps(matrix.m128[2], matrix.m128[3]); // z2,w2,z3,w3
    
    result.m128[0] = _mm_movelh_ps(temp1, temp2); // x0,y0,z0,w0
    result.m128[1] = _mm_movehl_ps(temp2, temp1); // x1,y1,z1,w1
    result.m128[2] = _mm_movelh_ps(temp3, temp4); // x2,y2,z2,w2
    result.m128[3] = _mm_movehl_ps(temp4, temp3); // x3,y3,z3,w3
    
    return result;
    
    /*
    // Option 2
    Matrix4 result = matrix;
    result.data[1] = matrix.data[4];
    result.data[2] = matrix.data[8];
    result.data[3] = matrix.data[12];
    result.data[4] = matrix.data[1];
    result.data[6] = matrix.data[9];
    result.data[7] = matrix.data[13];
    result.data[8] = matrix.data[2];
    result.data[9] = matrix.data[6];
    result.data[11] = matrix.data[14];
    result.data[12] = matrix.data[3];
    result.data[13] = matrix.data[7];
    result.data[14] = matrix.data[11];
    return result;*/
    
  }
  bool Matrix4::DecomposeTransform(const Matrix4 &m, Vector3& translation, Quaternion& rotation, Vector3& scale)
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 localMatrix = m;
    
    // Check if the matrix is not usable
    if (EpsilonEqual(localMatrix.columns[3][3], 0.0f, Epsilon<float>()))
    {
      CANDY_CORE_ERROR("Last element in matrix is 0! Cannot decompose. Column: {0}, element[3][3]: {1}", localMatrix.columns[3], localMatrix.columns[3][3]);
      return false;
    }
    
    
    // Normalize the matrix.
    for (int i = 0; i<4; ++i)
      for (int j = 0; j<4; ++j)
        localMatrix.columns[i][j] /= localMatrix.columns[3][3];
    
    // Extract the translation
    translation = Vector3(localMatrix.columns[3]);
    localMatrix.columns[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Extract column vectors of the matrix
    Vector3 vCols[3] = {Vector3(localMatrix.columns[0]), Vector3(localMatrix.columns[1]), Vector3(localMatrix.columns[2])};
    
    // Compute scaling factors
    scale.x = Vector3::Length(vCols[0]); // length of first column vector
    scale.y = Vector3::Length(vCols[1]); // length of second column vector
    scale.z = Vector3::Length(vCols[2]); // length of third column vector
    
    // Normalise the scale
    if (scale.x == 0 || scale.y == 0 || scale.z == 0)
    {
      CANDY_CORE_ERROR("One of the scale factors is 0! Cannot decompose. Scale: {0}", scale);
      return false;
    }
    
    
    // Remove scaling from matrix
    vCols[0] /= scale.x;
    vCols[1] /= scale.y;
    vCols[2] /= scale.z;
    
    // Extract rotation: the rotation should be represented by the unscaled column vectors
    
    // Recreate rotation matrix without translations
    for (int i = 0; i<3; ++i)
    {
      localMatrix.columns[i][0] = vCols[i].x;
      localMatrix.columns[i][1] = vCols[i].y;
      localMatrix.columns[i][2] = vCols[i].z;
      localMatrix.columns[i][3] = 0.0f;
    }
    
    // Convert to quaternion
    rotation = Quaternion(localMatrix);
    
    return true;
    
  }
  
  
  float Matrix4::Determinant(const Matrix4 &matrix)
  {
    CANDY_PROFILE_FUNCTION();
    float det;
    float subFactor00 = matrix.data[2] * matrix.data[7] - matrix.data[6] * matrix.data[3];
    float subFactor01 = matrix.data[2] * matrix.data[11] - matrix.data[10] * matrix.data[3];
    float subFactor02 = matrix.data[2] * matrix.data[15] - matrix.data[14] * matrix.data[3];
    float subFactor03 = matrix.data[6] * matrix.data[11] - matrix.data[10] * matrix.data[7];
    float subFactor04 = matrix.data[6] * matrix.data[15] - matrix.data[14] * matrix.data[7];
    float subFactor05 = matrix.data[10] * matrix.data[15] - matrix.data[14] * matrix.data[11];
    
    Vector4 detCof(
    +(matrix.data[5] * subFactor05 - matrix.data[9] * subFactor04 + matrix.data[13] * subFactor03),
    -(matrix.data[1] * subFactor05 - matrix.data[9] * subFactor02 + matrix.data[13] * subFactor01),
    +(matrix.data[1] * subFactor04 - matrix.data[5] * subFactor02 + matrix.data[13] * subFactor00),
    -(matrix.data[1] * subFactor03 - matrix.data[5] * subFactor01 + matrix.data[9] * subFactor00)
    );
    
    det = matrix.data[0]*detCof.x + 	matrix.data[4]*detCof.y + 	matrix.data[8]*detCof.z + 	matrix.data[12]*detCof.w;
    
    return det;
  }
  
  
  
  
  Vector4& Matrix4::operator[](int index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index < COLUMNS, "Matrix column index is out of range!");
    return columns[index];
  }
  
  Vector4 Matrix4::operator[](int index)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index < COLUMNS, "Matrix column index is out of range!");
    return columns[index];
  }
  
  
  float& Matrix4::operator[](int row, int column)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(row < ROWS && column < COLUMNS, "Matrix index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  float Matrix4::operator[](int row, int column)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(row < ROWS && column < COLUMNS, "Matrix index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  
  bool Matrix4::operator==(const Matrix4& other)const
  {
    CANDY_PROFILE_FUNCTION();
    int bitmask;
    for (int i = 0; i < 4; i++) {
      __m128 a = m128[i];
      __m128 b = other.m128[i];
      bitmask = _mm_movemask_ps(_mm_cmpeq_ps(a, b));
      if (bitmask != 0xF)  // if not all bits are set, matrices are not equal
        return false;
    }
    return true;
  }
  
  bool Matrix4::operator!=(const Matrix4& other)const
  {
    CANDY_PROFILE_FUNCTION();
    return !((*this)==other);
  }
  
  Vector3 Matrix4::operator*(const Vector3& vec)const
  {
    CANDY_PROFILE_FUNCTION();
    Math::Vector3 result{};
    for (int i=0; i<3; i++)
    {
      result[i] = data[i] * vec.x + data[i+4] * vec.y + data[i+8] * vec.z + data[i+12];
    }
    return result;
  }
  Vector4 Matrix4::operator*(const Vector4& vec)const
  {
    CANDY_PROFILE_FUNCTION();
    Math::Vector4 result{};
    for (int i=0; i<4; i++)
    {
      result[i] = data[i] * vec.x + data[i+4] * vec.y + data[i+8] * vec.z + data[i+12];
    }
    return result;
  }
  
  
  Matrix4 Matrix4::operator*(const Matrix4& other)const
  {
    CANDY_PROFILE_FUNCTION();
    const int N=4;
    Matrix4 result;
    for (int i = 0; i < N; i++) {
      result.m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[i][0]), m128[0]);
      for (int j = 1; j < N; j++) {
        result.m128[i] = _mm_add_ps(result.m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[i][j]), m128[j]));
      }
    }
    
    return result;
  }
  
  void Matrix4::operator+=(const Matrix4& other)
  {
    CANDY_PROFILE_FUNCTION();
    for(int i = 0; i < TOTAL_SIZE; i++)
      data[i] += other.data[i];
  }
  
  void Matrix4::operator-=(const Matrix4& other)
  {
    CANDY_PROFILE_FUNCTION();
    for(int i = 0; i < TOTAL_SIZE; i++)
      data[i] -= other.data[i];
  }
  
  void Matrix4::operator*=(const Matrix4& other)
  {
    CANDY_PROFILE_FUNCTION();
    const int N=4;
    
    for (int i = 0; i < N; i++) {
      m128[i] = _mm_mul_ps(_mm_set1_ps(other.m128[i][0]), m128[0]);
      for (int j = 1; j < N; j++) {
        m128[i] = _mm_add_ps(m128[i], _mm_mul_ps(_mm_set1_ps(other.m128[i][j]), m128[j]));
      }
    }
    
    
  }
  
  float& Matrix4::Entry(int index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index < TOTAL_SIZE, "Matrix index is out of range!");
    return data[index];
  }
  float Matrix4::Entry(int index)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index < TOTAL_SIZE, "Matrix index is out of range!");
    return data[index];
  }
  float& Matrix4::Entry(int row, int column)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(row < ROWS && column < COLUMNS, "Matrix index is out of range!");
    return data[AccessIndex(row, column)];
  }
  float Matrix4::Entry(int row, int column)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(row < ROWS && column < COLUMNS, "Matrix index is out of range!");
    return data[AccessIndex(row, column)];
  }
  
  Vector4& Matrix4::GetColumn(int index)
  {
    CANDY_PROFILE_FUNCTION();
    return columns[index];
  }
  const Vector4& Matrix4::GetColumn(int index)const
  {
    CANDY_PROFILE_FUNCTION();
    return columns[index];
  }
  Vector4 Matrix4::GetRow(int index)const
  {
    CANDY_PROFILE_FUNCTION();
    return {data[index], data[index+4], data[index+8], data[index+12]};
  }
  
  Vector3 Matrix4::GetTranslation()const
  {
    CANDY_PROFILE_FUNCTION();
    return {data[12], data[13], data[14]};
  }
  Vector3 Matrix4::GetScale()const
  {
    CANDY_PROFILE_FUNCTION();
    float sx = Math::Sqrt((*this)[0,0] * (*this)[0,0] + (*this)[0,1] * (*this)[0,1] + (*this)[0,2] * (*this)[0,2]);
    float sy = Math::Sqrt((*this)[1,0] * (*this)[1,0] + (*this)[1,1] * (*this)[1,1] + (*this)[1,2] * (*this)[1,2]);
    float sz = Math::Sqrt((*this)[2,0] * (*this)[2,0] + (*this)[2,1] * (*this)[2,1] + (*this)[2,2] * (*this)[2,2]);
    return {sx, sy, sz};
  }
  Vector3 Matrix4::GetRotation()const
  {
    CANDY_PROFILE_FUNCTION();
    Matrix4 m = *this;
    Vector3 scale = GetScale();
    float sx = scale.x;
    float sy = scale.y;
    float sz = scale.z;
    if (fabsf(sx) > 0.0001f)
    {
      m[0,0] /= sx;
      m[0,1] /= sx;
      m[0,2] /= sx;
    }
    if (fabsf(sy) > 0.0001f)
    {
      m[1,0] /= sy;
      m[1,1] /= sy;
      m[1,2] /= sy;
    }
    if (fabsf(sz) > 0.0001f)
    {
      m[2,0] /= sz;
      m[2,1] /= sz;
      m[2,2] /= sz;
    }

    // Extract the angles from the rotation matrix
    float angle_x = Math::Atan2(m[2,1],m[2,2]);
    float angle_y = Math::Atan2(-m[2,0],Math::Sqrt(m[2,1]*m[2,1]+m[2,2]*m[2,2]));
    float angle_z = Math::Atan2(m[1,0],m[0,0]);
    return {angle_x, angle_y, angle_z};
  }
  
  const float* Matrix4::Data()const
  {
    return data.data();
  }
  float* Matrix4::Data()
  {
    return data.data();
  }

}