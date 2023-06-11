#include "Matrix4.hpp"
#include "../../../../include/Candy/Math.hpp"
#include <xmmintrin.h>

namespace Candy::Math{
    
        Matrix4::Matrix4()  {
            data.fill(0);
        }
        
        Matrix4::Matrix4(std::initializer_list<float> elements) {
            int count=0;
            for (float element : elements)
            {
                data[count]=element;
                count++;
            }
        }
        Matrix4::Matrix4(const Matrix4& other)
        {
            for (int i=0; i<other.data.size(); i++)
            {
                data[i] = other.data[i];
            }
            
        }
        
        Matrix4::Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3)
        {
            data[0]=column0.x;
            data[1]=column0.y;
            data[2]=column0.z;
            data[3]=column0.w;
            
            data[4]=column1.x;
            data[5]=column1.y;
            data[6]=column1.z;
            data[7]=column1.w;
            
            data[8]=column2.x;
            data[9]=column2.y;
            data[10]=column2.z;
            data[11]=column2.w;
            
            data[12]=column3.x;
            data[13]=column3.y;
            data[14]=column3.z;
            data[15]=column3.w;
            
            
        }
        
        Matrix4::Matrix4(float diagonal)
        {
            data.fill(0);
            data[0] = diagonal;
            data[5] = diagonal;
            data[10] =diagonal;
            data[15] =diagonal;
        }
        
        Matrix4::Matrix4(const Vector4& value)
        {
            data.fill(0);
            data[0] = value.x;
            data[5] = value.y;
            data[10] =value.z;
            data[15] =value.w;
        }
        
        Matrix4 Matrix4::Diagonal(float value)
        {
            Matrix4 result;
            
            result[0] = value;
            result[5] = value;
            result[10] =value;
            result[15] =value;
            return result;
        }
        
        Matrix4 Matrix4::Diagonal(const Vector4& value)
        {
            Matrix4 result;
            result[0] = value.x;
            result[5] = value.y;
            result[10] =value.z;
            result[15] =value.w;
            return result;
            
        }
        
        Matrix4 Matrix4::Diagonal(float v0, float v1, float v2, float v3)
        {
            Matrix4 result;
            result[0] = v0;
            result[5] = v1;
            result[10] = v2;
            result[15] = v3;
            return result;
        }
        
        const Matrix4 Matrix4::Identity=Diagonal(1.0f);
        
        Matrix4 Matrix4::Eye() {
            return Identity;
        }
        
        
        Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
            Matrix4 result;
            float tx = - (right + left) / (right - left);
            float ty = - (top + bottom) / (top - bottom);
            float tz = - (far + near) / (far - near);
            return Matrix4(2.0f / (right - left), 0.0f, 0.0f, 0.0f,
                           0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
                           0.0f, 0.0f, -2.0f / (far - near), 0.0f,
                           tx, ty, tz, 1.0f);
        }
        
        Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far) {
            float f = 1.0f / Tan(fov / 2.0f);
            float zRange = near - far;
            
            return Matrix4(
                    f / aspectRatio, 0.0f, 0.0f, 0.0f,
                    0.0f, f, 0.0f, 0.0f,
                    0.0f, 0.0f, (far + near) / zRange, -1.0f,
                    0.0f, 0.0f, 2.0f * far * near / zRange, 0.0f);
            
            
        }
        
        Matrix4 Matrix4::LookAt(const Vector3 &camera, const Vector3 &object, const Vector3 &up) {
            Vector3 zaxis = Vector3::Normalize(camera - object);
            Vector3 xaxis = Vector3::Cross(up, zaxis).Normalized();
            Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
            
            Matrix4 result;
            result[0] = xaxis.x;
            result[1] = yaxis.x;
            result[2] = zaxis.x;
            result[4] = xaxis.y;
            result[5] = yaxis.y;
            result[6] = zaxis.y;
            result[8] = xaxis.z;
            result[9] = yaxis.z;
            result[10] = zaxis.z;
            result[12] = -xaxis.Dot(camera);
            result[13] = -yaxis.Dot(camera);
            result[14] = -zaxis.Dot(camera);
            result[15] = 1;
            
            return result;
        }
        
        
        Matrix4 Matrix4::Translation(const Vector3 &translation) {
            Matrix4 result;
            result[0] = 1;
            result[5] = 1;
            result[10] = 1;
            result[12] = translation.x;
            result[13] = translation.y;
            result[14] = translation.z;
            result[15] = 1;
            
            return result;
            
            return result;
        }
        
        Matrix4 Matrix4::Rotated(float angle, const Vector3 &axis) {
            float c = std::cos(angle);
            float s = std::sin(angle);
            float t = 1.0f - c;
            
            Vector3 naxis = axis.Normalized();
            
            Matrix4 result;
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
        
        Matrix4 Matrix4::Rotated(const Quaternion &quaternion) {
            float xx = quaternion.x * quaternion.x;
            float xy = quaternion.x * quaternion.y;
            float xz = quaternion.x * quaternion.z;
            float xw = quaternion.x * quaternion.w;
            float yy = quaternion.y * quaternion.y;
            float yz = quaternion.y * quaternion.z;
            float yw = quaternion.y * quaternion.w;
            float zz = quaternion.z * quaternion.z;
            float zw = quaternion.z * quaternion.w;
            
            Matrix4 result;
            result[0] = 1 - 2 * (yy + zz);
            result[1] = 2 * (xy - zw);
            result[2] = 2 * (xz + yw);
            result[4] = 2 * (xy + zw);
            result[5] = 1 - 2 * (xx + zz);
            result[6] = 2 * (yz - xw);
            result[8] = 2 * (xz - yw);
            result[9] = 2 * (yz + xw);
            result[10] = 1 - 2 * (xx + yy);
            result[15] = 1;
            
            return result;
        }
        
        Matrix4 Matrix4::Rotated(const Matrix4 &matrix, float angle, const Vector3 &axis) {
            return Rotated(angle, axis)*matrix;
        }
        
        
        Matrix4 Matrix4::Scaled(const Vector3 &scale) {
            Matrix4 result(1.0f);
            
            result[0] = scale.x;
            result[5] = scale.y;
            result[10] = scale.z;
            return result;
        }
        
        Matrix4 Matrix4::Scaled(const Matrix4 &mat, const Vector3 &scale) {
            return Scaled(scale) * mat;
        }
        
        Matrix4 Matrix4::Invert(const Matrix4 &matrix) {
            Matrix4 result = matrix;
            return result.Invert();
        }
        
        Matrix4 Matrix4::CreateFromRows(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3)
        {
            return Matrix4(Vector4(r0.x, r1.x, r2.x, r3.x), Vector4(r0.y, r1.y, r2.y, r3.y), Vector4(r0.z, r1.z, r2.z, r3.z), Vector4(r0.w, r1.w, r2.w, r3.w));
        }
        
        Matrix4 Matrix4::CreateFromColumns(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3)
        {
            return Matrix4(c0, c1, c2, c3);
        }
        
        Matrix4 Matrix4::Transpose(const Matrix4 &matrix)
        {
            Matrix4 result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result[j,i] = matrix[i,j];
                }
            }
            return result;
        }
    
        bool Matrix4::DecomposeTransform(const Matrix4& transform, Vector3& translation, Vector3& rotation, Vector3& scale)
        {
            
            Matrix4 localMatrix(transform);
            
            // Normalize the matrix.
            if (EpsilonEqual(localMatrix[3,3], static_cast<float>(0), std::numeric_limits<float>::epsilon()))
                return false;
            
            // First, isolate perspective.  This is the messiest.
            if (
                    EpsilonNotEqual(localMatrix[0,3], static_cast<float>(0), std::numeric_limits<float>::epsilon()) ||
                    EpsilonNotEqual(localMatrix[1,3], static_cast<float>(0), std::numeric_limits<float>::epsilon()) ||
                    EpsilonNotEqual(localMatrix[2,3], static_cast<float>(0), std::numeric_limits<float>::epsilon()))
            {
                // Clear the perspective partition
                localMatrix[0,3] = localMatrix[1,3] = localMatrix[2,3] = static_cast<float>(0);
                localMatrix[3,3] = static_cast<float>(1);
            }
            
            // Next take care of translation (easy).
            translation = localMatrix.GetColumn(3);
            localMatrix.SetColumn(3, Vector4(0, 0, 0, localMatrix.GetColumn(3).w));
            
            
            Vector3 row[3], pdum3;
            
            // Now get scale and shear.
            for (std::size_t i = 0; i < 3; ++i)
                for (std::size_t j = 0; j < 3; ++j)
                    row[i][j] = localMatrix[i,j];
            
            // Compute X scale factor and normalize first row.
            
            scale.x = row[0].Magnitude();
            row[0].Normalize();
            scale.y = row[1].Magnitude();
            row[1].Normalize();
            scale.z = row[2].Magnitude();
            row[2].Normalize();
            
            // At this point, the matrix (in rows[]) is orthonormal.
            // Check for a coordinate system flip.  If the determinant
            // is -1, then negate the matrix and the scaling factors.
#if 0
            pdum3 = cross(row[1], row[2]); // v3Cross(row[1], row[2], pdum3);
		if (dot(row[0], pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				row[i] *= static_cast<T>(-1);
			}
		}
#endif
            
            rotation.y = Math::Asin(-row[0][2]);
            if (cos(rotation.y) != 0) {
                rotation.x = Math::Atan2(row[1][2], row[2][2]);
                rotation.z = Math::Atan2(row[0][1], row[0][0]);
            }
            else {
                rotation.x = Math::Atan2(-row[2][0], row[1][1]);
                rotation.z = 0;
            }
            
            
            return true;
        }
    
        bool Matrix4::EpsilonEqual(float x, float y, float epsilon)
        {
            return Math::Abs(x-y) < epsilon;
        }
        bool Matrix4::EpsilonNotEqual(float x, float y, float epsilon)
        {
            return Math::Abs(x-y) >= epsilon;
        }
        
        Matrix4 Matrix4::operator+(const Matrix4& other)const
        {
            Matrix4 result;
            for (int i=0; i<16; i++)
            {
                result.data[i] = data[i]+other.data[i];
            }
            return result;
        }
        Matrix4 Matrix4::operator-(const Matrix4& other)const
        {
            Matrix4 result;
            for (int i=0; i<16; i++)
            {
                result.data[i] = data[i]-other.data[i];
            }
            return result;
        }
        
        
        Matrix4 Matrix4::operator*(const Matrix4 &other) const {
            const int N=4;
            Matrix4 result;
            for (int i = 0; i < N; i++) {
                result.matrix[i] = _mm_mul_ps(_mm_set1_ps(other.matrix[i][0]), matrix[0]);
                for (int j = 1; j < N; j++) {
                    result.matrix[i] = _mm_add_ps(result.matrix[i], _mm_mul_ps(_mm_set1_ps(other.matrix[i][j]), matrix[j]));
                }
            }
            
            return result;
        }
        
        Vector3 Matrix4::operator*(const Vector3& other)const
        {
            return Vector3(data[0] * other.x + data[1] * other.y + data[2] * other.z + data[3],
                           data[4] * other.x + data[5] * other.y + data[6] * other.z + data[7],
                           data[8] * other.x + data[9] * other.y + data[10] * other.z + data[11]);
            
        }
        Vector4 Matrix4::operator*(const Vector4& other)const
        {
            return Vector4(data[0] * other.x + data[1] * other.y + data[2] * other.z + data[3] * other.w,
                           data[4] * other.x + data[5] * other.y + data[6] * other.z + data[7] * other.w,
                           data[8] * other.x + data[9] * other.y + data[10] * other.z + data[11] * other.w,
                           data[12] * other.x + data[13] * other.y + data[14] * other.z + data[15] * other.w);
        }
        
        
        
        
        std::ostream &operator<<(std::ostream &ostream, const Matrix4 &mat) {
            
            ostream << std::fixed << std::setprecision(1);
            ostream << mat.data[0] << ", " << mat.data[4] << ", " << mat.data[8] << ", " << mat.data[12] << "\n";
            ostream << mat.data[1] << ", " << mat.data[5] << ", " << mat.data[9] << ", " << mat.data[13] << "\n";
            ostream << mat.data[2] << ", " << mat.data[6] << ", " << mat.data[10] << ", " << mat.data[14] << "\n";
            ostream << mat.data[3] << ", " << mat.data[7] << ", " << mat.data[11] << ", " << mat.data[15] << "\n";
            
            
            return ostream;
        }
        
        
        void Matrix4::SetRow(unsigned int index, const Vector4 &row) {
            Entry(index, 0) = row.x;
            Entry(index, 1) = row.y;
            Entry(index, 2) = row.z;
            Entry(index, 3) = row.w;
            
        }
        
        void Matrix4::SetColumn(unsigned int index, const Vector4 &column) {
            columns[index]=column;
            /*data[index] = column.x;
            data[index + 1] = column.y;
            data[index + 2] = column.z;
            data[index + 3] = column.w;*/
        }
        
        void Matrix4::SetPosition(const Vector3 &position) {
            SetColumn(3, Vector4(position, 1.0f));
        }
        
        Vector4 Matrix4::GetRow(int index) const {
            return Vector4(data[index], data[index + 4], data[index + 8], data[index + 12]);
        }
        
        Vector4 Matrix4::GetColumn(int index) const {
            return columns[index];
            //return Vector4(data[index], data[index+1], data[index+2], data[index+3]);
        }
        
        Vector3 Matrix4::GetPosition() const {
            return Vector3(GetColumn(3));
        }
        
        void Matrix4::Translate(const Vector3 &offset) {
            data[12] = offset.x;
            data[13] = offset.y;
            data[14] = offset.z;
        }
        
        void Matrix4::Scale(const Vector3 &scale) {
            Entry(0) = scale.x;
            Entry(5) = scale.y;
            Entry(10) = scale.z;
            
        }
        
        
        
        void Matrix4::RotateX(float angle) {
            (*this)[1, 1] = Cos(angle);
            (*this)[2, 1] = -Sin(angle);
            (*this)[1, 2] = Sin(angle);
            (*this)[2, 2] = Cos(angle);
        }
        
        void Matrix4::RotateY(float angle) {
            (*this)[0, 0] = Cos(angle);
            (*this)[0, 2] = -Sin(angle);
            (*this)[2, 0] = Sin(angle);
            (*this)[2, 2] = Cos(angle);
            
        }
        
        void Matrix4::RotateZ(float angle) {
            (*this)[0, 0] = Cos(angle);
            (*this)[0, 1] = Sin(angle);
            (*this)[1, 0] = -Sin(angle);
            (*this)[1, 1] = Cos(angle);
            
        }
        
        
        Matrix4 &Matrix4::Invert() {
            float temp[16];
            
            temp[0] = data[5] * data[10] * data[15] -
                      data[5] * data[11] * data[14] -
                      data[9] * data[6] * data[15] +
                      data[9] * data[7] * data[14] +
                      data[13] * data[6] * data[11] -
                      data[13] * data[7] * data[10];
            
            temp[4] = -data[4] * data[10] * data[15] +
                      data[4] * data[11] * data[14] +
                      data[8] * data[6] * data[15] -
                      data[8] * data[7] * data[14] -
                      data[12] * data[6] * data[11] +
                      data[12] * data[7] * data[10];
            
            temp[8] = data[4] * data[9] * data[15] -
                      data[4] * data[11] * data[13] -
                      data[8] * data[5] * data[15] +
                      data[8] * data[7] * data[13] +
                      data[12] * data[5] * data[11] -
                      data[12] * data[7] * data[9];
            
            temp[12] = -data[4] * data[9] * data[14] +
                       data[4] * data[10] * data[13] +
                       data[8] * data[5] * data[14] -
                       data[8] * data[6] * data[13] -
                       data[12] * data[5] * data[10] +
                       data[12] * data[6] * data[9];
            
            temp[1] = -data[1] * data[10] * data[15] +
                      data[1] * data[11] * data[14] +
                      data[9] * data[2] * data[15] -
                      data[9] * data[3] * data[14] -
                      data[13] * data[2] * data[11] +
                      data[13] * data[3] * data[10];
            
            temp[5] = data[0] * data[10] * data[15] -
                      data[0] * data[11] * data[14] -
                      data[8] * data[2] * data[15] +
                      data[8] * data[3] * data[14] +
                      data[12] * data[2] * data[11] -
                      data[12] * data[3] * data[10];
            
            temp[9] = -data[0] * data[9] * data[15] +
                      data[0] * data[11] * data[13] +
                      data[8] * data[1] * data[15] -
                      data[8] * data[3] * data[13] -
                      data[12] * data[1] * data[11] +
                      data[12] * data[3] * data[9];
            
            temp[13] = data[0] * data[9] * data[14] -
                       data[0] * data[10] * data[13] -
                       data[8] * data[1] * data[14] +
                       data[8] * data[2] * data[13] +
                       data[12] * data[1] * data[10] -
                       data[12] * data[2] * data[9];
            
            temp[2] = data[1] * data[6] * data[15] -
                      data[1] * data[7] * data[14] -
                      data[5] * data[2] * data[15] +
                      data[5] * data[3] * data[14] +
                      data[13] * data[2] * data[7] -
                      data[13] * data[3] * data[6];
            
            temp[6] = -data[0] * data[6] * data[15] +
                      data[0] * data[7] * data[14] +
                      data[4] * data[2] * data[15] -
                      data[4] * data[3] * data[14] -
                      data[12] * data[2] * data[7] +
                      data[12] * data[3] * data[6];
            
            temp[10] = data[0] * data[5] * data[15] -
                       data[0] * data[7] * data[13] -
                       data[4] * data[1] * data[15] +
                       data[4] * data[3] * data[13] +
                       data[12] * data[1] * data[7] -
                       data[12] * data[3] * data[5];
            
            temp[14] = -data[0] * data[5] * data[14] +
                       data[0] * data[6] * data[13] +
                       data[4] * data[1] * data[14] -
                       data[4] * data[2] * data[13] -
                       data[12] * data[1] * data[6] +
                       data[12] * data[2] * data[5];
            
            temp[3] = -data[1] * data[6] * data[11] +
                      data[1] * data[7] * data[10] +
                      data[5] * data[2] * data[11] -
                      data[5] * data[3] * data[10] -
                      data[9] * data[2] * data[7] +
                      data[9] * data[3] * data[6];
            
            temp[7] = data[0] * data[6] * data[11] -
                      data[0] * data[7] * data[10] -
                      data[4] * data[2] * data[11] +
                      data[4] * data[3] * data[10] +
                      data[8] * data[2] * data[7] -
                      data[8] * data[3] * data[6];
            
            temp[11] = -data[0] * data[5] * data[11] +
                       data[0] * data[7] * data[9] +
                       data[4] * data[1] * data[11] -
                       data[4] * data[3] * data[9] -
                       data[8] * data[1] * data[7] +
                       data[8] * data[3] * data[5];
            
            temp[15] = data[0] * data[5] * data[10] -
                       data[0] * data[6] * data[9] -
                       data[4] * data[1] * data[10] +
                       data[4] * data[2] * data[9] +
                       data[8] * data[1] * data[6] -
                       data[8] * data[2] * data[5];
            
            float determinant = data[0] * temp[0] + data[1] * temp[4] + data[2] * temp[8] + data[3] * temp[12];
            determinant = 1.0f / determinant;
            
            for (int i = 0; i < 4 * 4; i++)
                data[i] = temp[i] * determinant;
            
            return *this;
        }
        
        void Matrix4::PrintFlat()const
        {
            for (int i=0; i<TOTAL_SIZE; i++)
            {
                std::cout << std::fixed << std::setprecision(1) << data[i] << ", ";
            }
        }
}