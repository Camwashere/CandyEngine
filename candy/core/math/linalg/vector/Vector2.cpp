#include "Vector2.hpp"
#include "../../../../include/Candy/Math.hpp"


namespace Candy::Math{
        
        
        Vector2::Vector2() : VectorBase<float, 2>(0, 0) {}
        
        //Vector2::Vector2(float xValue, float yValue) : x(xValue), y(yValue) {}
        
        Vector2::Vector2(float value) : VectorBase<float, 2>(value) {}
        
        // constexpr Vector2::Vector2(const Vector2 &other) = default;
        //Vector2::Vector2(const ImVec2& other) : VectorBase<float, 2>(other.x, other.y){}
        
        
        Vector2::Vector2(const Vector3 &other) : VectorBase<float, 2>(other.x, other.y){}
        
        Vector2::Vector2(const Vector4 &other) : VectorBase<float, 2>(other.x, other.y) {}
        
        Vector2::Vector2(const float *data) : VectorBase<float, 2>(data[0], data[1]) {}
        
        
        const Vector2 Vector2::up(0, 1);
        const Vector2 Vector2::down(0, -1);
        const Vector2 Vector2::left(-1, 0);
        const Vector2 Vector2::right(1, 0);
        const Vector2 Vector2::upLeft(-1, 1);
        const Vector2 Vector2::upRight(1, 1);
        const Vector2 Vector2::downLeft(-1, -1);
        const Vector2 Vector2::downRight(1, -1);
        const Vector2 Vector2::zero(0, 0);
        const Vector2 Vector2::one(1, 1);
        const Vector2 Vector2::negativeOne(-1, -1);
        const Vector2 Vector2::positiveInfinity(std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity());
        const Vector2 Vector2::negativeInfinity(-std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity());
        
        bool Vector2::operator==(const Vector2 &other) const {
            return x == other.x && y == other.y;
        }
        
        bool Vector2::operator!=(const Vector2 &other) const {
            return !(x == other.x && y == other.y);
        }
        
        bool Vector2::operator<(const Vector2 &other) const {
            return x < other.x && y < other.y;
        }
        
        bool Vector2::operator<=(const Vector2 &other) const {
            return x <= other.x && y <= other.y;
        }
        
        bool Vector2::operator>(const Vector2 &other) const {
            return x > other.x && y > other.y;
        }
        
        bool Vector2::operator>=(const Vector2 &other) const {
            return x >= other.x && y >= other.y;
        }
        
        bool Vector2::operator<(float other) const { return x < other && y < other; }
        
        bool Vector2::operator<=(float other) const { return x <= other && y <= other; }
        
        bool Vector2::operator>(float other) const { return x > other && y > other; }
        
        bool Vector2::operator>=(float other) const { return x >= other && y >= other; }
        
        
        Vector2 Vector2::operator-() const {
            return {-x, -y};
        }
        
        
        /*Vector2 Vector2::operator+(const Vector2 &other) const {
            return {x + other.x, y + other.y};
        }

        Vector2 Vector2::operator-(const Vector2 &other) const {
            return {x - other.x, y - other.y};
        }

        Vector2 Vector2::operator*(const Vector2 &other) const {
            return {x * other.x, y * other.y};
        }

        Vector2 Vector2::operator/(const Vector2 &other) const {
            return {x / other.x, y / other.y};
        }*/
        
        Vector2 Vector2::operator^(const Vector2 &other) const {
            return {Pow(x, other.x), Pow(y, other.y)};
        }
        
        /*Vector2 Vector2::operator+(const Vector3 &other) const { return {x + other.x, y + other.y}; }

        Vector2 Vector2::operator-(const Vector3 &other) const { return {x - other.x, y - other.y}; }

        Vector2 Vector2::operator*(const Vector3 &other) const { return {x * other.x, y * other.y}; }

        Vector2 Vector2::operator/(const Vector3 &other) const { return {x / other.x, y / other.y}; }*/
        
        Vector2 Vector2::operator^(const Vector3 &other) const { return {Pow(x, other.x), Pow(y, other.y)}; }
        
        /*Vector2 Vector2::operator*(float scalar) const { return {x * scalar, y * scalar}; }

        Vector2 Vector2::operator/(float scalar) const { return {x / scalar, y / scalar}; }*/
        
        Vector2 Vector2::operator^(float scalar) const { return {Pow(x, scalar), Pow(y, scalar)}; }
        
        /*Vector2 Vector2::operator*(int scalar) const { return {x * scalar, y * scalar}; }

        Vector2 Vector2::operator/(int scalar) const { return {x / scalar, y / scalar}; }*/
        
        void Vector2::operator+=(const Vector2 &other) {
            x += other.x;
            y += other.y;
        }
        
        void Vector2::operator-=(const Vector2 &other) {
            x -= other.x;
            y -= other.y;
        }
        
        void Vector2::operator*=(const Vector2 &other) {
            x *= other.x;
            y *= other.y;
        }
        
        void Vector2::operator/=(const Vector2 &other) {
            x /= other.x;
            y /= other.y;
        }
        
        void Vector2::operator+=(const Vector3 &other) {
            x += other.x;
            y += other.y;
        }
        
        void Vector2::operator-=(const Vector3 &other) {
            x -= other.x;
            y -= other.y;
        }
        
        void Vector2::operator*=(const Vector3 &other) {
            x *= other.x;
            y *= other.y;
        }
        
        void Vector2::operator/=(const Vector3 &other) {
            x /= other.x;
            y /= other.y;
        }
        
        
        void Vector2::operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
        }
        
        void Vector2::operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
        }
        
        void Vector2::operator*=(int scalar) {
            x *= scalar;
            y *= scalar;
        }
        
        void Vector2::operator/=(int scalar) {
            x /= scalar;
            y /= scalar;
        }
        
        void Vector2::Set(float value) {
            x = value;
            y = value;
        }
        
        void Vector2::Set(float xValue, float yValue) {
            x = xValue;
            y = yValue;
        }
        
        void Vector2::Set(const Vector2 &other) {
            x = other.x;
            y = other.y;
        }
        
        /*void Vector2::Set(const Vector3 &other) {
            x = other.x;
            y = other.y;
        }

        void Vector2::Set(const Vector4 &other) {
            x = other.x;
            y = other.y;
        }*/
        
        void Vector2::Add(float value) {
            x += value;
            y += value;
        }
        
        void Vector2::Subtract(float value) {
            x -= value;
            y -= value;
        }
        
        void Vector2::Normalize() {
            float mag = Magnitude();
            x /= mag;
            y /= mag;
        }
        
        Vector2 Vector2::Normalized() const {
            float mag = Magnitude();
            return {x / mag, y / mag};
        }
        
        float Vector2::Magnitude() const {
            return Sqrt(x * x + y * y);
        }
        
        float Vector2::SqrMagnitude() const {
            return x * x + y * y;
        }
        
        Vector2::operator std::string() const {
            return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
        }
        
        //Vector2::operator ImVec2()const{return ImVec2(x, y);}
        
        Vector2::operator Vector3() const { return {x, y, 0}; }
        
        Vector2::operator Vector4() const { return {x, y, 0, 0}; }
        
        std::ostream &Vector2::operator<<(std::ostream &ostream) const {
            ostream << '(' << x << ',' << y << ')';
            return ostream;
        }
        
        std::ostream &operator<<(std::ostream &ostream, const Vector2 &vec) {
            ostream << '(' << vec.x << ',' << vec.y << ')';
            return ostream;
        }
        
        /*Vector2 operator*(float scalar, const Vector2 &vec) {
            return {vec.x * scalar, vec.y * scalar};
        }*/
        
        Vector2 operator/(float scalar, const Vector2 &vec) {
            return {scalar / vec.x, scalar / vec.y};
        }
        
        Vector2 operator^(float scalar, const Vector2 &vec) {
            return {Pow(scalar, vec.x), Pow(scalar, vec.y)};
        }
        
        void Vector2::Clamp(float min, float max) {
            x = Math::Clamp(x, min, max);
            y = Math::Clamp(y, min, max);
        }
        
        void Vector2::Clamp(float xMin, float yMin, float xMax, float yMax) {
            x = Math::Clamp(x, xMin, xMax);
            y = Math::Clamp(y, yMin, yMax);
            
        }
        
        void Vector2::Clamp(const Vector2 &min, const Vector2 &max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
        }
        
        Vector2 Vector2::Clamped(float xMin, float yMin, float xMax, float yMax) const {
            return {Math::Clamp(x, xMin, xMax), Math::Clamp(y, yMin, yMax)};
        }
        
        Vector2 Vector2::Clamped(const Vector2 &min, const Vector2 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y)};
        }
        
        Vector2 Vector2::Clamped(float valueMin, float valueMax) const {
            return {Math::Clamp(x, valueMin, valueMax), Math::Clamp(y, valueMin, valueMax)};
        }
        
        void Vector2::ScaleToLength(float newLength) {
            Normalize();
            *this *= newLength;
        }
        
        bool Vector2::InRangeInclusive(float minValue, float maxValue) const {
            if (x < minValue || x > maxValue) {
                return false;
            }
            return !(y < minValue || y > maxValue);
        }
        
        bool Vector2::InRangeInclusive(float xMin, float yMin, float xMax, float yMax) const {
            if (x < xMin || x > xMax) {
                return false;
            }
            return !(y < yMin || y > yMax);
        }
        
        bool Vector2::InRangeInclusive(const Vector2 &min, const Vector2 &max) const {
            if (x < min.x || x > max.x) {
                return false;
            }
            return !(y < min.y || y > max.y);
        }
        
        bool Vector2::InRangeInclusiveMin(float minValue, float maxValue) const {
            if (x < minValue || x >= maxValue) {
                return false;
            }
            return !(y < minValue || y >= maxValue);
        }
        
        bool Vector2::InRangeInclusiveMin(float xMin, float yMin, float xMax, float yMax) const {
            if (x < xMin || x >= xMax) {
                return false;
            }
            return !(y < yMin || y >= yMax);
        }
        
        bool Vector2::InRangeInclusiveMin(const Vector2 &min, const Vector2 &max) const {
            if (x < min.x || x >= max.x) {
                return false;
            }
            return !(y < min.y || y >= max.y);
        }
        
        bool Vector2::InRangeInclusiveMax(float minValue, float maxValue) const {
            if (x <= minValue || x > maxValue) {
                return false;
            }
            return !(y <= minValue || y > maxValue);
        }
        
        bool Vector2::InRangeInclusiveMax(float xMin, float yMin, float xMax, float yMax) const {
            if (x <= xMin || x > xMax) {
                return false;
            }
            return !(y <= yMin || y > yMax);
        }
        
        bool Vector2::InRangeInclusiveMax(const Vector2 &min, const Vector2 &max) const {
            if (x <= min.x || x > max.x) {
                return false;
            }
            return !(y <= min.y || y > max.y);
        }
        
        bool Vector2::InRangeExclusive(float minValue, float maxValue) const {
            if (x > minValue && x < maxValue) {
                return true;
            }
            return y > minValue && y < maxValue;
        }
        
        bool Vector2::InRangeExclusive(float xMin, float yMin, float xMax, float yMax) const {
            if (x > xMin && x < xMax) {
                return true;
            }
            return y > yMin && y < yMax;
        }
        
        bool Vector2::InRangeExclusive(const Vector2 &min, const Vector2 &max) const {
            if (x > min.x && x < max.x) {
                return y > min.y && y < max.y;
            }
            return false;
        }
        
        [[nodiscard]] bool Vector2::EqualComponents() const {
            return x == y;
        }
        
        float Vector2::Sum() const {
            return x + y;
        }
        
        float Vector2::Difference() const {
            return x - y;
        }
        
        float Vector2::AbsDifference() const {
            return Math::Abs(x - y);
        }
        
        float Vector2::Product() const {
            return x * y;
        }
        
        float Vector2::Quotient() const {
            return x / y;
        }
        
        float Vector2::MaxValue() const {
            return Math::Max(x, y);
        }
        
        float Vector2::MinValue() const {
            return Math::Min(x, y);
        }
        
        float Vector2::Average() const {
            return (x + y) / 2.0f;
        }
        
        
        float Vector2::Dot(const Vector2 &a, const Vector2 &b) {
            return a.x * b.x + a.y * b.y;
        }
        
        float Vector2::Distance(const Vector2 &a, const Vector2 &b) {
            float xDif = (b.x - a.x);
            float yDif = (b.y - a.y);
            return Sqrt(xDif * xDif + yDif * yDif);
        }
        
        float Vector2::Slope(const Vector2 &start, const Vector2 &end) {
            return (end.y - start.y) / (end.x - start.x);
        }
        
        float Vector2::SqrDistance(const Vector2 &a, const Vector2 &b) {
            float xDif = b.x - a.x;
            float yDif = b.y - a.y;
            return xDif * xDif + yDif * yDif;
        }
        
        Vector2 Vector2::Scale(const Vector2 &a, const Vector2 &b) {
            return {a.x * b.x, a.y * b.y};
        }
        
        Vector2 Vector2::Lerp(const Vector2 &a, const Vector2 &b, float t) {
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
        }
        
        Vector2 Vector2::LerpClamped(const Vector2 &a, const Vector2 &b, float t) {
            if (t < 0) {
                return a;
            }
            if (t > 1) {
                return b;
            }
            float oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
        }
        
        Vector2 Vector2::InverseLerp(const Vector2 &a, const Vector2 &b, float t) {
            return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y)};
        }
        
        Vector2 Vector2::Max(const Vector2 &a, const Vector2 &b) {
            return {Math::Max(a.x, b.x), Math::Max(a.y, b.y)};
        }
        
        Vector2 Vector2::Min(const Vector2 &a, const Vector2 &b) {
            return {Math::Min(a.x, b.x), Math::Min(a.y, b.y)};
        }
        
        Vector2 Vector2::Normalize(const Vector2 &vec) {
            return vec.Normalized();
        }
        
        
        float Vector2::Determinant(const Vector2 &a, const Vector2 &b) {
            return a.x * b.y - a.y * b.x;
        }
        
        float Vector2::Angle(const Vector2 &from, const Vector2 &to) {
            float d = (from.x * to.x + from.y * to.y) / (from.Magnitude() * to.Magnitude());
            return Math::Acos(Math::Clamp(d, -1.0f, 1.0f));
        }
        
        float Vector2::SignedAngle(const Vector2 &from, const Vector2 &to) {
            return Math::Atan2(from.x * to.y - from.y * to.x, from.x * to.x + from.y * to.y);
        }
        
        Vector2 Vector2::PerpendicularClockwise(const Vector2 &vec) {
            return {vec.y, -vec.x};
        }
        
        Vector2 Vector2::PerpendicularCounterClockwise(const Vector2 &vec) {
            return {-vec.y, vec.x};
        }
        
        Vector2 Vector2::MoveTowards(const Vector2 &current, const Vector2 &target, float maxDistanceDelta) {
            if (maxDistanceDelta > 1) {
                return target;
            }
            float oneMinusT = 1 - maxDistanceDelta;
            return {current.x * oneMinusT + target.x * maxDistanceDelta,
                    current.y * oneMinusT + target.y * maxDistanceDelta};
            
        }
        
        Vector2 Vector2::Reflect(const Vector2 &inDirection, const Vector2 &inNormal) {
            Vector2 vec = inDirection - 2.0f * Dot(inDirection, inNormal) * inNormal;
            return Vector2();
        }
        
        float Vector2::Dot(const Vector2 &other) const {
            return Dot(*this, other);
        }
        
        float Vector2::Determinant(const Vector2 &b) const {
            return Determinant(*this, b);
        }
        
        float Vector2::Distance(const Vector2 &b) const {
            return Distance(*this, b);
        }
        
        float Vector2::SqrDistance(const Vector2 &b) const {
            return SqrDistance(*this, b);
        }
        
        float Vector2::Slope(const Vector2 &end) const {
            return Slope(*this, end);
        }
        
        Vector2 Vector2::Scale(const Vector2 &b) const {
            return Scale(*this, b);
        }
        
        Vector2 Vector2::Lerp(const Vector2 &b, float t) const {
            return Lerp(*this, b, t);
        }
        
        Vector2 Vector2::LerpClamped(const Vector2 &b, float t) const {
            return LerpClamped(*this, b, t);
        }
        
        Vector2 Vector2::InverseLerp(const Vector2 &b, float t) const {
            return InverseLerp(*this, b, t);
        }
        
        float Vector2::Angle(const Vector2 &to) const {
            return Angle(*this, to);
        }
        
        float Vector2::SignedAngle(const Vector2 &to) const {
            return SignedAngle(*this, to);
        }
        
        Vector2 Vector2::PerpendicularClockwise() const {
            return PerpendicularClockwise(*this);
        }
        
        Vector2 Vector2::PerpendicularCounterClockwise() const {
            return PerpendicularCounterClockwise(*this);
        }
        
        Vector2 Vector2::MoveTowards(const Vector2 &target, float maxDistanceDelta) const {
            return MoveTowards(*this, target, maxDistanceDelta);
        }
        
        Vector2 Vector2::Reflect(const Vector2 &inNormal) const {
            return Reflect(*this, inNormal);
        }
        
        Vector2 Vector2::ScaledToLength(float newLength) const {
            return Normalized() * newLength;
        }
        
        
        Vector2 Vector2::xx() const { return {x, x}; }
        
        Vector2 Vector2::xy() const { return {x, y}; }
        
        Vector2 Vector2::yx() const { return {y, x}; }
        
        Vector2 Vector2::yy() const { return {y, y}; }
        
        float Vector2::ToVector1() const { return x; }
        
        Vector3 Vector2::ToVector3() const { return {x, y, 0}; }
        
        Vector4 Vector2::ToVector4() const { return {x, y, 0, 0}; }
        
        int Vector2::LexicographicCompare(const Vector2 &other) const {
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
            return 0;
        }
        
        int Vector2::MagnitudeCompare(const Vector2 &other) const {
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
        
        int Vector2::SumCompare(const Vector2 &other) const {
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

















