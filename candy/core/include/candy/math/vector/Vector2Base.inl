#pragma once



namespace Candy::Math
{
    
    template<typename T>
    T VectorBase<T, 2>::Dot(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    { return a.x * b.x + a.y * b.y; }
    
    template<typename T>
    T VectorBase<T, 2>::Determinant(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    { return a.x * b.y - a.y * b.x; }
    
    template<typename T>
    T VectorBase<T, 2>::Distance(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    {
        T xDif = (b.x - a.x);
        T yDif = (b.y - a.y);
        return Sqrt(xDif * xDif + yDif * yDif);
    }
    
    template<typename T>
    T VectorBase<T, 2>::SqrDistance(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    {
        T xDif = b.x - a.x;
        T yDif = b.y - a.y;
        return xDif * xDif + yDif * yDif;
    }
    
    template<typename T>
    T VectorBase<T, 2>::Slope(const VectorBase<T, 2> &start, const VectorBase<T, 2> &end)
    { return (end.y - start.y) / (end.x - start.x); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Scale(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    { return {a.x * b.x, a.y * b.y}; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Lerp(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t)
    {
        T oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
    }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::LerpClamped(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t)
    {
        if (t < 0)
        {
            return a;
        }
        if (t > 1)
        {
            return b;
        }
        float oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t};
    }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::InverseLerp(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t)
    { return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y)}; }
    
    template<typename T>
    float VectorBase<T, 2>::Angle(const VectorBase<T, 2> &from, const VectorBase<T, 2> &to)
    {
        float d = (from.x * to.x + from.y * to.y) / (from.Magnitude() * to.Magnitude());
        return Math::Acos(Math::Clamp(d, -1.0f, 1.0f));
    }
    
    template<typename T>
    float VectorBase<T, 2>::SignedAngle(const VectorBase<T, 2> &from, const VectorBase<T, 2> &to)
    { return Math::Atan2(from.x * to.y - from.y * to.x, from.x * to.x + from.y * to.y); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::PerpendicularClockwise(const VectorBase<T, 2> &vec)
    { return {vec.y, -vec.x}; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::PerpendicularCounterClockwise(const VectorBase<T, 2> &vec)
    { return {-vec.y, vec.x}; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::MoveTowards(const VectorBase<T, 2> &current, const VectorBase<T, 2> &target, float maxDistanceDelta)
    {
        if (maxDistanceDelta > 1)
        {
            return target;
        }
        float oneMinusT = 1 - maxDistanceDelta;
        return {current.x * oneMinusT + target.x * maxDistanceDelta, current.y * oneMinusT + target.y * maxDistanceDelta};
    }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Reflect(const VectorBase<T, 2> &inDirection, const VectorBase<T, 2> &inNormal)
    { return inDirection - 2 * Dot(inDirection, inNormal) * inNormal; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Max(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    { return {Math::Max(a.x, b.x), Math::Max(a.y, b.y)}; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Min(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b)
    { return {Math::Min(a.x, b.x), Math::Min(a.y, b.y)}; }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Normalize(const VectorBase<T, 2> &vec)
    { return vec / vec.Magnitude(); }
    
    
    template<typename T>
    VectorBase<T, 2>::VectorBase() = default;
    
    template<typename T>
    VectorBase<T, 2>::VectorBase(T value) : data{value, value}
    {}
    
    template<typename T>
    constexpr VectorBase<T, 2>::VectorBase(T xValue, T yValue) : x(xValue), y(yValue)
    {}
    
    template<typename T>
    template<typename U>
    requires(std::is_convertible_v<U, T>) VectorBase<T, 2>::VectorBase(const VectorBase<U, 2> &other) : data{other[0], other[1]}
    {};
    
    
    template<typename T>
    template<typename U, typename E>
    requires(std::is_arithmetic_v<U>) VectorBase<T, 2>::VectorBase(const VectorExpression<U, E> &expr) : data{expr[0], expr[1]}
    {}
    
    
    
    
    // ITERATOR
    template<typename T>
    VectorBase<T, 2>::Iterator::Iterator(T *pointer)
    { ptr = pointer; }
    
    template<typename T>
    T &VectorBase<T, 2>::Iterator::operator*() const
    { return *ptr; }
    
    template<typename T>
    T *VectorBase<T, 2>::Iterator::operator->() const
    { return ptr; }
    
    template<typename T>
    VectorBase<T, 2>::Iterator &VectorBase<T, 2>::Iterator::operator++()
    {
        ++ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 2>::Iterator VectorBase<T, 2>::Iterator::operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 2>::Iterator &VectorBase<T, 2>::Iterator::operator+=(int i)
    {
        ptr += i;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 2>::Iterator &VectorBase<T, 2>::Iterator::operator--()
    {
        --ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 2>::Iterator VectorBase<T, 2>::Iterator::operator--(int)
    {
        Iterator temp = *this;
        --(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 2>::Iterator &VectorBase<T, 2>::Iterator::operator-=(int i)
    {
        ptr -= i;
        return *this;
    }
    template<typename T>
    VectorBase<T, 2>::Iterator VectorBase<T, 2>::Iterator::operator+(const std::ptrdiff_t other) const
    { return ptr + other; }
    
    template<typename T>
    std::ptrdiff_t VectorBase<T, 2>::Iterator::operator-(const Iterator &other) const
    { return ptr - other.ptr; }
    
    template<typename T>
    T &VectorBase<T, 2>::Iterator::operator[](std::ptrdiff_t index) const
    { return ptr[index]; }
    
    template<typename T>
    auto VectorBase<T, 2>::Iterator::operator<=>(const Iterator &) const = default;
    template<typename T>
    VectorBase<T, 2>::Iterator VectorBase<T, 2>::begin()
    { return Iterator{data}; }
    template<typename T>
    VectorBase<T, 2>::Iterator VectorBase<T, 2>::end()
    { return Iterator{data + 2}; }
    
    
    
    
    
    
    
    
    
    
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator==(const VectorBase<T, 2> &other) const
    { return x == other.x && y == other.y; }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator!=(const VectorBase<T, 2> &other) const
    { return !(x == other.x && y == other.y); }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator<(const VectorBase<T, 2> &other) const
    { return x < other.x && y < other.y; }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator<=(const VectorBase<T, 2> &other) const
    { return x <= other.x && y <= other.y; }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator>(const VectorBase<T, 2> &other) const
    { return x > other.x && y > other.y; }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator>=(const VectorBase<T, 2> &other) const
    { return x >= other.x && y >= other.y; }
    
    template<typename T>
    inline bool VectorBase<T, 2>::operator<(T other) const
    { return x < other && y < other; }
    
    template<typename T>
    bool VectorBase<T, 2>::operator<=(T other) const
    {return x <= other && y <= other;}
    
    template<typename T>
    bool VectorBase<T, 2>::operator>(T other) const
    { return x > other && y > other;}
    template<typename T>
    bool VectorBase<T, 2>::operator>=(T other) const
    { return x >= other && y >= other; }
    
    template<typename T>
     T &VectorBase<T, 2>::operator[](std::size_t index) noexcept
    { return data[index]; }
    
    template<typename T>
     T VectorBase<T, 2>::operator[](std::size_t index) const
    { return data[index]; }
    
    
    template<typename T>
     VectorBase<T, 2> VectorBase<T, 2>::operator-() const
    { return {-x, -y}; }
    
    template<typename T>
     void VectorBase<T, 2>::operator+=(const VectorBase<T, 2> &other)
    {
        x += other.x;
        y += other.y;
    }
    
    template<typename T>
     void VectorBase<T, 2>::operator-=(const VectorBase<T, 2> &other)
    {
        x -= other.x;
        y -= other.y;
    }
    
    template<typename T>
     void VectorBase<T, 2>::operator*=(const VectorBase<T, 2> &other)
    {
        x *= other.x;
        y *= other.y;
    }
    
    template<typename T>
     void VectorBase<T, 2>::operator/=(const VectorBase<T, 2> &other)
    {
        x /= other.x;
        y /= other.y;
    }
    
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator+=(const VectorBase<U, 2> &other)
    {
        x += other.x;
        y += other.y;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator-=(const VectorBase<U, 2> &other)
    {
        x -= other.x;
        y -= other.y;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator*=(const VectorBase<U, 2> &other)
    {
        x *= other.x;
        y *= other.y;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator/=(const VectorBase<U, 2> &other)
    {
        x /= other.x;
        y /= other.y;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator*=(U scalar)
    {
        x *= scalar;
        y *= scalar;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 2>::operator/=(U scalar)
    {
        x /= scalar;
        y /= scalar;
    }
    
    
    
    
    template<typename T>
    void VectorBase<T, 2>::Set(T value)
    {
        x = value;
        y = value;
    }
    
    template<typename T>
    void VectorBase<T, 2>::Set(T xValue, T yValue)
    {
        x = xValue;
        y = yValue;
    }
    
    template<typename T>
    void VectorBase<T, 2>::Set(const VectorBase<T, 2> &other)
    {
        x = other.x;
        y = other.y;
    }
    
    template<typename T>
    void VectorBase<T, 2>::AddToAll(T value)
    {
        x += value;
        y += value;
    }
    
    template<typename T>
    void VectorBase<T, 2>::SubtractFromAll(T value)
    {
        x -= -value;
        y -= value;
    }
    
    template<typename T>
    void VectorBase<T, 2>::Normalize()
    {
        T mag = Magnitude();
        x /= mag;
        y /= mag;
    }
    
    
    template<typename T>
    void VectorBase<T, 2>::ScaleToLength(T newLength)
    {
        Normalize();
        x *= newLength;
        y *= newLength;
    }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Normalized() const
    {
        float mag = Magnitude();
        return {x / mag, y / mag};
    }
    
    template<typename T>
    T VectorBase<T, 2>::Magnitude() const
    { return Sqrt(x * x + y * y); }
    
    template<typename T>
    T VectorBase<T, 2>::SqrMagnitude() const
    { return x * x + y * y; }
    
    template<typename T>
    T VectorBase<T, 2>::Dot(const VectorBase<T, 2> &other) const
    { return Dot(*this, other); }
    
    template<typename T>
    T VectorBase<T, 2>::Determinant(const VectorBase<T, 2> &b) const
    { return Determinant(*this, b); }
    
    template<typename T>
    T VectorBase<T, 2>::Distance(const VectorBase<T, 2> &b) const
    { return Distance(*this, b); }
    
    template<typename T>
    T VectorBase<T, 2>::SqrDistance(const VectorBase<T, 2> &b) const
    { return SqrDistance(*this, b); }
    
    template<typename T>
    T VectorBase<T, 2>::Slope(const VectorBase<T, 2> &end) const
    { return Slope(*this, end); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Scale(const VectorBase<T, 2> &b) const
    { return Scale(*this, b); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Lerp(const VectorBase<T, 2> &b, T t) const
    {
        return Lerp(*this, b, t);
    }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::LerpClamped(const VectorBase<T, 2> &b, T t) const
    { return LerpClamped(*this, b, t); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::InverseLerp(const VectorBase<T, 2> &b, T t) const
    { return InverseLerp(*this, b, t); }
    
    template<typename T>
    T VectorBase<T, 2>::Angle(const VectorBase<T, 2> &to) const
    { return Angle(*this, to); }
    
    template<typename T>
    T VectorBase<T, 2>::SignedAngle(const VectorBase<T, 2> &to) const
    { return SignedAngle(*this, to); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::PerpendicularClockwise() const
    { return PerpendicularClockwise(*this); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::PerpendicularCounterClockwise() const
    { return PerpendicularCounterClockwise(*this); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::MoveTowards(const VectorBase<T, 2> &target, T maxDistanceDelta) const
    { return MoveTowards(*this, target, maxDistanceDelta); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::Reflect(const VectorBase<T, 2> &inNormal) const
    { return Reflect(*this, inNormal); }
    
    template<typename T>
    VectorBase<T, 2> VectorBase<T, 2>::ScaledToLength(T newLength) const
    { return newLength * Normalized(); }
    
    template<typename T>
    T VectorBase<T, 2>::Sum() const
    { return x + y; }
    
    template<typename T>
    T VectorBase<T, 2>::Difference() const
    { return x - y; }
    
    template<typename T>
    T VectorBase<T, 2>::AbsDifference() const
    { return Math::Abs(x - y); }
    
    template<typename T>
    T VectorBase<T, 2>::Product() const
    { return x * y; }
    
    template<typename T>
    T VectorBase<T, 2>::Quotient() const
    { return x / y; }
    
    template<typename T>
    T VectorBase<T, 2>::MaxValue() const
    { return Math::Max(x, y); }
    
    template<typename T>
    T VectorBase<T, 2>::MinValue() const
    { return Math::Min(x, y); }
    
    template<typename T>
    T VectorBase<T, 2>::Average() const
    { return (x + y) / (T) 2; }
    
    
    
    
    template<typename T>   VectorBase<T, 2> VectorBase<T, 2>:: xx() const
    { return {x, x}; }
    
    template<typename T>   VectorBase<T, 2> VectorBase<T, 2>:: xy() const
    { return {x, y}; }
    
    template<typename T>   VectorBase<T, 2> VectorBase<T, 2>:: yx() const
    { return {y, x}; }
    
    template<typename T>   VectorBase<T, 2> VectorBase<T, 2>:: yy() const
    { return {y, y}; }
    
    template<typename T>   T VectorBase<T, 2>::ToVector1() const
    { return x; }
    
    template<typename T>   VectorBase<T, 3> VectorBase<T, 2>::ToVector3() const
    { return {x, y, (T) 0}; }
    
    template<typename T>   VectorBase<T, 4> VectorBase<T, 2>::ToVector4() const
    { return {x, y, (T) 0, (T) 0}; }
    
    template<typename T>   std::string VectorBase<T, 2>::ToString() const
    { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
    
    
    template<typename T>  int VectorBase<T, 2>::LexicographicCompare(const VectorBase<T, 2> &other) const
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
        return 0;
    }
    
    template<typename T>  int VectorBase<T, 2>::MagnitudeCompare(const VectorBase<T, 2> &other) const
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
    
    template<typename T>  int VectorBase<T, 2>::SumCompare(const VectorBase<T, 2> &other) const
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
    
    template<typename T>   size_t VectorBase<T, 2>::Dimensions() const
    { return 2; }
    
    template<typename T>   size_t VectorBase<T, 2>::Size() const
    { return 2; }
    
    
}

template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 2> &vec)
{
    ostream << "(" << vec.x << ", " << vec.y << ")";
    return ostream;
}