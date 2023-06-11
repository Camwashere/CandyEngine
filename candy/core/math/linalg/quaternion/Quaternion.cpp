#include "Quaternion.hpp"
#include "../../../../include/Candy/Math.hpp"
namespace Candy::Math{
        
        
        Quaternion::Quaternion() : VectorBase<float, 4>(0, 0, 0, 1) {}
        
        Quaternion::Quaternion(const Quaternion &quaternion) = default;
        
        Quaternion::Quaternion(float x, float y, float z, float w) : VectorBase<float, 4>(x, y, z, w){}
        
        Quaternion::Quaternion(const Vector3 &xyz, float w) : VectorBase<float, 4>(xyz.x, xyz.y, xyz.z, w) {}
        
        Quaternion::Quaternion(const Vector4 &vec) : VectorBase<float, 4>(vec) {}
        
        Quaternion::Quaternion(float scalar) : VectorBase<float, 4>(scalar) {}
        
        const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1.0f);
        
        Vector3 Quaternion::GetVector3() const {
            return {x, y, z};
        }
        
        Matrix4 Quaternion::ToMatrix() const {
            Matrix4 result(0.0f);
            float sqw = w * w;
            float sqx = x * x;
            float sqy = y * y;
            float sqz = z * z;
            
            // invs (inverse square length) is only required if quaternion is not already normalised
            float invs = 1 / (sqx + sqy + sqz + sqw);
            result[0] = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
            result[5] = (-sqx + sqy - sqz + sqw) * invs;
            result[10] = (-sqx - sqy + sqz + sqw) * invs;
            
            double tmp1 = x * y;
            double tmp2 = z * w;
            result[1] = 2.0 * (tmp1 + tmp2) * invs;
            result[4] = 2.0 * (tmp1 - tmp2) * invs;
            
            tmp1 = x * z;
            tmp2 = y * w;
            result[3] = 2.0 * (tmp1 - tmp2) * invs;
            result[8] = 2.0 * (tmp1 + tmp2) * invs;
            tmp1 = y * z;
            tmp2 = x * w;
            result[6] = 2.0 * (tmp1 + tmp2) * invs;
            result[9] = 2.0 * (tmp1 - tmp2) * invs;
            return result;
        }
        
        Vector3 Quaternion::GetAxis() const {
            float x1 = 1.0f - w * w;
            if (x1 < 0.0000001f) {
                return Vector3::right;
            }
            float x2 = x1 * x1;
            return GetVector3() / x2;
        }
        
        Vector3 Quaternion::ToEulerAngles() const {
            return Vector3(Atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
                           Atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
                           Asin(2 * x * y + 2 * z * w));
        }
        
        float Quaternion::Norm() const {
            float result;
            result = (x * x);
            result = (result + (y * y));
            result = (result + (z * z));
            result = (result + (w * w));
            return result;
        }
        
        Quaternion Quaternion::Normalized() const {
            float lenSqr, lenInv;
            lenSqr = Norm();
            lenInv = 1.0f / Sqrt(lenSqr);
            return *this * lenInv;
        }
        
        Quaternion Quaternion::NormalizedEst() const {
            float lenSqr, lenInv;
            lenSqr = Norm();
            lenInv = 1.0f / Sqrt(lenSqr);
            return *this * lenInv;
        }
        
        void Quaternion::Normalize() {
            float lenSqr, lenInv;
            lenSqr = Norm();
            lenInv = 1.0f / Sqrt(lenSqr);
            *this = *this * lenInv;
        }
        
        
        
        float &Quaternion::operator[](int index) {
            return *(&x + index);
        }
        
        float Quaternion::operator[](int index) const {
            return *(&x + index);
        }
    
    void Quaternion::operator+=(const Quaternion &other)
    {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
    }
    void Quaternion::operator-=(const Quaternion &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }
    void Quaternion::operator*=(const Quaternion &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
    }
    void Quaternion::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }
    void Quaternion::operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }
    
    Quaternion Quaternion::operator-() const
    {
            return Quaternion(-x, -y, -z, -w);
    }
        
        bool Quaternion::operator==(const Quaternion &quaternion) const {
            return (x == quaternion.x) && (y == quaternion.y) && (z == quaternion.z) && (w == quaternion.w);
        }
        
        bool Quaternion::operator!=(const Quaternion &quaternion) const {
            return !(*this == quaternion);
        }
        
        
        Quaternion Quaternion::FromEulerAngles(const Vector3 &angles) {
            Quaternion pitch(Vector3::right, angles.x);
            Quaternion yaw(Vector3::up, angles.y);
            Quaternion roll(Vector3::forward, angles.z);
            return pitch * yaw * roll;
        }
        
        Vector3 Quaternion::Rotate(const Quaternion &quat, const Vector3 &vec) {
            float tmpX, tmpY, tmpZ, tmpW;
            tmpX = (((quat.w * vec.x) + (quat.y * vec.z)) - (quat.z * vec.y));
            tmpY = (((quat.w * vec.y) + (quat.z * vec.x)) - (quat.x * vec.z));
            tmpZ = (((quat.w * vec.z) + (quat.x * vec.y)) - (quat.y * vec.x));
            tmpW = (((quat.x * vec.x) + (quat.y * vec.y)) + (quat.z * vec.z));
            return Vector3(
                    ((((tmpW * quat.x) + (tmpX * quat.w)) - (tmpY * quat.z)) + (tmpZ * quat.y)),
                    ((((tmpW * quat.y) + (tmpY * quat.w)) - (tmpZ * quat.x)) + (tmpX * quat.z)),
                    ((((tmpW * quat.z) + (tmpZ * quat.w)) - (tmpX * quat.y)) + (tmpY * quat.x))
            );
        }
        
         Quaternion Quaternion::Rotation(const Vector3 &unitVec0, const Vector3 &unitVec1) {
            float cosHalfAngleX2, recipCosHalfAngleX2;
            cosHalfAngleX2 = Sqrt((2.0f * (1.0f + unitVec0.Dot(unitVec1))));
            recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
            return Quaternion((unitVec0.Cross(unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
        }
        
        Quaternion Quaternion::Rotation(float radians, const Vector3 &unitVec) {
            float angle = radians * 0.5f;
            return Quaternion((unitVec * Sin(angle)), Cos(angle));
        }
    
    Quaternion Quaternion::RotationX(float radians) {
        float angle = radians * 0.5f;
        return Quaternion(Sin(angle), 0.0f, 0.0f, Cos(angle));
    }
    
    Quaternion Quaternion::RotationY(float radians) {
        float angle = radians * 0.5f;
        return Quaternion(0.0f, Sin(angle), 0.0f, Cos(angle));
    }
    
    Quaternion Quaternion::RotationZ(float radians) {
        float angle = radians * 0.5f;
        return Quaternion(0.0f, 0.0f, Sin(angle), Cos(angle));
    }
    
    Quaternion Quaternion::ToRadians(const Quaternion& vec)
    {
        return {Math::ToRadians(vec.x), Math::ToRadians(vec.y), Math::ToRadians(vec.z), Math::ToRadians(vec.w)};
    }
    Quaternion Quaternion::ToDegrees(const Quaternion& vec)
    {
        return {Math::ToDegrees(vec.x), Math::ToDegrees(vec.y), Math::ToDegrees(vec.z), Math::ToDegrees(vec.w)};
    }
        
        float Quaternion::Dot(const Quaternion &other) const {
            float result = (x * other.x);
            result = (result + (y * other.y));
            result = (result + (z * other.z));
            result = (result + (w * other.w));
            return result;
        }
        
        Quaternion Quaternion::Conjugate() const {
            return Quaternion(-x, -y, -z, w);
        }
}
