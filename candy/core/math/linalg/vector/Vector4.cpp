#include "Vector4.hpp"
#include "../../../../include/Candy/Math.hpp"

namespace Candy::Math{
        
        
        Vector4::Vector4() : VectorBase<float, 4>() {}
        
        Vector4::Vector4(float value) : VectorBase<float, 4>(value) {}
        
        Vector4::Vector4(const Vector3 &vec, float wValue) : VectorBase<float, 4>(vec.x, vec.y, vec.z, wValue) {}
        
        Vector4::Vector4(const Vector2 &vec) : VectorBase<float, 4>(vec.x, vec.y, 0.0f, 0.0f) {}
        
        Vector4::Vector4(const Vector3 &vec) : VectorBase<float, 4>(vec.x, vec.y, vec.z, 0.0f) {}
        
        
        const Vector4 Vector4::up(0, 1, 0, 0);
        const Vector4 Vector4::down(0, -1, 0, 0);
        const Vector4 Vector4::left(-1, 0, 0, 0);
        const Vector4 Vector4::right(1, 0, 0, 0);
        const Vector4 Vector4::forward(0, 0, 1, 0);
        const Vector4 Vector4::back(0, 0, -1, 0);
        const Vector4 Vector4::zero(0, 0, 0, 0);
        const Vector4 Vector4::one(1, 1, 1, 1);
        const Vector4 Vector4::negativeOne(-1, -1, -1, -1);
        const Vector4 Vector4::positiveInfinity(std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity());
        const Vector4 Vector4::negativeInfinity(-std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity());
        
        
        bool Vector4::operator==(const Vector4 &other) const {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }
        
        bool Vector4::operator!=(const Vector4 &other) const {
            return !(x == other.x && y == other.y && z == other.z && w == other.w);
        }
        
        /*Vector4 Vector4::operator+(const Vector4 &other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        Vector4 Vector4::operator-(const Vector4 &other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        Vector4 Vector4::operator*(const Vector4 &other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }

        Vector4 Vector4::operator/(const Vector4 &other) const {
            return {x / other.x, y / other.y, z / other.z, z / other.z};
        }*/
        
        Vector4 Vector4::operator^(const Vector4 &other) const {
            return {Math::Pow(x, other.x), Math::Pow(y, other.y), Math::Pow(z, other.z), Math::Pow(w, other.w)};
        }
        
        /*Vector4 Vector4::operator*(float scalar) const {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }

        Vector4 Vector4::operator/(float scalar) const {
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }*/
        
        Vector4 Vector4::operator^(float scalar) const {
            return {Math::Pow(x, scalar), Math::Pow(y, scalar), Math::Pow(z, scalar), Math::Pow(w, scalar)};
        }
        
        void Vector4::operator+=(const Vector4 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
        }
        
        void Vector4::operator-=(const Vector4 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
        }
        
        void Vector4::operator*=(const Vector4 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
        }
        
        void Vector4::operator/=(const Vector4 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
        }
        
        
        void Vector4::operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
        }
        
        void Vector4::operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }
        
        
        Vector4::operator Vector2() const { return Vector2(x, y); }
        
        Vector4::operator Vector3() const { return Vector3(x, y, z); }
        
        
        void Vector4::Set(float value) {
            x = value;
            y = value;
            z = value;
            w = value;
        }
        
        void Vector4::Set(float xValue, float yValue, float zValue, float wValue) {
            x = xValue;
            y = yValue;
            z = zValue;
            w = wValue;
        }
        
        void Vector4::Normalize() {
            float mag = Magnitude();
            x /= mag;
            y /= mag;
            z /= mag;
            w /= mag;
        }
        
        Vector4 Vector4::Normalized() const {
            float mag = Magnitude();
            return {x / mag, y / mag, z / mag, w / mag};
        }
        
        float Vector4::Magnitude() const {
            return Math::Sqrt(x * x + y * y + z * z + w * w);
        }
        
        float Vector4::SqrMagnitude() const {
            return x * x + y * y + z * z + w * w;
        }
        
        Vector4::operator std::string() const {
            return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ',' +
                   std::to_string(w) + ')';
        }
        
        
        std::ostream &Vector4::operator<<(std::ostream &ostream) const {
            ostream << '(' << x << ',' << y << ',' << z << ',' << w << ')';
            return ostream;
        }
        
        std::ostream &operator<<(std::ostream &ostream, const Vector4 &vec) {
            ostream << '(' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << ')';
            return ostream;
        }
        
        /*Vector4 operator*(float scalar, const Vector4 &vec) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar};
        }

        Vector4 operator/(float scalar, const Vector4 &vec) {
            return {scalar / vec.x, scalar / vec.y, scalar / vec.z, scalar / vec.w};
        }*/
        
        Vector4 operator^(float scalar, const Vector4 &vec) {
            return {Math::Pow(scalar, vec.x), Math::Pow(scalar, vec.y), Math::Pow(scalar, vec.z),
                    Math::Pow(scalar, vec.w)};
        }
        
        void Vector4::Clamp(float min, float max) {
            x = Math::Clamp(x, min, max);
            y = Math::Clamp(y, min, max);
            z = Math::Clamp(z, min, max);
            w = Math::Clamp(w, min, max);
        }
        
        void
        Vector4::Clamp(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax, float wMax) {
            x = Math::Clamp(x, xMin, xMax);
            y = Math::Clamp(y, yMin, yMax);
            z = Math::Clamp(z, zMin, zMax);
            w = Math::Clamp(w, wMin, wMax);
            
        }
        
        void Vector4::Clamp(const Vector4 &min, const Vector4 &max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
            z = Math::Clamp(z, min.z, max.z);
            w = Math::Clamp(w, min.w, max.w);
        }
        
        
        [[nodiscard]] bool Vector4::InRangeInclusive(float minValue, float maxValue) const {
            if (x < minValue || x > maxValue) {
                return false;
            }
            if (y < minValue || y > maxValue) {
                return false;
            }
            if (z < minValue || z > maxValue) {
                return false;
            }
            return !(w < minValue || w > maxValue);
        }
        
        [[nodiscard]] bool
        Vector4::InRangeInclusive(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                  float wMax) const {
            if (x < xMin || x > xMax) {
                return false;
            }
            if (y < yMin || y > yMax) {
                return false;
            }
            if (z < zMin || z > zMax) {
                return false;
            }
            return !(w < wMin || w > wMax);
            
        }
        
        [[nodiscard]] bool Vector4::InRangeInclusive(const Vector4 &min, const Vector4 &max) const {
            if (x < min.x || x > max.x) {
                return false;
            }
            if (y < min.y || y > max.y) {
                return false;
            }
            if (z < min.z || z > max.z) {
                return false;
            }
            return !(w < min.w || w > max.w);
        }
        
        [[nodiscard]] bool Vector4::InRangeInclusiveMin(float minValue, float maxValue) const {
            if (x < minValue || x >= maxValue) {
                return false;
            }
            if (y < minValue || y >= maxValue) {
                return false;
            }
            if (z < minValue || z >= maxValue) {
                return false;
            }
            return !(w < minValue || w >= maxValue);
            
        }
        
        [[nodiscard]] bool
        Vector4::InRangeInclusiveMin(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                     float wMax) const {
            if (x < xMin || x >= xMax) {
                return false;
            }
            if (y < yMin || y >= yMax) {
                return false;
            }
            if (z < zMin || z >= zMax) {
                return false;
            }
            return !(w < wMin || w >= wMax);
        }
        
        [[nodiscard]] bool Vector4::InRangeInclusiveMin(const Vector4 &min, const Vector4 &max) const {
            if (x < min.x || x >= max.x) {
                return false;
            }
            if (y < min.y || y >= max.y) {
                return false;
            }
            if (z < min.z || z >= max.z) {
                return false;
            }
            return !(w < min.w || w >= max.w);
        }
        
        [[nodiscard]] bool Vector4::InRangeInclusiveMax(float minValue, float maxValue) const {
            if (x <= minValue || x > maxValue) {
                return false;
            }
            if (y <= minValue || y > maxValue) {
                return false;
            }
            if (z <= minValue || z > maxValue) {
                return false;
            }
            return !(w <= minValue || w > maxValue);
        }
        
        [[nodiscard]] bool
        Vector4::InRangeInclusiveMax(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                     float wMax) const {
            if (x <= xMin || x > xMax) {
                return false;
            }
            if (y <= yMin || y > yMax) {
                return false;
            }
            if (z <= zMin || z > zMax) {
                return false;
            }
            return !(w <= wMin || w > wMax);
        }
        
        [[nodiscard]] bool Vector4::InRangeInclusiveMax(const Vector4 &min, const Vector4 &max) const {
            if (x <= min.x || x > max.x) {
                return false;
            }
            if (y <= min.y || y > max.y) {
                return false;
            }
            if (z <= min.z || z > max.z) {
                return false;
            }
            return !(w <= min.w || w > max.w);
        }
        
        [[nodiscard]] bool Vector4::InRangeExclusive(float minValue, float maxValue) const {
            if (x > minValue && x < maxValue) {
                if (y > minValue && y < maxValue) {
                    if (z > minValue && z < maxValue) {
                        return w > minValue && w < maxValue;
                    }
                }
            }
            return false;
        }
        
        [[nodiscard]] bool
        Vector4::InRangeExclusive(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                  float wMax) const {
            if (x > xMin && x < xMax) {
                if (y > yMin && y < yMax) {
                    if (z > zMin && z < zMax) {
                        return w > wMin && w < wMax;
                    }
                }
            }
            return false;
        }
        
        bool Vector4::InRangeExclusive(const Vector4 &min, const Vector4 &max) const {
            if (x > min.x && x < max.x) {
                if (y > min.y && y < max.y) {
                    if (z > min.z && z < max.z) {
                        return w > min.w && w < max.w;
                    }
                }
            }
            return false;
        }
        
        
        float Vector4::Sum() const {
            return x + y + z + w;
        }
        
        float Vector4::Product() const {
            return x * y * z * w;
        }
        
        float Vector4::MaxValue() const {
            return Math::Max(Math::Max(x, y), Math::Max(z, w));
        }
        
        float Vector4::MinValue() const {
            return Math::Min(Math::Min(x, y), Math::Min(z, w));
        }
        
        Vector4 Vector4::Clamped(float valueMin, float valueMax) const {
            return {Math::Clamp(x, valueMin, valueMax), Math::Clamp(y, valueMin, valueMax),
                    Math::Clamp(z, valueMin, valueMax), Math::Clamp(w, valueMin, valueMax)};
        }
        
        Vector4 Vector4::Clamped(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                 float wMax) const {
            return {Math::Clamp(x, xMin, xMax), Math::Clamp(y, yMin, yMax), Math::Clamp(z, zMin, zMax),
                    Math::Clamp(w, wMin, wMax)};
        }
        
        Vector4 Vector4::Clamped(const Vector4 &min, const Vector4 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z),
                    Math::Clamp(w, min.w, max.w)};
        }
        
        float Vector4::Dot(const Vector4 &a, const Vector4 &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }
        
        float Vector4::Distance(const Vector4 &a, const Vector4 &b) {
            float xDif = (b.x - a.x);
            float yDif = (b.y - a.y);
            float zDif = (b.z - a.z);
            float wDif = (b.w - a.w);
            return Math::Sqrt(xDif * xDif + yDif * yDif + zDif * zDif + wDif * wDif);
        }
        
        float Vector4::SqrDistance(const Vector4 &a, const Vector4 &b) {
            float xDif = b.x - a.x;
            float yDif = b.y - a.y;
            float zDif = (b.z - a.z);
            float wDif = (b.w - a.w);
            return xDif * xDif + yDif * yDif + zDif * zDif + wDif * wDif;
        }
        
        
        Vector4 Vector4::Scale(const Vector4 &a, const Vector4 &b) {
            return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
        }
        
        Vector4 Vector4::Lerp(const Vector4 &a, const Vector4 &b, float t) {
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t,
                    a.w * oneMinusT + b.w * t};
        }
        
        Vector4 Vector4::LerpClamped(const Vector4 &a, const Vector4 &b, float t) {
            if (t < 0) {
                return a;
            }
            if (t > 1) {
                return b;
            }
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t,
                    a.w * oneMinusT + b.w * t};
        }
        
        Vector4 Vector4::InverseLerp(const Vector4 &a, const Vector4 &b, float t) {
            return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z), (t - a.w) / (b.w - a.w)};
        }
        
        Vector4 Vector4::Max(const Vector4 &a, const Vector4 &b) {
            return {Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z), Math::Max(a.w, b.w)};
        }
        
        Vector4 Vector4::Min(const Vector4 &a, const Vector4 &b) {
            return {Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z), Math::Min(a.w, b.w)};
        }
        
        Vector4 Vector4::Average(const Vector4 &a, const Vector4 &b) {
            return (a + b) / 2;
        }
        
        Vector4 Vector4::Normalize(const Vector4 &vec) {
            return vec.Normalized();
        }
        
        Vector4 Vector4::MoveTowards(const Vector4 &current, const Vector4 &target, float maxDistanceDelta) {
            if (maxDistanceDelta > 1) {
                return target;
            }
            float oneMinusT = 1 - maxDistanceDelta;
            return {current.x * oneMinusT + target.x * maxDistanceDelta,
                    current.y * oneMinusT + target.y * maxDistanceDelta,
                    current.z * oneMinusT + target.z * maxDistanceDelta,
                    current.w * oneMinusT + target.w * maxDistanceDelta};
            
        }
        
        
        Vector4 Vector4::Reflect(const Vector4 &inDirection, const Vector4 &inNormal) {
            return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
        }
        
        float Vector4::Dot(const Vector4 &other) const {
            return Dot(*this, other);
        }
        
        
        float Vector4::Distance(const Vector4 &b) const {
            return Distance(*this, b);
        }
        
        float Vector4::SqrDistance(const Vector4 &b) const {
            return SqrDistance(*this, b);
        }
        
        [[nodiscard]] Vector4 Vector4::Scale(const Vector4 &b) const { return Scale(*this, b); }
        
        [[nodiscard]] Vector4 Vector4::Lerp(const Vector4 &b, float t) const {
            return Lerp(*this, b, t);
        }
        
        [[nodiscard]] Vector4 Vector4::LerpClamped(const Vector4 &b, float t) const { return LerpClamped(*this, b, t); }
        
        [[nodiscard]] Vector4 Vector4::InverseLerp(const Vector4 &b, float t) const { return InverseLerp(*this, b, t); }
        
        [[nodiscard]] Vector4 Vector4::MoveTowards(const Vector4 &target, float maxDistanceDelta) const {
            return MoveTowards(*this, target, maxDistanceDelta);
        }
        
        
        Vector4 Vector4::Reflect(const Vector4 &inNormal) const {
            return Reflect(*this, inNormal);
        }
        
        int Vector4::LexicographicCompare(const Vector4 &other) const {
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
            if (w < other.w) {
                return -1;
            } else if (w > other.w) {
                return 1;
            }
            return 0;
        }
        
        int Vector4::MagnitudeCompare(const Vector4 &other) const {
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
        
        int Vector4::SumCompare(const Vector4 &other) const {
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

















