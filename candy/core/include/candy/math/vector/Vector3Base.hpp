#pragma once
#include "VectorBase.hpp"
#include "VectorBaseStaticData.hpp"
namespace Candy::Math
{
    template<typename T>
    struct VectorBase<T, 3> : public VectorExpression<T, VectorBase<T, 3>>, public VectorBaseStaticData<T, 3>
    {
    public:
        static constexpr bool isLeaf=true;
    
    public:
        static constexpr T Dot(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr T Determinant(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr T Distance(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr T SqrDistance(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr VectorBase<T, 3> Cross(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr T Slope(const VectorBase<T, 3> &start, const VectorBase<T, 3> &end);
        static constexpr VectorBase<T, 3> Scale(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr VectorBase<T, 3> Lerp(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t);
        static constexpr VectorBase<T, 3> LerpClamped(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t);
        static constexpr VectorBase<T, 3> InverseLerp(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b, float t);
        static constexpr float Angle(const VectorBase<T, 3> &from, const VectorBase<T, 3> &to);
        static constexpr float SignedAngle(const VectorBase<T, 3> &from, const VectorBase<T, 3> &to);
        static constexpr VectorBase<T, 3> PerpendicularClockwise(const VectorBase<T, 3> &vec);
        static constexpr VectorBase<T, 3> PerpendicularCounterClockwise(const VectorBase<T, 3> &vec);
        static constexpr VectorBase<T, 3> MoveTowards(const VectorBase<T, 3> &current, const VectorBase<T, 3> &target, float maxDistanceDelta);
        static constexpr VectorBase<T, 3> Reflect(const VectorBase<T, 3> &inDirection, const VectorBase<T, 3> &inNormal);
        static constexpr VectorBase<T, 3> Max(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr VectorBase<T, 3> Min(const VectorBase<T, 3> &a, const VectorBase<T, 3> &b);
        static constexpr VectorBase<T, 3> Normalize(const VectorBase<T, 3> &vec);
        static constexpr T Length(const VectorBase<T, 3> &vec);
        
        
        
    public:
        union
        {
            T data[3];
            struct{T x, y, z;};
            struct{T r, g, b;};
            struct{T first, second, third;};
            struct{T pitch, yaw, roll;};
        };
        
        struct Iterator
        {
        private:
            T *ptr;
        
        public:
            Iterator() = default;
            Iterator(T *pointer);
            T &operator*() const;
            T *operator->() const;
            Iterator &operator++();
            Iterator operator++(int); //NOLINT
            Iterator &operator+=(int i);
            Iterator &operator--();
            Iterator operator--(int); //NOLINT
            Iterator &operator-=(int i);
            Iterator operator+(std::ptrdiff_t other) const;
            std::ptrdiff_t operator-(const Iterator &other) const;
            T &operator[](std::ptrdiff_t index) const;
            auto operator<=>(const Iterator &) const;
            
        };
    
    public:
        VectorBase();
        explicit VectorBase(T value);
        VectorBase(T xValue, T yValue, T zValue);
      
      typedef T VALUE_TYPE;
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        explicit VectorBase(const VectorBase<U, 3> &other);
        
        template <typename U, typename E>
        requires(std::is_arithmetic_v<U>)
        constexpr VectorBase(const VectorExpression<U,E>& expr); //NOLINT
    
    
    public:
        bool operator==(const VectorBase<T, 3> &other) const;
        bool operator!=(const VectorBase<T, 3> &other) const;
        bool operator<(const VectorBase<T, 3> &other) const;
        bool operator<=(const VectorBase<T, 3> &other) const;
        bool operator>(const VectorBase<T, 3> &other) const;
        bool operator>=(const VectorBase<T, 3> &other) const;
        bool operator<(T other) const;
        bool operator<=(T other) const;
        bool operator>(T other) const;
        bool operator>=(T other) const;
        constexpr inline T& operator[](std::size_t index) noexcept;
        [[nodiscard]] constexpr inline T operator[](std::size_t index) const;
        
        
        Iterator begin();
        Iterator end();
        VectorBase<T, 3> operator-() const;
        void operator+=(const VectorBase<T, 3> &other);
        void operator-=(const VectorBase<T, 3> &other);
        void operator*=(const VectorBase<T, 3> &other);
        void operator/=(const VectorBase<T, 3> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator+=(const VectorBase<U, 3> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator-=(const VectorBase<U, 3> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(const VectorBase<U, 3> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(const VectorBase<U, 3> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(U scalar);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(U scalar);
        
    public:
        void Set(T value);
        void Set(T xValue, T yValue, T zValue);
        void Set(const VectorBase<T, 3> &other);
        void AddToAll(T value);
        void SubtractFromAll(T value);
        void Normalize();
        void ScaleToLength(T newLength);
    
    
    public:
        [[nodiscard]] VectorBase<T, 3> Rotated(float theta, const VectorBase<T, 3> &orientation)const;
        void Rotate(float theta, const VectorBase<T, 3> &orientation);
        [[nodiscard]] VectorBase<T, 3> Normalized() const;
        [[nodiscard]] T Magnitude() const;
        [[nodiscard]] T SqrMagnitude() const;
        [[nodiscard]] T Dot(const VectorBase<T, 3> &other) const;
        [[nodiscard]] VectorBase<T, 3> Cross(const VectorBase<T, 3>& other)const;
        [[nodiscard]] T Determinant(const VectorBase<T, 3> &b) const;
        [[nodiscard]] T Distance(const VectorBase<T, 3> &b) const;
        [[nodiscard]] T SqrDistance(const VectorBase<T, 3> &b) const;
        [[nodiscard]] T Slope(const VectorBase<T, 3> &end) const;
        [[nodiscard]] VectorBase<T, 3> Scale(const VectorBase<T, 3> &b) const;
        [[nodiscard]] VectorBase<T, 3> Lerp(const VectorBase<T, 3> &b, T t) const;
        [[nodiscard]] VectorBase<T, 3> LerpClamped(const VectorBase<T, 3> &b, T t) const;
        [[nodiscard]] VectorBase<T, 3> InverseLerp(const VectorBase<T, 3> &b, T t) const;
        [[nodiscard]] T Angle(const VectorBase<T, 3> &to) const;
        [[nodiscard]] T SignedAngle(const VectorBase<T, 3> &to) const;
        [[nodiscard]] VectorBase<T, 3> PerpendicularClockwise() const;
        [[nodiscard]] VectorBase<T, 3> PerpendicularCounterClockwise() const;
        [[nodiscard]] VectorBase<T, 3> MoveTowards(const VectorBase<T, 3> &target, T maxDistanceDelta) const;
        [[nodiscard]] VectorBase<T, 3> Reflect(const VectorBase<T, 3> &inNormal) const;
        [[nodiscard]] VectorBase<T, 3> ScaledToLength(T newLength) const;
        [[nodiscard]] VectorBase<T, 3> ToRadians()const;
        [[nodiscard]] VectorBase<T, 3> ToDegrees()const;
        [[nodiscard]] T Sum() const;
        [[nodiscard]] T Difference() const;
        [[nodiscard]] T AbsDifference() const;
        [[nodiscard]] T Product() const;
        [[nodiscard]] T Quotient() const;
        [[nodiscard]] T MaxValue() const;
        [[nodiscard]] T MinValue() const;
        [[nodiscard]] T Average() const;
        [[nodiscard]] std::string ToString()const;
        
    
    
    public:
        [[nodiscard]]   int LexicographicCompare(const VectorBase<T, 3> &other) const;
        [[nodiscard]]   int MagnitudeCompare(const VectorBase<T, 3> &other) const;
        [[nodiscard]]   int SumCompare(const VectorBase<T, 3> &other) const;
        [[nodiscard]] constexpr inline size_t Dimensions()const;
        [[nodiscard]] constexpr inline size_t Size()const;
        
    public:
        [[nodiscard]] constexpr VectorBase<T, 2> xx() const;
        [[nodiscard]] constexpr VectorBase<T, 2> xy() const;
        [[nodiscard]] constexpr VectorBase<T, 2> xz() const;
        [[nodiscard]] constexpr VectorBase<T, 2> yx() const;
        [[nodiscard]] constexpr VectorBase<T, 2> yy() const;
        [[nodiscard]] constexpr VectorBase<T, 2> yz() const;
        [[nodiscard]] constexpr VectorBase<T, 2> zx() const;
        [[nodiscard]] constexpr VectorBase<T, 2> zy() const;
        [[nodiscard]] constexpr VectorBase<T, 2> zz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xxx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xxy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xxz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xyx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xyy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xyz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xzx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xzy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> xzz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yxx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yxy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yxz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yyx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yyy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yyz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yzx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yzy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> yzz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zxx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zxy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zxz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zyx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zyy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zyz() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zzx() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zzy() const;
        [[nodiscard]] constexpr VectorBase<T, 3> zzz() const;
    };
}
template <typename T>
struct fmt::formatter<Candy::Math::VectorBase<T, 3>> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::VectorBase<T, 3>& vec, FormatContext& ctx) {
    return format_to(ctx.out(), "({0}, {1}, {2})", vec.x, vec.y, vec.z);
  }
};
template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 3> &vec);

#include "Vector3Base.inl"