#pragma once
namespace Candy::Math
{
    template<typename T>
    constexpr T VectorBase<T, 3>::Dot(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    template<typename T>
    constexpr T VectorBase<T, 3>::Determinant(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return a.x * b.y - a.y * b.x;
    }
    template<typename T>
    constexpr T VectorBase<T, 3>::Distance(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        float xDif = (b.x - a.x);
        float yDif = (b.y - a.y);
        float zDif = (b.z - a.z);
        return Math::Sqrt(xDif * xDif + yDif * yDif + zDif * zDif);
    }
    template<typename T>
    constexpr T VectorBase<T, 3>::SqrDistance(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        T xDif = b.x - a.x;
        T yDif = b.y - a.y;
        T zDif = (b.z - a.z);
        return xDif * xDif + yDif * yDif + zDif * zDif;
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Cross(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    template<typename T>
    constexpr T VectorBase<T, 3>::Slope(const VectorBase<T, 3> &start, const VectorBase<T, 3> &end)
    {
        return (end.y - start.y) / (end.x - start.x);
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Scale(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Lerp(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t)
    {
        T oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::LerpClamped(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t)
    {
        if (t < 0) {
            return a;
        }
        if (t > 1) {
            return b;
        }
        float oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::InverseLerp(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t)
    {
        return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z)};
    }
    template<typename T>
    constexpr float VectorBase<T, 3>::Angle(const VectorBase<T, 3> &from, const VectorBase<T, 3> &to)
    {
        float d = (from.x * to.x + from.y * to.y) / (from.Magnitude() * to.Magnitude());
        return Math::Acos(Math::Clamp(d, -1.0f, 1.0f));
    }
    template<typename T>
    constexpr float VectorBase<T, 3>::SignedAngle(const VectorBase<T, 3> &from, const VectorBase<T, 3> &to)
    {
        return Math::Atan2(from.x * to.y - from.y * to.x, from.x * to.x + from.y * to.y);
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::PerpendicularClockwise(const VectorBase<T, 3> &vec)
    {
        return {vec.y, -vec.x};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::PerpendicularCounterClockwise(const VectorBase<T, 3> &vec)
    {
        return {-vec.y, vec.x};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::MoveTowards(const VectorBase<T, 3> &current, const VectorBase<T, 3> &target, float maxDistanceDelta)
    {
        if (maxDistanceDelta > 1) {
            return target;
        }
        float oneMinusT = 1 - maxDistanceDelta;
        return {current.x * oneMinusT + target.x * maxDistanceDelta,
                current.y * oneMinusT + target.y * maxDistanceDelta,
                current.z * oneMinusT + target.z * maxDistanceDelta};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Reflect(const VectorBase<T, 3> &inDirection, const VectorBase<T, 3> &inNormal)
    {
        return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Max(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return {Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z)};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Min(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b)
    {
        return {Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z)};
    }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::Normalize(const VectorBase<T, 3> &vec)
    {
        return vec / vec.Magnitude();
    }
    template<typename T>
    VectorBase<T, 3>::VectorBase()=default;
    template<typename T>
    VectorBase<T, 3>::VectorBase(T value) : data{value, value, value}{}
    template<typename T>
    VectorBase<T, 3>::VectorBase(T xValue, T yValue, T zValue) : data{xValue, yValue, zValue}{}
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    VectorBase<T, 3>::VectorBase(const VectorBase<U, 3> &other) : data{static_cast<T>(other.x), static_cast<T>(other.y), static_cast<T>(other.z)}{}
    
    template<typename T> template <typename U, typename E>
    requires(std::is_arithmetic_v<U>)
    constexpr VectorBase<T, 3>::VectorBase(const VectorExpression<U,E>& expr) : data{expr[0], expr[1], expr[2]}
    {
    
    }
    
    
    
    
    // ITERATOR
    
    
    // ITERATOR
    template<typename T>
    VectorBase<T, 3>::Iterator::Iterator(T *pointer)
    { ptr = pointer; }
    
    template<typename T>
    T &VectorBase<T, 3>::Iterator::operator*() const
    { return *ptr; }
    
    template<typename T>
    T *VectorBase<T, 3>::Iterator::operator->() const
    { return ptr; }
    
    template<typename T>
    VectorBase<T, 3>::Iterator &VectorBase<T, 3>::Iterator::operator++()
    {
        ++ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 3>::Iterator VectorBase<T, 3>::Iterator::operator++(int) //NOLINT
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 3>::Iterator &VectorBase<T, 3>::Iterator::operator+=(int i)
    {
        ptr += i;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 3>::Iterator &VectorBase<T, 3>::Iterator::operator--()
    {
        --ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 3>::Iterator VectorBase<T, 3>::Iterator::operator--(int) //NOLINT
    {
        Iterator temp = *this;
        --(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 3>::Iterator &VectorBase<T, 3>::Iterator::operator-=(int i)
    {
        ptr -= i;
        return *this;
    }
    template<typename T>
    VectorBase<T, 3>::Iterator VectorBase<T, 3>::Iterator::operator+(const std::ptrdiff_t other) const
    { return ptr + other; }
    
    template<typename T>
    std::ptrdiff_t VectorBase<T, 3>::Iterator::operator-(const Iterator &other) const
    { return ptr - other.ptr; }
    
    template<typename T>
    T &VectorBase<T, 3>::Iterator::operator[](std::ptrdiff_t index) const
    { return ptr[index]; }
    
    template<typename T>
    auto VectorBase<T, 3>::Iterator::operator<=>(const Iterator &) const = default;
    template<typename T>
    VectorBase<T, 3>::Iterator VectorBase<T, 3>::begin()
    { return Iterator{data}; }
    template<typename T>
    VectorBase<T, 3>::Iterator VectorBase<T, 3>::end()
    { return Iterator{data + 3}; }
    
    
    
    
    
    
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator==(const VectorBase<T, 3> &other) const
    { return x == other.x && y == other.y && z == other.z; }
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator!=(const VectorBase<T, 3> &other) const
    { return !(x == other.x && y == other.y && z == other.z); }
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator<(const VectorBase<T, 3> &other) const
    { return x < other.x && y < other.y && z < other.z; }
    
    
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator<=(const VectorBase<T, 3> &other) const
    { return x <= other.x && y <= other.y && z<=other.z ; }
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator>(const VectorBase<T, 3> &other) const
    { return x > other.x && y > other.y && z>other.z; }
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator>=(const VectorBase<T, 3> &other) const
    { return x >= other.x && y >= other.y && z>=other.z; }
    
    template<typename T>
    inline bool VectorBase<T, 3>::operator<(T other) const
    { return x < other && y < other && z < other; }
    
    template<typename T>
    bool VectorBase<T, 3>::operator<=(T other) const
    {return x <= other && y <= other && z<other;}
    
    template<typename T>
    bool VectorBase<T, 3>::operator>(T other) const
    { return x > other && y > other && z > other;}
    template<typename T>
    bool VectorBase<T, 3>::operator>=(T other) const
    { return x >= other && y >= other && z>= other; }
    
    template<typename T>
    constexpr T &VectorBase<T, 3>::operator[](std::size_t index) noexcept
    { return data[index]; }
    
    template<typename T>
    constexpr T VectorBase<T, 3>::operator[](std::size_t index) const
    { return data[index]; }
    
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::operator-() const
    { return {-x, -y, -z}; }
    
    template<typename T>
    void VectorBase<T, 3>::operator+=(const VectorBase<T, 3> &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    
    template<typename T>
    void VectorBase<T, 3>::operator-=(const VectorBase<T, 3> &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    
    template<typename T>
    void VectorBase<T, 3>::operator*=(const VectorBase<T, 3> &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }
    
    template<typename T>
    void VectorBase<T, 3>::operator/=(const VectorBase<T, 3> &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
    
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator+=(const VectorBase<U, 3> &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator-=(const VectorBase<U, 3> &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator*=(const VectorBase<U, 3> &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator/=(const VectorBase<U, 3> &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator*=(U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 3>::operator/=(U scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    
    
    
    
    
    template<typename T>
    void VectorBase<T, 3>::Set(T value)
    {
        x = value;
        y = value;
        z = value;
    }
    
    template<typename T>
    void VectorBase<T, 3>::Set(T xValue, T yValue, T zValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
    }
    
    template<typename T>
    void VectorBase<T, 3>::Set(const VectorBase<T, 3> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    
    template<typename T>
    void VectorBase<T, 3>::AddToAll(T value)
    {
        x += value;
        y += value;
        z += value;
    }
    
    template<typename T>
    void VectorBase<T, 3>::SubtractFromAll(T value)
    {
        x -= -value;
        y -= value;
        z -= value;
    }
    
    template<typename T>
    void VectorBase<T, 3>::Normalize()
    {
        T mag = Magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
    }
    
    
    
    template<typename T>
    void VectorBase<T, 3>::ScaleToLength(T newLength)
    {
        Normalize();
        x *= newLength;
        y *= newLength;
        z *= newLength;
    }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::Normalized() const
    {
        float mag = Magnitude();
        return {x / mag, y / mag, z/mag};
    }
    
    template<typename T>
    T VectorBase<T, 3>::Magnitude() const
    { return Sqrt(x * x + y * y + z*z); }
    
    template<typename T>
    T VectorBase<T, 3>::SqrMagnitude() const
    { return x * x + y * y + z*z; }
    
    template<typename T>
    T VectorBase<T, 3>::Dot(const VectorBase<T, 3> &other) const
    { return Dot(*this, other); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::Cross(const VectorBase<T, 3>& other)const
    {return Cross(*this, other);}
    
    template<typename T>
    T VectorBase<T, 3>::Determinant(const VectorBase<T, 3> &b) const
    { return Determinant(*this, b); }
    
    template<typename T>
    T VectorBase<T, 3>::Distance(const VectorBase<T, 3> &b) const
    { return Distance(*this, b); }
    
    template<typename T>
    T VectorBase<T, 3>::SqrDistance(const VectorBase<T, 3> &b) const
    { return SqrDistance(*this, b); }
    
    template<typename T>
    T VectorBase<T, 3>::Slope(const VectorBase<T, 3> &end) const
    { return Slope(*this, end); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::Scale(const VectorBase<T, 3> &b) const
    { return Scale(*this, b); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::Lerp(const VectorBase<T, 3> &b, T t) const
    {
        return Lerp(*this, b, t);
    }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::LerpClamped(const VectorBase<T, 3> &b, T t) const
    { return LerpClamped(*this, b, t); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::InverseLerp(const VectorBase<T, 3> &b, T t) const
    { return InverseLerp(*this, b, t); }
    
    template<typename T>
    T VectorBase<T, 3>::Angle(const VectorBase<T, 3> &to) const
    { return Angle(*this, to); }
    
    template<typename T>
    T VectorBase<T, 3>::SignedAngle(const VectorBase<T, 3> &to) const
    { return SignedAngle(*this, to); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::PerpendicularClockwise() const
    { return PerpendicularClockwise(*this); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::PerpendicularCounterClockwise() const
    { return PerpendicularCounterClockwise(*this); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::MoveTowards(const VectorBase<T, 3> &target, T maxDistanceDelta) const
    { return MoveTowards(*this, target, maxDistanceDelta); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::Reflect(const VectorBase<T, 3> &inNormal) const
    { return Reflect(*this, inNormal); }
    
    template<typename T>
    VectorBase<T, 3> VectorBase<T, 3>::ScaledToLength(T newLength) const
    { return newLength * Normalized(); }
    
    template<typename T>
    T VectorBase<T, 3>::Sum() const
    { return x + y + z; }
    
    
    
    template<typename T>
    T VectorBase<T, 3>::Product() const
    { return x * y * z; }
    
    
    template<typename T>
    T VectorBase<T, 3>::MaxValue() const
    { return Math::Max(x, y, z); }
    
    template<typename T>
    T VectorBase<T, 3>::MinValue() const
    { return Math::Min(x, y, z); }
    
    template<typename T>
    T VectorBase<T, 3>::Average() const
    { return Sum() / (T) 3; }
    
    template<typename T>  int VectorBase<T, 3>::LexicographicCompare(const VectorBase<T, 3> &other) const
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
    
    template<typename T>  int VectorBase<T, 3>::MagnitudeCompare(const VectorBase<T, 3> &other) const
    {
        float mag = SqrMagnitude();
        float otherMag = other.SqrMagnitude();
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
    
    template<typename T>  int VectorBase<T, 3>::SumCompare(const VectorBase<T, 3> &other) const
    {
        float sum = Sum();
        float otherSum = other.Sum();
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
    
    
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::xx() const { return {x, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::xy() const { return {x, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::xz() const { return {x, z}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::yx() const { return {y, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::yy() const { return {y, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::yz() const { return {y, z}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::zx() const { return {z, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::zy() const { return {z, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 3>::zz() const { return {z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xxx() const { return {x, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xxy() const { return {x, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xxz() const { return {x, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xyx() const { return {x, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xyy() const { return {x, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xyz() const { return {x, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xzx() const { return {x, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xzy() const { return {x, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::xzz() const { return {x, z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yxx() const { return {y, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yxy() const { return {y, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yxz() const { return {y, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yyx() const { return {y, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yyy() const { return {y, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yyz() const { return {y, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yzx() const { return {y, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yzy() const { return {y, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::yzz() const { return {y, z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zxx() const { return {z, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zxy() const { return {z, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zxz() const { return {z, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zyx() const { return {z, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zyy() const { return {z, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zyz() const { return {z, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zzx() const { return {z, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zzy() const { return {z, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 3>::zzz() const { return {z, z, z}; }
    
    template<typename T>
    constexpr inline size_t VectorBase<T, 3>::Dimensions()const{return 3;}
    template<typename T>
    constexpr inline size_t VectorBase<T, 3>::Size()const{return 3;}
    
}

template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 3> &vec)
{
  ostream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return ostream;
}