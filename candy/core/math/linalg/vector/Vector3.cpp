#include "Vector3.hpp"
#include "../../../../include/Candy/Math.hpp"


namespace Candy::Math{
        
        
        Vector3::Vector3() : VectorBase<float, 3>(0, 0, 0) {}
        
        Vector3::Vector3(const Vector2 &vec, float zValue) : VectorBase<float, 3>(vec.x, vec.y, zValue) {}
        
        Vector3::Vector3(float value) : VectorBase<float, 3>(value) {}
        
        Vector3::Vector3(const Vector3 &other) : VectorBase<float, 3>(other.x, other.y, other.z) {}
        
        Vector3::Vector3(const Vector2 &other) : VectorBase<float, 3>(other.x, other.y, 0) {}
        
        Vector3::Vector3(const Vector4 &other) : VectorBase<float, 3>(other.x, other.y, other.z) {}
        
        
        const Vector3 Vector3::up(0, 1, 0);
        const Vector3 Vector3::down(0, -1, 0);
        const Vector3 Vector3::left(-1, 0, 0);
        const Vector3 Vector3::right(1, 0, 0);
        const Vector3 Vector3::forward(0, 0, 1);
        const Vector3 Vector3::back(0, 0, -1);
        const Vector3 Vector3::upLeft(-1, 1, 0);
        const Vector3 Vector3::upRight(1, 1, 0);
        const Vector3 Vector3::upForward(0, 1, 1);
        const Vector3 Vector3::upBack(0, 1, -1);
        const Vector3 Vector3::leftBack(-1, 0, -1);
        const Vector3 Vector3::rightBack(1, 0, -1);
        const Vector3 Vector3::leftForward(-1, 0, 1);
        const Vector3 Vector3::rightForward(1, 0, 1);
        const Vector3 Vector3::upLeftForward(-1, 1, 1);
        const Vector3 Vector3::upLeftBack(-1, 1, -1);
        const Vector3 Vector3::upRightForward(1, 1, 1);
        const Vector3 Vector3::upRightBack(1, 1, -1);
        const Vector3 Vector3::downLeft(-1, -1, 0);
        const Vector3 Vector3::downRight(1, -1, 0);
        const Vector3 Vector3::downForward(0, -1, 1);
        const Vector3 Vector3::downBack(0, -1, -1);
        const Vector3 Vector3::downLeftForward(-1, -1, 1);
        const Vector3 Vector3::downLeftBack(-1, -1, -1);
        const Vector3 Vector3::downRightForward(1, -1, 1);
        const Vector3 Vector3::downRightBack(1, -1, -1);
        const Vector3 Vector3::zero(0, 0, 0);
        const Vector3 Vector3::one(1, 1, 1);
        const Vector3 Vector3::negativeOne(-1, -1, -1);
        const Vector3 Vector3::positiveInfinity(std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity());
        const Vector3 Vector3::negativeInfinity(-std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity());
        
        
        bool Vector3::operator==(const Vector3 &other) const {
            return x == other.x && y == other.y && z == other.z;
        }
        
        bool Vector3::operator!=(const Vector3 &other) const {
            return !(x == other.x && y == other.y && z == other.z);
        }
        
        /*Vector3 Vector3::operator+(const Vector3 &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vector3 Vector3::operator-(const Vector3 &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }*/
        
        /*Vector3 Vector3::operator*(const Vector3 &other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        Vector3 Vector3::operator/(const Vector3 &other) const {
            return {x / other.x, y / other.y, z / other.z};
        }*/
        
        Vector3 Vector3::operator^(const Vector3 &other) const {
            return {Math::Pow(x, other.x), Math::Pow(y, other.y), Math::Pow(z, other.z)};
        }
        
        /*Vector3 Vector3::operator*(float scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }*/
        /*Vector3 Vector3::operator/(float scalar) const {
            return {x / scalar, y / scalar, z / scalar};
        }*/
        
        Vector3 Vector3::operator^(float scalar) const {
            return {Math::Pow(x, scalar), Math::Pow(y, scalar), Math::Pow(z, scalar)};
        }
        
        void Vector3::operator+=(const Vector3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }
        
        void Vector3::operator-=(const Vector3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }
        
        void Vector3::operator*=(const Vector3 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
        }
        
        void Vector3::operator/=(const Vector3 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
        }
        
        
        void Vector3::operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }
        
        void Vector3::operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        
        float *Vector3::CombineToArray(const Vector2 &other) const {
            return new float[5]{x, y, z, other.x, other.y};
        }
        
        void Vector3::Set(float value) {
            x = value;
            y = value;
            z = value;
        }
        
        void Vector3::Set(float xValue, float yValue, float zValue) {
            x = xValue;
            y = yValue;
            z = zValue;
        }
        
        void Vector3::Set(const Vector2 &vec) {
            x = vec.x;
            y = vec.y;
            z = 0;
        }
        
        void Vector3::Set(const Vector3 &vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }
        
        void Vector3::Set(const Vector4 &vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }
        
        void Vector3::Normalize() {
            float mag = Magnitude();
            x /= mag;
            y /= mag;
            z /= mag;
        }
        
        Vector3 Vector3::Normalized() const {
            float mag = Magnitude();
            return {x / mag, y / mag, z / mag};
        }
        
        float Vector3::Magnitude() const {
            return Math::Sqrt(x * x + y * y + z * z);
        }
        
        float Vector3::SqrMagnitude() const {
            return x * x + y * y + z * z;
        }
        
        Vector3::operator Vector2() const {
            return {x, y};
        }
        
        Vector3::operator Vector4() const {
            return {x, y, 0, 0};
        }
        
        Vector3::operator std::string() const {
            return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ')';
        }
        
        
        std::ostream &Vector3::operator<<(std::ostream &ostream) const {
            ostream << '(' << x << ',' << y << ',' << z << ')';
            return ostream;
        }
        
        std::ostream &operator<<(std::ostream &ostream, const Vector3 &vec) {
            ostream << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
            return ostream;
        }
        
        /*Vector3 operator*(float scalar, const Vector3 &vec) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
        }*/
        
        /*Vector3 operator/(float scalar, const Vector3 &vec) {
            return {scalar / vec.x, scalar / vec.y, scalar / vec.z};
        }*/
        
        Vector3 operator^(float scalar, const Vector3 &vec) {
            return {Math::Pow(scalar, vec.x), Math::Pow(scalar, vec.y), Math::Pow(scalar, vec.z)};
        }
        
        void Vector3::Clamp(float min, float max) {
            x = Math::Clamp(x, min, max);
            y = Math::Clamp(y, min, max);
            z = Math::Clamp(z, min, max);
        }
        
        void Vector3::Clamp(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
            x = Math::Clamp(x, xMin, xMax);
            y = Math::Clamp(y, yMin, yMax);
            z = Math::Clamp(z, zMin, zMax);
            
        }
        
        void Vector3::Clamp(const Vector3 &min, const Vector3 &max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
            z = Math::Clamp(z, min.z, max.z);
        }
        
        void Vector3::ScaleToLength(float newLength) {
            Normalize();
            *this *= newLength;
        }
        
        Vector3 Vector3::Clamped(float valueMin, float valueMax) const {
            return {Math::Clamp(x, valueMin, valueMax), Math::Clamp(y, valueMin, valueMax),
                    Math::Clamp(z, valueMin, valueMax)};
        }
        
        Vector3 Vector3::Clamped(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const {
            return {Math::Clamp(x, xMin, xMax), Math::Clamp(y, yMin, yMax), Math::Clamp(z, zMin, zMax)};
        }
        
        Vector3 Vector3::Clamped(const Vector3 &min, const Vector3 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z)};
        }
        
        
        bool Vector3::InRangeInclusive(float minValue, float maxValue) const {
            if (x < minValue || x > maxValue) {
                return false;
            }
            if (y < minValue || y > maxValue) {
                return false;
            }
            return !(z < minValue || z > maxValue);
        }
        
        bool Vector3::InRangeInclusive(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const {
            if (x < xMin || x > xMax) {
                return false;
            }
            if (y < yMin || y > yMax) {
                return false;
            }
            return !(z < zMin || z > zMax);
        }
        
        bool Vector3::InRangeInclusive(const Vector3 &min, const Vector3 &max) const {
            if (x < min.x || x > max.x) {
                return false;
            }
            if (y < min.y || y > max.y) {
                return false;
            }
            return !(z < min.z || z > max.z);
        }
        
        
        bool Vector3::InRangeInclusiveMin(float minValue, float maxValue) const {
            if (x < minValue || x >= maxValue) {
                return false;
            }
            if (y < minValue || y >= maxValue) {
                return false;
            }
            return !(z < minValue || z >= maxValue);
        }
        
        bool
        Vector3::InRangeInclusiveMin(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const {
            if (x < xMin || x >= xMax) {
                return false;
            }
            if (y < yMin || y >= yMax) {
                return false;
            }
            return !(z < zMin || z >= zMax);
        }
        
        bool Vector3::InRangeInclusiveMin(const Vector3 &min, const Vector3 &max) const {
            if (x < min.x || x >= max.x) {
                return false;
            }
            if (y < min.y || y >= max.y) {
                return false;
            }
            return !(z < min.z || z >= max.z);
        }
        
        
        bool Vector3::InRangeInclusiveMax(float minValue, float maxValue) const {
            if (x <= minValue || x > maxValue) {
                return false;
            }
            if (y <= minValue || y > maxValue) {
                return false;
            }
            return !(z <= minValue || z > maxValue);
        }
        
        bool
        Vector3::InRangeInclusiveMax(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const {
            if (x <= xMin || x > xMax) {
                return false;
            }
            if (y <= yMin || y > yMax) {
                return false;
            }
            return !(z <= zMin || z > zMax);
        }
        
        bool Vector3::InRangeInclusiveMax(const Vector3 &min, const Vector3 &max) const {
            if (x <= min.x || x > max.x) {
                return false;
            }
            if (y <= min.y || y > max.y) {
                return false;
            }
            return !(z <= min.z || z > max.z);
        }
        
        
        bool Vector3::InRangeExclusive(float minValue, float maxValue) const {
            if (x > minValue && x < maxValue) {
                if (y > minValue && y < maxValue) {
                    return z > minValue && z < maxValue;
                }
            }
            return false;
        }
        
        bool Vector3::InRangeExclusive(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const {
            if (x > xMin && x < xMax) {
                if (y > yMin && y < yMax) {
                    return z > zMin && z < zMax;
                }
            }
            return false;
        }
        
        bool Vector3::InRangeExclusive(const Vector3 &min, const Vector3 &max) const {
            if (x > min.x && x < max.x) {
                if (y > min.y && y < max.y) {
                    return z > min.z && z < max.z;
                }
            }
            return false;
        }
        
        
        float Vector3::Sum() const {
            return x + y + z;
        }
        
        float Vector3::Product() const {
            return x * y * z;
        }
        
        float Vector3::Average() const {
            return (x + y + z) / 3.0f;
        }
        
        float Vector3::MaxValue() const {
            return Math::Max(Math::Max(x, y), z);
        }
        
        float Vector3::MinValue() const {
            return Math::Min(Math::Min(x, y), z);
        }
        
        
        float Vector3::Dot(const Vector3 &a, const Vector3 &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
        
        Vector3 Vector3::Average(const Vector3 &a, const Vector3 &b) {
            return (a + b) / 2.0f;
        }
        
        Vector3 Vector3::Normalize(const Vector3 &vec) {
            return vec.Normalized();
        }
        
        Vector3 Vector3::Cross(const Vector3 &a, const Vector3 &b) {
            return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }
        
        float Vector3::Distance(const Vector3 &a, const Vector3 &b) {
            float xDif = (b.x - a.x);
            float yDif = (b.y - a.y);
            float zDif = (b.z - a.z);
            return Math::Sqrt(xDif * xDif + yDif * yDif + zDif * zDif);
        }
        
        float Vector3::SqrDistance(const Vector3 &a, const Vector3 &b) {
            float xDif = b.x - a.x;
            float yDif = b.y - a.y;
            float zDif = (b.z - a.z);
            return xDif * xDif + yDif * yDif + zDif * zDif;
        }
        
        Vector3 Vector3::Scale(const Vector3 &a, const Vector3 &b) {
            return {a.x * b.x, a.y * b.y, a.z * b.z};
        }
        
        Vector3 Vector3::Lerp(const Vector3 &a, const Vector3 &b, float t) {
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
        }
        
        Vector3 Vector3::LerpClamped(const Vector3 &a, const Vector3 &b, float t) {
            if (t < 0) {
                return a;
            }
            if (t > 1) {
                return b;
            }
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
        }
        
        Vector3 Vector3::InverseLerp(const Vector3 &a, const Vector3 &b, float t) {
            return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z)};
        }
        
        Vector3 Vector3::Max(const Vector3 &a, const Vector3 &b) {
            return {Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z)};
        }
        
        Vector3 Vector3::Min(const Vector3 &a, const Vector3 &b) {
            return {Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z)};
        }
        
        Vector3 Vector3::MoveTowards(const Vector3 &current, const Vector3 &target, float maxDistanceDelta) {
            if (maxDistanceDelta > 1) {
                return target;
            }
            float oneMinusT = 1 - maxDistanceDelta;
            return {current.x * oneMinusT + target.x * maxDistanceDelta,
                    current.y * oneMinusT + target.y * maxDistanceDelta,
                    current.z * oneMinusT + target.z * maxDistanceDelta};
            
        }
        
        Vector3 Vector3::Reflect(const Vector3 &inDirection, const Vector3 &inNormal) {
            return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
        }
        
        float Vector3::Dot(const Vector3 &other) const {
            return Dot(*this, other);
        }
        
        Vector3 Vector3::Cross(const Vector3 &other) const {
            return Vector3::Cross(*this, other);
        }
        
        float Vector3::Distance(const Vector3 &b) const {
            return Distance(*this, b);
        }
        
        float Vector3::SqrDistance(const Vector3 &b) const {
            return SqrDistance(*this, b);
        }
        
        
        Vector3 Vector3::Scale(const Vector3 &b) const {
            return Scale(*this, b);
        }
        
        Vector3 Vector3::Lerp(const Vector3 &b, float t) const {
            return Lerp(*this, b, t);
        }
        
        Vector3 Vector3::LerpClamped(const Vector3 &b, float t) const {
            return LerpClamped(*this, b, t);
        }
        
        Vector3 Vector3::InverseLerp(const Vector3 &b, float t) const {
            return {InverseLerp(*this, b, t)};
        }
        
        Vector3 Vector3::MoveTowards(const Vector3 &target, float maxDistanceDelta) const {
            return MoveTowards(*this, target, maxDistanceDelta);
        }
        
        Vector3 Vector3::Reflect(const Vector3 &inNormal) const {
            return Reflect(*this, inNormal);
        }
        
        Vector3 Vector3::ScaledToLength(float newLength) const { return Normalized() * newLength; }
        
        Vector2 Vector3::xx() const { return {x, x}; }
        
        Vector2 Vector3::xy() const { return {x, y}; }
        
        Vector2 Vector3::xz() const { return {x, z}; }
        
        Vector2 Vector3::yx() const { return {y, x}; }
        
        Vector2 Vector3::yy() const { return {y, y}; }
        
        Vector2 Vector3::yz() const { return {y, z}; }
        
        Vector2 Vector3::zx() const { return {z, x}; }
        
        Vector2 Vector3::zy() const { return {z, y}; }
        
        Vector2 Vector3::zz() const { return {z, z}; }
        
        Vector3 Vector3::xxx() const { return {x, x, x}; }
        
        Vector3 Vector3::xxy() const { return {x, x, y}; }
        
        Vector3 Vector3::xxz() const { return {x, x, z}; }
        
        Vector3 Vector3::xyx() const { return {x, y, x}; }
        
        Vector3 Vector3::xyy() const { return {x, y, y}; }
        
        Vector3 Vector3::xyz() const { return {x, y, z}; }
        
        Vector3 Vector3::xzx() const { return {x, z, x}; }
        
        Vector3 Vector3::xzy() const { return {x, z, y}; }
        
        Vector3 Vector3::xzz() const { return {x, z, z}; }
        
        Vector3 Vector3::yxx() const { return {y, x, x}; }
        
        Vector3 Vector3::yxy() const { return {y, x, y}; }
        
        Vector3 Vector3::yxz() const { return {y, x, z}; }
        
        Vector3 Vector3::yyx() const { return {y, y, x}; }
        
        Vector3 Vector3::yyy() const { return {y, y, y}; }
        
        Vector3 Vector3::yyz() const { return {y, y, z}; }
        
        Vector3 Vector3::yzx() const { return {y, z, x}; }
        
        Vector3 Vector3::yzy() const { return {y, z, y}; }
        
        Vector3 Vector3::yzz() const { return {y, z, z}; }
        
        Vector3 Vector3::zxx() const { return {z, x, x}; }
        
        Vector3 Vector3::zxy() const { return {z, x, y}; }
        
        Vector3 Vector3::zxz() const { return {z, x, z}; }
        
        Vector3 Vector3::zyx() const { return {z, y, x}; }
        
        Vector3 Vector3::zyy() const { return {z, y, y}; }
        
        Vector3 Vector3::zyz() const { return {z, y, z}; }
        
        Vector3 Vector3::zzx() const { return {z, z, x}; }
        
        Vector3 Vector3::zzy() const { return {z, z, y}; }
        
        Vector3 Vector3::zzz() const { return {z, z, z}; }
        
        int Vector3::LexicographicCompare(const Vector3 &other) const {
            if (x < other.x) {
                return -1;
            } else if (x > other.x) {
                return 1;
            }
            if (y < other.y) {
                return -1;
            } else if (y > other.y) {
                return 1;
            }
            if (z < other.z) {
                return -1;
            } else if (z > other.z) {
                return 1;
            }
            return 0;
        }
        
        int Vector3::MagnitudeCompare(const Vector3 &other) const {
            float mag = SqrMagnitude();
            float otherMag = other.SqrMagnitude();
            if (mag < otherMag) {
                return -1;
            }
            if (mag > otherMag) {
                return 1;
            }
            return 0;
        }
        
        int Vector3::SumCompare(const Vector3 &other) const {
            float sum = Sum();
            float otherSum = other.Sum();
            if (sum < otherSum) {
                return -1;
            } else if (sum > otherSum) {
                return 1;
            }
            return 0;
        }
    
}



















