#include "Vector2Int.hpp"
#include "../../../../include/Candy/Math.hpp"


namespace Candy::Math{
        
        
        Vector2Int::Vector2Int() : VectorBase<int, 2>(0, 0) {}
        Vector2Int::Vector2Int(int value) : VectorBase<int, 2>(value) {}
        
        const Vector2Int Vector2Int::up(0, 1);
        const Vector2Int Vector2Int::down(0, -1);
        const Vector2Int Vector2Int::left(-1, 0);
        const Vector2Int Vector2Int::right(1, 0);
        const Vector2Int Vector2Int::upLeft(-1, 1);
        const Vector2Int Vector2Int::upRight(1, 1);
        const Vector2Int Vector2Int::downLeft(-1, -1);
        const Vector2Int Vector2Int::downRight(1, -1);
        const Vector2Int Vector2Int::zero(0, 0);
        const Vector2Int Vector2Int::one(1, 1);
        const Vector2Int Vector2Int::negativeOne(-1, -1);
        const Vector2Int Vector2Int::positiveInfinity(std::numeric_limits<int>::infinity(),
                                                      std::numeric_limits<int>::infinity());
        const Vector2Int Vector2Int::negativeInfinity(-std::numeric_limits<int>::infinity(),
                                                      -std::numeric_limits<int>::infinity());
        
        bool Vector2Int::operator==(const Vector2Int &other) const {
            return x == other.x && y == other.y;
        }
        
        bool Vector2Int::operator!=(const Vector2Int &other) const {
            return !(x == other.x && y == other.y);
        }
        
        bool Vector2Int::operator<(const Vector2Int &other) const {
            return x < other.x && y < other.y;
        }
        
        bool Vector2Int::operator<=(const Vector2Int &other) const {
            return x <= other.x && y <= other.y;
        }
        
        bool Vector2Int::operator>(const Vector2Int &other) const {
            return x > other.x && y > other.y;
        }
        
        bool Vector2Int::operator>=(const Vector2Int &other) const {
            return x >= other.x && y >= other.y;
        }
        
        bool Vector2Int::operator<(int other) const { return x < other && y < other; }
        
        bool Vector2Int::operator<=(int other) const { return x <= other && y <= other; }
        
        bool Vector2Int::operator>(int other) const { return x > other && y > other; }
        
        bool Vector2Int::operator>=(int other) const { return x >= other && y >= other; }
        
        
        Vector2Int Vector2Int::operator-() const {
            return {-x, -y};
        }
        
        Vector2Int Vector2Int::operator*(const Vector2Int &other) const {
            return {x * other.x, y * other.y};
        }
        
        Vector2Int Vector2Int::operator/(const Vector2Int &other) const {
            return {x / other.x, y / other.y};
        }
        
        Vector2Int Vector2Int::operator^(const Vector2Int &other) const {
            return {Pow(x, other.x), Pow(y, other.y)};
        }
        
        Vector2Int Vector2Int::operator^(int scalar) const { return {Pow(x, scalar), Pow(y, scalar)}; }
        
        void Vector2Int::operator+=(const Vector2Int &other) {
            x += other.x;
            y += other.y;
        }
        
        void Vector2Int::operator-=(const Vector2Int &other) {
            x -= other.x;
            y -= other.y;
        }
        
        void Vector2Int::operator*=(const Vector2Int &other) {
            x *= other.x;
            y *= other.y;
        }
        
        void Vector2Int::operator/=(const Vector2Int &other) {
            x /= other.x;
            y /= other.y;
        }
        
        void Vector2Int::operator+=(const Vector3Int &other) {
            x += other.x;
            y += other.y;
        }
        
        void Vector2Int::operator-=(const Vector3Int &other) {
            x -= other.x;
            y -= other.y;
        }
        
        void Vector2Int::operator*=(const Vector3Int &other) {
            x *= other.x;
            y *= other.y;
        }
        
        void Vector2Int::operator/=(const Vector3Int &other) {
            x /= other.x;
            y /= other.y;
        }
        
        
        void Vector2Int::operator*=(int scalar) {
            x *= scalar;
            y *= scalar;
        }
        
        void Vector2Int::operator/=(int scalar) {
            x /= scalar;
            y /= scalar;
        }
        
        
        void Vector2Int::Set(int value) {
            x = value;
            y = value;
        }
        
        void Vector2Int::Set(int xValue, int yValue) {
            x = xValue;
            y = yValue;
        }
        
        void Vector2Int::Set(const Vector2Int &other) {
            x = other.x;
            y = other.y;
        }
        
        
        
        
        int Vector2Int::SqrMagnitude() const {
            return x * x + y * y;
        }
        
        Vector2Int::operator std::string() const {
            return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
        }
        
        
        std::ostream &Vector2Int::operator<<(std::ostream &ostream) const {
            ostream << '(' << x << ',' << y << ')';
            return ostream;
        }
        
        std::ostream &operator<<(std::ostream &ostream, const Vector2Int &vec) {
            ostream << '(' << vec.x << ',' << vec.y << ')';
            return ostream;
        }
        
        Vector2Int operator*(int scalar, const Vector2Int &vec) {
            return {vec.x * scalar, vec.y * scalar};
        }
        
        Vector2Int operator/(int scalar, const Vector2Int &vec) {
            return {scalar / vec.x, scalar / vec.y};
        }
        
        Vector2Int operator^(int scalar, const Vector2Int &vec) {
            return {Pow(scalar, vec.x), Pow(scalar, vec.y)};
        }
        
        void Vector2Int::Clamp(int min, int max) {
            x = Math::Clamp(x, min, max);
            y = Math::Clamp(y, min, max);
        }
        
        void Vector2Int::Clamp(int xMin, int yMin, int xMax, int yMax) {
            x = Math::Clamp(x, xMin, xMax);
            y = Math::Clamp(y, yMin, yMax);
            
        }
        
        void Vector2Int::Clamp(const Vector2Int &min, const Vector2Int &max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
        }
        
        Vector2Int Vector2Int::Clamped(int xMin, int yMin, int xMax, int yMax) const {
            return {Math::Clamp(x, xMin, xMax), Math::Clamp(y, yMin, yMax)};
        }
        
        Vector2Int Vector2Int::Clamped(const Vector2Int &min, const Vector2Int &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y)};
        }
        
        Vector2Int Vector2Int::Clamped(int valueMin, int valueMax) const {
            return {Math::Clamp(x, valueMin, valueMax), Math::Clamp(y, valueMin, valueMax)};
        }
        
        
        
        bool Vector2Int::InRangeInclusive(int minValue, int maxValue) const {
            if (x < minValue || x > maxValue) {
                return false;
            }
            return !(y < minValue || y > maxValue);
        }
        
        bool Vector2Int::InRangeInclusive(int xMin, int yMin, int xMax, int yMax) const {
            if (x < xMin || x > xMax) {
                return false;
            }
            return !(y < yMin || y > yMax);
        }
        
        bool Vector2Int::InRangeInclusive(const Vector2Int &min, const Vector2Int &max) const {
            if (x < min.x || x > max.x) {
                return false;
            }
            return !(y < min.y || y > max.y);
        }
        
        bool Vector2Int::InRangeInclusiveMin(int minValue, int maxValue) const {
            if (x < minValue || x >= maxValue) {
                return false;
            }
            return !(y < minValue || y >= maxValue);
        }
        
        bool Vector2Int::InRangeInclusiveMin(int xMin, int yMin, int xMax, int yMax) const {
            if (x < xMin || x >= xMax) {
                return false;
            }
            return !(y < yMin || y >= yMax);
        }
        
        bool Vector2Int::InRangeInclusiveMin(const Vector2Int &min, const Vector2Int &max) const {
            if (x < min.x || x >= max.x) {
                return false;
            }
            return !(y < min.y || y >= max.y);
        }
        
        bool Vector2Int::InRangeInclusiveMax(int minValue, int maxValue) const {
            if (x <= minValue || x > maxValue) {
                return false;
            }
            return !(y <= minValue || y > maxValue);
        }
        
        bool Vector2Int::InRangeInclusiveMax(int xMin, int yMin, int xMax, int yMax) const {
            if (x <= xMin || x > xMax) {
                return false;
            }
            return !(y <= yMin || y > yMax);
        }
        
        bool Vector2Int::InRangeInclusiveMax(const Vector2Int &min, const Vector2Int &max) const {
            if (x <= min.x || x > max.x) {
                return false;
            }
            return !(y <= min.y || y > max.y);
        }
        
        bool Vector2Int::InRangeExclusive(int minValue, int maxValue) const {
            if (x > minValue && x < maxValue) {
                return true;
            }
            return y > minValue && y < maxValue;
        }
        
        bool Vector2Int::InRangeExclusive(int xMin, int yMin, int xMax, int yMax) const {
            if (x > xMin && x < xMax) {
                return true;
            }
            return y > yMin && y < yMax;
        }
        
        bool Vector2Int::InRangeExclusive(const Vector2Int &min, const Vector2Int &max) const {
            if (x > min.x && x < max.x) {
                return y > min.y && y < max.y;
            }
            return false;
        }
        
        int Vector2Int::Sum() const {
            return x + y;
        }
        
        int Vector2Int::Product() const {
            return x * y;
        }
        
        int Vector2Int::MaxValue() const {
            return Math::Max(x, y);
        }
        
        int Vector2Int::MinValue() const {
            return Math::Min(x, y);
        }
        
        int Vector2Int::Average() const {
            return (x + y) / 2.0f;
        }
        
        
        int Vector2Int::Dot(const Vector2Int &a, const Vector2Int &b) {
            return a.x * b.x + a.y * b.y;
        }
        
        float Vector2Int::Distance(const Vector2Int &a, const Vector2Int &b) {
            int xDif = (b.x - a.x);
            int yDif = (b.y - a.y);
            return Sqrt(xDif * xDif + yDif * yDif);
        }
        
        
        int Vector2Int::SqrDistance(const Vector2Int &a, const Vector2Int &b) {
            int xDif = b.x - a.x;
            int yDif = b.y - a.y;
            return xDif * xDif + yDif * yDif;
        }
        
        Vector2Int Vector2Int::Scale(const Vector2Int &a, const Vector2Int &b) {
            return {a.x * b.x, a.y * b.y};
        }
        
        Vector2Int Vector2Int::Lerp(const Vector2Int &a, const Vector2Int &b, int t) {
            int oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
        }
        
        Vector2Int Vector2Int::LerpClamped(const Vector2Int &a, const Vector2Int &b, int t) {
            if (t < 0) {
                return a;
            }
            if (t > 1) {
                return b;
            }
            int oneMinusT = 1 - t;
            return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
        }
        
        Vector2Int Vector2Int::InverseLerp(const Vector2Int &a, const Vector2Int &b, int t) {
            return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y)};
        }
        
        Vector2Int Vector2Int::Max(const Vector2Int &a, const Vector2Int &b) {
            return {Math::Max(a.x, b.x), Math::Max(a.y, b.y)};
        }
        
        Vector2Int Vector2Int::Min(const Vector2Int &a, const Vector2Int &b) {
            return {Math::Min(a.x, b.x), Math::Min(a.y, b.y)};
        }
        
        Vector2Int Vector2Int::MoveTowards(const Vector2Int &current, const Vector2Int &target, int maxDistanceDelta) {
            if (maxDistanceDelta > 1) {
                return target;
            }
            int oneMinusT = 1 - maxDistanceDelta;
            return {current.x * oneMinusT + target.x * maxDistanceDelta,
                    current.y * oneMinusT + target.y * maxDistanceDelta};
            
        }
        
        Vector2Int Vector2Int::Reflect(const Vector2Int &inDirection, const Vector2Int &inNormal) {
            return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
        }
        
        int Vector2Int::Dot(const Vector2Int &other) const {
            return Dot(*this, other);
        }
        
        
        float Vector2Int::Distance(const Vector2Int &b) const {
            return Distance(*this, b);
        }
        
        int Vector2Int::SqrDistance(const Vector2Int &b) const {
            return SqrDistance(*this, b);
        }
        
        
        Vector2Int Vector2Int::Scale(const Vector2Int &b) const {
            return Scale(*this, b);
        }
        
        Vector2Int Vector2Int::Lerp(const Vector2Int &b, int t) const {
            return Lerp(*this, b, t);
        }
        
        Vector2Int Vector2Int::LerpClamped(const Vector2Int &b, int t) const {
            return LerpClamped(*this, b, t);
        }
        
        Vector2Int Vector2Int::InverseLerp(const Vector2Int &b, int t) const {
            return InverseLerp(*this, b, t);
        }
        
        
        Vector2Int Vector2Int::MoveTowards(const Vector2Int &target, int maxDistanceDelta) const {
            return MoveTowards(*this, target, maxDistanceDelta);
        }
        
        Vector2Int Vector2Int::Reflect(const Vector2Int &inNormal) const {
            return Reflect(*this, inNormal);
        }
        
        
        
        Vector2Int Vector2Int::xx() const { return {x, x}; }
        
        Vector2Int Vector2Int::xy() const { return {x, y}; }
        
        Vector2Int Vector2Int::yx() const { return {y, x}; }
        
        Vector2Int Vector2Int::yy() const { return {y, y}; }
        
        int Vector2Int::LexicographicCompare(const Vector2Int &other) const {
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
        
        int Vector2Int::MagnitudeCompare(const Vector2Int &other) const {
            int mag = SqrMagnitude();
            int otherMag = other.SqrMagnitude();
            if (mag < otherMag) {
                return -1;
            }
            if (mag > otherMag) {
                return 1;
            }
            return 0;
        }
        
        int Vector2Int::SumCompare(const Vector2Int &other) const {
            int sum = Sum();
            int otherSum = other.Sum();
            if (sum < otherSum) {
                return -1;
            } else if (sum > otherSum) {
                return 1;
            }
            return 0;
        }
}

















