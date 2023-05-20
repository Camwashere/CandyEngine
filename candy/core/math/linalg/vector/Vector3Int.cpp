#include "Vector3Int.hpp"
#include "../../../../include/Candy/Math.hpp"


namespace Candy::Math
{
    
    
    Vector3Int::Vector3Int() : VectorBase<int, 3>(0, 0, 0)
    {}
    
    Vector3Int::Vector3Int(const Vector2 &vec, int zValue) : VectorBase<int, 3>(vec.x, vec.y, zValue)
    {}
    
    Vector3Int::Vector3Int(int value) : VectorBase<int, 3>(value)
    {}
    
    Vector3Int::Vector3Int(const Vector3Int &other) : VectorBase<int, 3>(other.x, other.y, other.z)
    {}
    
    Vector3Int::Vector3Int(const Vector2 &other) : VectorBase<int, 3>(other.x, other.y, 0)
    {}
    
    Vector3Int::Vector3Int(const Vector4 &other) : VectorBase<int, 3>(other.x, other.y, other.z)
    {}
    
    
    const Vector3Int Vector3Int::up(0, 1, 0);
    const Vector3Int Vector3Int::down(0, -1, 0);
    const Vector3Int Vector3Int::left(-1, 0, 0);
    const Vector3Int Vector3Int::right(1, 0, 0);
    const Vector3Int Vector3Int::forward(0, 0, 1);
    const Vector3Int Vector3Int::back(0, 0, -1);
    const Vector3Int Vector3Int::upLeft(-1, 1, 0);
    const Vector3Int Vector3Int::upRight(1, 1, 0);
    const Vector3Int Vector3Int::upForward(0, 1, 1);
    const Vector3Int Vector3Int::upBack(0, 1, -1);
    const Vector3Int Vector3Int::leftBack(-1, 0, -1);
    const Vector3Int Vector3Int::rightBack(1, 0, -1);
    const Vector3Int Vector3Int::leftForward(-1, 0, 1);
    const Vector3Int Vector3Int::rightForward(1, 0, 1);
    const Vector3Int Vector3Int::upLeftForward(-1, 1, 1);
    const Vector3Int Vector3Int::upLeftBack(-1, 1, -1);
    const Vector3Int Vector3Int::upRightForward(1, 1, 1);
    const Vector3Int Vector3Int::upRightBack(1, 1, -1);
    const Vector3Int Vector3Int::downLeft(-1, -1, 0);
    const Vector3Int Vector3Int::downRight(1, -1, 0);
    const Vector3Int Vector3Int::downForward(0, -1, 1);
    const Vector3Int Vector3Int::downBack(0, -1, -1);
    const Vector3Int Vector3Int::downLeftForward(-1, -1, 1);
    const Vector3Int Vector3Int::downLeftBack(-1, -1, -1);
    const Vector3Int Vector3Int::downRightForward(1, -1, 1);
    const Vector3Int Vector3Int::downRightBack(1, -1, -1);
    const Vector3Int Vector3Int::zero(0, 0, 0);
    const Vector3Int Vector3Int::one(1, 1, 1);
    const Vector3Int Vector3Int::negativeOne(-1, -1, -1);
    const Vector3Int Vector3Int::positiveInfinity(std::numeric_limits<int>::infinity(), std::numeric_limits<int>::infinity(), std::numeric_limits<int>::infinity());
    const Vector3Int Vector3Int::negativeInfinity(-std::numeric_limits<int>::infinity(), -std::numeric_limits<int>::infinity(), -std::numeric_limits<int>::infinity());
    
    
    bool Vector3Int::operator==(const Vector3Int &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool Vector3Int::operator!=(const Vector3Int &other) const
    {
        return !(x == other.x && y == other.y && z == other.z);
    }
    
    /*Vector3Int Vector3Int::operator+(const Vector3Int &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3Int Vector3Int::operator-(const Vector3Int &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }*/
    
    Vector3Int Vector3Int::operator*(const Vector3Int &other) const
    {
        return {x * other.x, y * other.y, z * other.z};
    }
    
    Vector3Int Vector3Int::operator/(const Vector3Int &other) const
    {
        return {x / other.x, y / other.y, z / other.z};
    }
    
    Vector3Int Vector3Int::operator^(const Vector3Int &other) const
    {
        return {Math::Pow(x, other.x), Math::Pow(y, other.y), Math::Pow(z, other.z)};
    }
    
    /*Vector3Int Vector3Int::operator*(int scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }*/
    /*Vector3Int Vector3Int::operator/(int scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }*/
    
    Vector3Int Vector3Int::operator^(int scalar) const
    {
        return {Math::Pow(x, scalar), Math::Pow(y, scalar), Math::Pow(z, scalar)};
    }
    
    void Vector3Int::operator+=(const Vector3Int &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    
    void Vector3Int::operator-=(const Vector3Int &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    
    void Vector3Int::operator*=(const Vector3Int &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }
    
    void Vector3Int::operator/=(const Vector3Int &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
    
    
    void Vector3Int::operator*=(int scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    
    void Vector3Int::operator/=(int scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    
    
    void Vector3Int::Set(int value)
    {
        x = value;
        y = value;
        z = value;
    }
    
    void Vector3Int::Set(int xValue, int yValue, int zValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
    }
    
    void Vector3Int::Set(const Vector2 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = 0;
    }
    
    void Vector3Int::Set(const Vector3Int &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    
    void Vector3Int::Set(const Vector4 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    
    float Vector3Int::Magnitude() const
    {
        return Math::Sqrt(x * x + y * y + z * z);
    }
    
    int Vector3Int::SqrMagnitude() const
    {
        return x * x + y * y + z * z;
    }
    
    Vector3Int::operator Vector2() const
    {
        return {(float) x, (float) y};
    }
    
    Vector3Int::operator Vector3() const
    {
        return {(float) x, (float) y, (float) z};
    }
    
    Vector3Int::operator Vector4() const
    {
        return {(float) x, (float) y, (float) z, 0};
    }
    
    Vector3Int::operator std::string() const
    {
        return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ')';
    }
    
    
    std::ostream &Vector3Int::operator<<(std::ostream &ostream) const
    {
        ostream << '(' << x << ',' << y << ',' << z << ')';
        return ostream;
    }
    
    std::ostream &operator<<(std::ostream &ostream, const Vector3Int &vec)
    {
        ostream << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
        return ostream;
    }
    
    Vector3Int operator^(int scalar, const Vector3Int &vec)
    {
        return {Math::Pow(scalar, vec.x), Math::Pow(scalar, vec.y), Math::Pow(scalar, vec.z)};
    }
    
    void Vector3Int::Clamp(int min, int max)
    {
        x = Math::Clamp(x, min, max);
        y = Math::Clamp(y, min, max);
        z = Math::Clamp(z, min, max);
    }
    
    void Vector3Int::Clamp(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax)
    {
        x = Math::Clamp(x, xMin, xMax);
        y = Math::Clamp(y, yMin, yMax);
        z = Math::Clamp(z, zMin, zMax);
        
    }
    
    void Vector3Int::Clamp(const Vector3Int &min, const Vector3Int &max)
    {
        x = Math::Clamp(x, min.x, max.x);
        y = Math::Clamp(y, min.y, max.y);
        z = Math::Clamp(z, min.z, max.z);
    }
    
    
    Vector3Int Vector3Int::Clamped(int valueMin, int valueMax) const
    {
        return {Math::Clamp(x, valueMin, valueMax), Math::Clamp(y, valueMin, valueMax), Math::Clamp(z, valueMin, valueMax)};
    }
    
    Vector3Int Vector3Int::Clamped(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const
    {
        return {Math::Clamp(x, xMin, xMax), Math::Clamp(y, yMin, yMax), Math::Clamp(z, zMin, zMax)};
    }
    
    Vector3Int Vector3Int::Clamped(const Vector3Int &min, const Vector3Int &max) const
    {
        return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z)};
    }
    
    
    bool Vector3Int::InRangeInclusive(int minValue, int maxValue) const
    {
        if (x < minValue || x > maxValue)
        {
            return false;
        }
        if (y < minValue || y > maxValue)
        {
            return false;
        }
        return !(z < minValue || z > maxValue);
    }
    
    bool Vector3Int::InRangeInclusive(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const
    {
        if (x < xMin || x > xMax)
        {
            return false;
        }
        if (y < yMin || y > yMax)
        {
            return false;
        }
        return !(z < zMin || z > zMax);
    }
    
    bool Vector3Int::InRangeInclusive(const Vector3Int &min, const Vector3Int &max) const
    {
        if (x < min.x || x > max.x)
        {
            return false;
        }
        if (y < min.y || y > max.y)
        {
            return false;
        }
        return !(z < min.z || z > max.z);
    }
    
    
    bool Vector3Int::InRangeInclusiveMin(int minValue, int maxValue) const
    {
        if (x < minValue || x >= maxValue)
        {
            return false;
        }
        if (y < minValue || y >= maxValue)
        {
            return false;
        }
        return !(z < minValue || z >= maxValue);
    }
    
    bool Vector3Int::InRangeInclusiveMin(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const
    {
        if (x < xMin || x >= xMax)
        {
            return false;
        }
        if (y < yMin || y >= yMax)
        {
            return false;
        }
        return !(z < zMin || z >= zMax);
    }
    
    bool Vector3Int::InRangeInclusiveMin(const Vector3Int &min, const Vector3Int &max) const
    {
        if (x < min.x || x >= max.x)
        {
            return false;
        }
        if (y < min.y || y >= max.y)
        {
            return false;
        }
        return !(z < min.z || z >= max.z);
    }
    
    
    bool Vector3Int::InRangeInclusiveMax(int minValue, int maxValue) const
    {
        if (x <= minValue || x > maxValue)
        {
            return false;
        }
        if (y <= minValue || y > maxValue)
        {
            return false;
        }
        return !(z <= minValue || z > maxValue);
    }
    
    bool Vector3Int::InRangeInclusiveMax(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const
    {
        if (x <= xMin || x > xMax)
        {
            return false;
        }
        if (y <= yMin || y > yMax)
        {
            return false;
        }
        return !(z <= zMin || z > zMax);
    }
    
    bool Vector3Int::InRangeInclusiveMax(const Vector3Int &min, const Vector3Int &max) const
    {
        if (x <= min.x || x > max.x)
        {
            return false;
        }
        if (y <= min.y || y > max.y)
        {
            return false;
        }
        return !(z <= min.z || z > max.z);
    }
    
    
    bool Vector3Int::InRangeExclusive(int minValue, int maxValue) const
    {
        if (x > minValue && x < maxValue)
        {
            if (y > minValue && y < maxValue)
            {
                return z > minValue && z < maxValue;
            }
        }
        return false;
    }
    
    bool Vector3Int::InRangeExclusive(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const
    {
        if (x > xMin && x < xMax)
        {
            if (y > yMin && y < yMax)
            {
                return z > zMin && z < zMax;
            }
        }
        return false;
    }
    
    bool Vector3Int::InRangeExclusive(const Vector3Int &min, const Vector3Int &max) const
    {
        if (x > min.x && x < max.x)
        {
            if (y > min.y && y < max.y)
            {
                return z > min.z && z < max.z;
            }
        }
        return false;
    }
    
    
    int Vector3Int::Sum() const
    {
        return x + y + z;
    }
    
    int Vector3Int::Product() const
    {
        return x * y * z;
    }
    
    int Vector3Int::Average() const
    {
        return (x + y + z) / 3.0f;
    }
    
    int Vector3Int::MaxValue() const
    {
        return Math::Max(Math::Max(x, y), z);
    }
    
    int Vector3Int::MinValue() const
    {
        return Math::Min(Math::Min(x, y), z);
    }
    
    int Vector3Int::Dot(const Vector3Int &a, const Vector3Int &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    
    Vector3Int Vector3Int::Average(const Vector3Int &a, const Vector3Int &b)
    {
        return (a + b) / 2;
    }
    
    
    Vector3Int Vector3Int::Cross(const Vector3Int &a, const Vector3Int &b)
    {
        return Vector3Int(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    
    float Vector3Int::Distance(const Vector3Int &a, const Vector3Int &b)
    {
        int xDif = (b.x - a.x);
        int yDif = (b.y - a.y);
        int zDif = (b.z - a.z);
        return Math::Sqrt(xDif * xDif + yDif * yDif + zDif * zDif);
    }
    
    int Vector3Int::SqrDistance(const Vector3Int &a, const Vector3Int &b)
    {
        int xDif = b.x - a.x;
        int yDif = b.y - a.y;
        int zDif = (b.z - a.z);
        return xDif * xDif + yDif * yDif + zDif * zDif;
    }
    
    Vector3Int Vector3Int::Scale(const Vector3Int &a, const Vector3Int &b)
    {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }
    
    Vector3Int Vector3Int::Lerp(const Vector3Int &a, const Vector3Int &b, int t)
    {
        int oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
    }
    
    Vector3Int Vector3Int::LerpClamped(const Vector3Int &a, const Vector3Int &b, int t)
    {
        if (t < 0)
        {
            return a;
        }
        if (t > 1)
        {
            return b;
        }
        int oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
    }
    
    Vector3Int Vector3Int::InverseLerp(const Vector3Int &a, const Vector3Int &b, int t)
    {
        return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z)};
    }
    
    Vector3Int Vector3Int::Max(const Vector3Int &a, const Vector3Int &b)
    {
        return {Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z)};
    }
    
    Vector3Int Vector3Int::Min(const Vector3Int &a, const Vector3Int &b)
    {
        return {Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z)};
    }
    
    Vector3Int Vector3Int::MoveTowards(const Vector3Int &current, const Vector3Int &target, int maxDistanceDelta)
    {
        if (maxDistanceDelta > 1)
        {
            return target;
        }
        int oneMinusT = 1 - maxDistanceDelta;
        return {current.x * oneMinusT + target.x * maxDistanceDelta, current.y * oneMinusT + target.y * maxDistanceDelta, current.z * oneMinusT + target.z * maxDistanceDelta};
        
    }
    
    Vector3Int Vector3Int::Reflect(const Vector3Int &inDirection, const Vector3Int &inNormal)
    {
        return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
    }
    
    int Vector3Int::Dot(const Vector3Int &other) const
    {
        return Dot(*this, other);
    }
    
    [[nodiscard]] Vector3Int Vector3Int::Cross(const Vector3Int &other) const
    {
        return Vector3Int::Cross(*this, other);
    }
    
    float Vector3Int::Distance(const Vector3Int &b) const
    {
        return Distance(*this, b);
    }
    
    int Vector3Int::SqrDistance(const Vector3Int &b) const
    {
        return SqrDistance(*this, b);
    }
    
    
    Vector3Int Vector3Int::Scale(const Vector3Int &b) const
    {
        return Scale(*this, b);
    }
    
    Vector3Int Vector3Int::Lerp(const Vector3Int &b, int t) const
    {
        return Lerp(*this, b, t);
    }
    
    Vector3Int Vector3Int::LerpClamped(const Vector3Int &b, int t) const
    {
        return LerpClamped(*this, b, t);
    }
    
    Vector3Int Vector3Int::InverseLerp(const Vector3Int &b, int t) const
    {
        return {InverseLerp(*this, b, t)};
    }
    
    Vector3Int Vector3Int::MoveTowards(const Vector3Int &target, int maxDistanceDelta) const
    {
        return MoveTowards(*this, target, maxDistanceDelta);
    }
    
    Vector3Int Vector3Int::Reflect(const Vector3Int &inNormal) const
    {
        return Reflect(*this, inNormal);
    }
    
    Vector2 Vector3Int::xx() const
    { return {(float) x, (float) x}; }
    
    Vector2 Vector3Int::xy() const
    { return {(float) x, (float) y}; }
    
    Vector2 Vector3Int::xz() const
    { return {(float) x, (float) z}; }
    
    Vector2 Vector3Int::yx() const
    { return {(float) y, (float) x}; }
    
    Vector2 Vector3Int::yy() const
    { return {(float) y, (float) y}; }
    
    Vector2 Vector3Int::yz() const
    { return {(float) y, (float) z}; }
    
    Vector2 Vector3Int::zx() const
    { return {(float) z, (float) x}; }
    
    Vector2 Vector3Int::zy() const
    { return {(float) z, (float) y}; }
    
    Vector2 Vector3Int::zz() const
    { return {(float) z, (float) z}; }
    
    Vector3Int Vector3Int::xxx() const
    { return {x, x, x}; }
    
    Vector3Int Vector3Int::xxy() const
    { return {x, x, y}; }
    
    Vector3Int Vector3Int::xxz() const
    { return {x, x, z}; }
    
    Vector3Int Vector3Int::xyx() const
    { return {x, y, x}; }
    
    Vector3Int Vector3Int::xyy() const
    { return {x, y, y}; }
    
    Vector3Int Vector3Int::xyz() const
    { return {x, y, z}; }
    
    Vector3Int Vector3Int::xzx() const
    { return {x, z, x}; }
    
    Vector3Int Vector3Int::xzy() const
    { return {x, z, y}; }
    
    Vector3Int Vector3Int::xzz() const
    { return {x, z, z}; }
    
    Vector3Int Vector3Int::yxx() const
    { return {y, x, x}; }
    
    Vector3Int Vector3Int::yxy() const
    { return {y, x, y}; }
    
    Vector3Int Vector3Int::yxz() const
    { return {y, x, z}; }
    
    Vector3Int Vector3Int::yyx() const
    { return {y, y, x}; }
    
    Vector3Int Vector3Int::yyy() const
    { return {y, y, y}; }
    
    Vector3Int Vector3Int::yyz() const
    { return {y, y, z}; }
    
    Vector3Int Vector3Int::yzx() const
    { return {y, z, x}; }
    
    Vector3Int Vector3Int::yzy() const
    { return {y, z, y}; }
    
    Vector3Int Vector3Int::yzz() const
    { return {y, z, z}; }
    
    Vector3Int Vector3Int::zxx() const
    { return {z, x, x}; }
    
    Vector3Int Vector3Int::zxy() const
    { return {z, x, y}; }
    
    Vector3Int Vector3Int::zxz() const
    { return {z, x, z}; }
    
    Vector3Int Vector3Int::zyx() const
    { return {z, y, x}; }
    
    Vector3Int Vector3Int::zyy() const
    { return {z, y, y}; }
    
    Vector3Int Vector3Int::zyz() const
    { return {z, y, z}; }
    
    Vector3Int Vector3Int::zzx() const
    { return {z, z, x}; }
    
    Vector3Int Vector3Int::zzy() const
    { return {z, z, y}; }
    
    Vector3Int Vector3Int::zzz() const
    { return {z, z, z}; }
    
    int Vector3Int::LexicographicCompare(const Vector3Int &other) const
    {
        if (x < other.x)
        {
            return -1;
        }
        else if (x > other.x)
        {
            return 1;
        }
        if (y < other.y)
        {
            return -1;
        }
        else if (y > other.y)
        {
            return 1;
        }
        if (z < other.z)
        {
            return -1;
        }
        else if (z > other.z)
        {
            return 1;
        }
        return 0;
    }
    
    int Vector3Int::MagnitudeCompare(const Vector3Int &other) const
    {
        int mag = SqrMagnitude();
        int otherMag = other.SqrMagnitude();
        if (mag < otherMag)
        {
            return -1;
        }
        if (mag > otherMag)
        {
            return 1;
        }
        return 0;
    }
    
    int Vector3Int::SumCompare(const Vector3Int &other) const
    {
        int sum = Sum();
        int otherSum = other.Sum();
        if (sum < otherSum)
        {
            return -1;
        }
        else if (sum > otherSum)
        {
            return 1;
        }
        return 0;
    }
}



















