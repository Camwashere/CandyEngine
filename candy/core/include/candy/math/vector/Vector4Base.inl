#pragma once

namespace Candy::Math
{
    template<typename T>
    constexpr T VectorBase<T, 4>::Dot(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
    
    template<typename T>
    constexpr T VectorBase<T, 4>::Distance(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        float xDif = (b.x - a.x);
        float yDif = (b.y - a.y);
        float zDif = (b.z - a.z);
        float wDif = (b.w - a.w);
        return Math::Sqrt(xDif * xDif + yDif * yDif + zDif * zDif + wDif*wDif);
    }
    template<typename T>
    constexpr T VectorBase<T, 4>::SqrDistance(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        T xDif = b.x - a.x;
        T yDif = b.y - a.y;
        T zDif = (b.z - a.z);
        return xDif * xDif + yDif * yDif + zDif * zDif;
    }
   
    
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Scale(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Lerp(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t)
    {
        T oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t, a.w*oneMinusT + b.w * t};
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::LerpClamped(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t)
    {
        if (t < 0) {
            return a;
        }
        if (t > 1) {
            return b;
        }
        return Lerp(a, b, t);
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::InverseLerp(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t)
    {
        return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z), (t-a.w)/(b.w-a.w)};
    }
    
   
   
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::MoveTowards(const VectorBase<T, 4> &current, const VectorBase<T, 4> &target, float maxDistanceDelta)
    {
        if (maxDistanceDelta > 1) {
            return target;
        }
        float oneMinusT = 1 - maxDistanceDelta;
        return {current.x * oneMinusT + target.x * maxDistanceDelta,
                current.y * oneMinusT + target.y * maxDistanceDelta,
                current.z * oneMinusT + target.z * maxDistanceDelta,
                current.w * oneMinusT + target.w * maxDistanceDelta};
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Reflect(const VectorBase<T, 4> &inDirection, const VectorBase<T, 4> &inNormal)
    {
        return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Max(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        return {Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z), Math::Max(a.w, b.w)};
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Min(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b)
    {
        return {Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z), Math::Min(a.w, b.w)};
    }
    template<typename T>
    constexpr VectorBase<T, 4> VectorBase<T, 4>::Normalize(const VectorBase<T, 4> &vec)
    {
        return vec / vec.Magnitude();
    }
    template<typename T>
    VectorBase<T, 4>::VectorBase()=default;
    template<typename T>
    VectorBase<T, 4>::VectorBase(T value) : data{value, value, value, value}{}
  template<typename T>
  VectorBase<T, 4>::VectorBase(T xValue, T yValue, T zValue) : data{xValue, yValue, zValue, 0.0f}{}
    template<typename T>
    VectorBase<T, 4>::VectorBase(T xValue, T yValue, T zValue, T wValue) : data{xValue, yValue, zValue, wValue}{}
  
    template<typename T>
    VectorBase<T, 4>::VectorBase(const VectorBase<T, 3>& vec3, T wValue) : data{vec3.x, vec3.y, vec3.z, wValue}{}
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    VectorBase<T, 4>::VectorBase(const VectorBase<U, 4> &other) : data{static_cast<T>(other.x), static_cast<T>(other.y), static_cast<T>(other.z), static_cast<T>(other.w)}{}
    
    template<typename T> template <typename U, typename E>
    requires(std::is_arithmetic_v<U>)
    constexpr VectorBase<T, 4>::VectorBase(const VectorExpression<U,E>& expr) : data{expr[0], expr[1], expr[2], expr[3]}
    {
        
    }
    
    
    
    
    // ITERATOR
    
    
    // ITERATOR
    template<typename T>
    VectorBase<T, 4>::Iterator::Iterator(T *pointer)
    { ptr = pointer; }
    
    template<typename T>
    T &VectorBase<T, 4>::Iterator::operator*() const
    { return *ptr; }
    
    template<typename T>
    T *VectorBase<T, 4>::Iterator::operator->() const
    { return ptr; }
    
    template<typename T>
    VectorBase<T, 4>::Iterator &VectorBase<T, 4>::Iterator::operator++()
    {
        ++ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 4>::Iterator VectorBase<T, 4>::Iterator::operator++(int) //NOLINT
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 4>::Iterator &VectorBase<T, 4>::Iterator::operator+=(int i)
    {
        ptr += i;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 4>::Iterator &VectorBase<T, 4>::Iterator::operator--()
    {
        --ptr;
        return *this;
    }
    
    template<typename T>
    VectorBase<T, 4>::Iterator VectorBase<T, 4>::Iterator::operator--(int) //NOLINT
    {
        Iterator temp = *this;
        --(*this);
        return temp;
    }
    
    template<typename T>
    VectorBase<T, 4>::Iterator &VectorBase<T, 4>::Iterator::operator-=(int i)
    {
        ptr -= i;
        return *this;
    }
    template<typename T>
    VectorBase<T, 4>::Iterator VectorBase<T, 4>::Iterator::operator+(const std::ptrdiff_t other) const
    { return ptr + other; }
    
    template<typename T>
    std::ptrdiff_t VectorBase<T, 4>::Iterator::operator-(const Iterator &other) const
    { return ptr - other.ptr; }
    
    template<typename T>
    T &VectorBase<T, 4>::Iterator::operator[](std::ptrdiff_t index) const
    { return ptr[index]; }
    
    template<typename T>
    auto VectorBase<T, 4>::Iterator::operator<=>(const Iterator &) const = default;
    template<typename T>
    VectorBase<T, 4>::Iterator VectorBase<T, 4>::begin()
    { return Iterator{data}; }
    template<typename T>
    VectorBase<T, 4>::Iterator VectorBase<T, 4>::end()
    { return Iterator{data + 4}; }
    
    
    
    
    
    
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator==(const VectorBase<T, 4> &other) const
    { return x == other.x && y == other.y && z == other.z && w == other.w; }
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator!=(const VectorBase<T, 4> &other) const
    { return !(x == other.x && y == other.y && z == other.z && w == other.w); }
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator<(const VectorBase<T, 4> &other) const
    { return x < other.x && y < other.y && z < other.z && w < other.w; }
    
    
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator<=(const VectorBase<T, 4> &other) const
    { return x <= other.x && y <= other.y && z<=other.z && w <= other.w; }
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator>(const VectorBase<T, 4> &other) const
    { return x > other.x && y > other.y && z>other.z && w > other.w; }
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator>=(const VectorBase<T, 4> &other) const
    { return x >= other.x && y >= other.y && z>=other.z && w >= other.w; }
    
    template<typename T>
    inline bool VectorBase<T, 4>::operator<(T other) const
    { return x < other && y < other && z < other && w < other.w; }
    
    template<typename T>
    bool VectorBase<T, 4>::operator<=(T other) const
    {return x <= other && y <= other && z<other && w < other;}
    
    template<typename T>
    bool VectorBase<T, 4>::operator>(T other) const
    { return x > other && y > other && z > other && w > other;}
    template<typename T>
    bool VectorBase<T, 4>::operator>=(T other) const
    { return x >= other && y >= other && z>= other && w >= other; }
    
    template<typename T>
    constexpr T &VectorBase<T, 4>::operator[](std::size_t index) noexcept
    { return data[index]; }
    
    template<typename T>
    constexpr T VectorBase<T, 4>::operator[](std::size_t index) const
    { return data[index]; }
    
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::operator-() const
    { return {-x, -y, -z, -w}; }
    
    template<typename T>
    void VectorBase<T, 4>::operator+=(const VectorBase<T, 4> &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }
    
    template<typename T>
    void VectorBase<T, 4>::operator-=(const VectorBase<T, 4> &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }
    
    template<typename T>
    void VectorBase<T, 4>::operator*=(const VectorBase<T, 4> &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
    }
    
    template<typename T>
    void VectorBase<T, 4>::operator/=(const VectorBase<T, 4> &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
    }
    
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator+=(const VectorBase<U, 4> &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator-=(const VectorBase<U, 4> &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator*=(const VectorBase<U, 4> &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator/=(const VectorBase<U, 4> &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator*=(U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }
    
    template<typename T> template<typename U>
    requires(std::is_convertible_v<U, T>)
    void VectorBase<T, 4>::operator/=(U scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }
    
    
    
    
    
    template<typename T>
    void VectorBase<T, 4>::Set(T value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }
    
    template<typename T>
    void VectorBase<T, 4>::Set(T xValue, T yValue, T zValue, T wValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
        w = wValue;
    }
    
    template<typename T>
    void VectorBase<T, 4>::Set(const VectorBase<T, 4> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }
    
    template<typename T>
    void VectorBase<T, 4>::AddToAll(T value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
    }
    
    template<typename T>
    void VectorBase<T, 4>::SubtractFromAll(T value)
    {
        x -= -value;
        y -= value;
        z -= value;
        w -= value;
    }
    
    template<typename T>
    void VectorBase<T, 4>::Normalize()
    {
        T mag = Magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
    }
    
    
    
    template<typename T>
    void VectorBase<T, 4>::ScaleToLength(T newLength)
    {
        Normalize();
        x *= newLength;
        y *= newLength;
        z *= newLength;
        w *= newLength;
    }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::Normalized() const
    {
        float mag = Magnitude();
        return {x / mag, y / mag, z/mag, w/mag};
    }
    
    template<typename T>
    T VectorBase<T, 4>::Magnitude() const
    { return Sqrt(x * x + y * y + z*z + w*w); }
    
    template<typename T>
    T VectorBase<T, 4>::SqrMagnitude() const
    { return x * x + y * y + z*z + w*w; }
    
    template<typename T>
    T VectorBase<T, 4>::Dot(const VectorBase<T, 4> &other) const
    { return Dot(*this, other); }
    
    
    
    template<typename T>
    T VectorBase<T, 4>::Distance(const VectorBase<T, 4> &b) const
    { return Distance(*this, b); }
    
    template<typename T>
    T VectorBase<T, 4>::SqrDistance(const VectorBase<T, 4> &b) const
    { return SqrDistance(*this, b); }

    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::Scale(const VectorBase<T, 4> &b) const
    { return Scale(*this, b); }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::Lerp(const VectorBase<T, 4> &b, T t) const
    {
        return Lerp(*this, b, t);
    }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::LerpClamped(const VectorBase<T, 4> &b, T t) const
    { return LerpClamped(*this, b, t); }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::InverseLerp(const VectorBase<T, 4> &b, T t) const
    { return InverseLerp(*this, b, t); }
    
    
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::MoveTowards(const VectorBase<T, 4> &target, T maxDistanceDelta) const
    { return MoveTowards(*this, target, maxDistanceDelta); }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::Reflect(const VectorBase<T, 4> &inNormal) const
    { return Reflect(*this, inNormal); }
    
    template<typename T>
    VectorBase<T, 4> VectorBase<T, 4>::ScaledToLength(T newLength) const
    { return newLength * Normalized(); }
    
    template<typename T>
    T VectorBase<T, 4>::Sum() const
    { return x + y + z + w; }
    
    
    
    template<typename T>
    T VectorBase<T, 4>::Product() const
    { return x * y * z * w; }
    
    
    template<typename T>
    T VectorBase<T, 4>::MaxValue() const
    { return Math::Max(x, y, z, w); }
    
    template<typename T>
    T VectorBase<T, 4>::MinValue() const
    { return Math::Min(x, y, z, w); }
    
    template<typename T>
    T VectorBase<T, 4>::Average() const
    { return Sum() / (T) 4; }
  
    template<typename T>
  std::string VectorBase<T, 4>::ToString()const
    {
      return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + ")";
    }
    
    template<typename T>  int VectorBase<T, 4>::LexicographicCompare(const VectorBase<T, 4> &other) const
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
        if (w < other.w)
        {
            return -1;
        }
        else if (w > other.w)
        {
            return 1;
        }
        return 0;
    }
    
    template<typename T>  int VectorBase<T, 4>::MagnitudeCompare(const VectorBase<T, 4> &other) const
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
    
    template<typename T>  int VectorBase<T, 4>::SumCompare(const VectorBase<T, 4> &other) const
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
    constexpr VectorBase<T, 2> VectorBase<T, 4>::xx() const { return {x, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::xy() const { return {x, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::xz() const { return {x, z}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::yx() const { return {y, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::yy() const { return {y, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::yz() const { return {y, z}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::zx() const { return {z, x}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::zy() const { return {z, y}; }
    template<typename T>
    constexpr VectorBase<T, 2> VectorBase<T, 4>::zz() const { return {z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xxx() const { return {x, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xxy() const { return {x, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xxz() const { return {x, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xyx() const { return {x, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xyy() const { return {x, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xyz() const { return {x, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xzx() const { return {x, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xzy() const { return {x, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::xzz() const { return {x, z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yxx() const { return {y, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yxy() const { return {y, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yxz() const { return {y, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yyx() const { return {y, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yyy() const { return {y, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yyz() const { return {y, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yzx() const { return {y, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yzy() const { return {y, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::yzz() const { return {y, z, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zxx() const { return {z, x, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zxy() const { return {z, x, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zxz() const { return {z, x, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zyx() const { return {z, y, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zyy() const { return {z, y, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zyz() const { return {z, y, z}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zzx() const { return {z, z, x}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zzy() const { return {z, z, y}; }
    template<typename T>
    constexpr VectorBase<T, 3> VectorBase<T, 4>::zzz() const { return {z, z, z}; }
    
    template<typename T>
    constexpr inline size_t VectorBase<T, 4>::Dimensions()const{return 4;}
    template<typename T>
    constexpr inline size_t VectorBase<T, 4>::Size()const{return 4;}
    
}

template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 4> &vec)
{
  ostream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
  return ostream;
}