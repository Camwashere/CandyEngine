#pragma once
#include "VectorBase.hpp"
#include "VectorBaseStaticData.hpp"
namespace Candy::Math
{
    template<typename T>
    struct VectorBase<T, 4> : public VectorExpression<T, VectorBase<T, 4>>, public VectorBaseStaticData<T, 4>
    {
        
    public:
        static constexpr T Dot(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr T Distance(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr T SqrDistance(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr VectorBase<T, 4> Scale(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr VectorBase<T, 4> Lerp(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t);
        static constexpr VectorBase<T, 4> LerpClamped(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t);
        static constexpr VectorBase<T, 4> InverseLerp(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b, float t);
        
        static constexpr VectorBase<T, 4> MoveTowards(const VectorBase<T, 4> &current, const VectorBase<T, 4> &target, float maxDistanceDelta);
        static constexpr VectorBase<T, 4> Reflect(const VectorBase<T, 4> &inDirection, const VectorBase<T, 4> &inNormal);
        static constexpr VectorBase<T, 4> Max(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr VectorBase<T, 4> Min(const VectorBase<T, 4> &a, const VectorBase<T, 4> &b);
        static constexpr VectorBase<T, 4> Normalize(const VectorBase<T, 4> &vec);
    public:
        static constexpr bool isLeaf=true;
        union
        {
            T data[4];
            struct{T x, y, z, w;};
            struct{T x1, y1, x2, y2;};
            struct{T r, g, b, a;};
            struct{T first, second, third, fourth;};
           
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
        VectorBase(T xValue, T yValue, T zValue, T wValue);
        
        VectorBase(const VectorBase<T, 3>& vec3, T wValue);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        explicit VectorBase(const VectorBase<U, 4> &other);
        
        
        template <typename U, typename E>
        requires(std::is_arithmetic_v<U>)
        constexpr VectorBase(const VectorExpression<U,E>& expr);
    
    
    public:
        
        bool operator==(const VectorBase<T, 4> &other) const;
        bool operator!=(const VectorBase<T, 4> &other) const;
        bool operator<(const VectorBase<T, 4> &other) const;
        bool operator<=(const VectorBase<T, 4> &other) const;
        bool operator>(const VectorBase<T, 4> &other) const;
        bool operator>=(const VectorBase<T, 4> &other) const;
        bool operator<(T other) const;
        bool operator<=(T other) const;
        bool operator>(T other) const;
        bool operator>=(T other) const;
        
        
        constexpr inline T& operator[](std::size_t index) noexcept;
        [[nodiscard]] constexpr inline T operator[](std::size_t index) const;
        
        
        Iterator begin();
        Iterator end();
        VectorBase<T, 4> operator-() const;
        void operator+=(const VectorBase<T, 4> &other);
        void operator-=(const VectorBase<T, 4> &other);
        void operator*=(const VectorBase<T, 4> &other);
        void operator/=(const VectorBase<T, 4> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator+=(const VectorBase<U, 4> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator-=(const VectorBase<U, 4> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(const VectorBase<U, 4> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(const VectorBase<U, 4> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(U scalar);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(U scalar);
    
    public:
        void Set(T value);
        void Set(T xValue, T yValue, T zValue, T wValue);
        void Set(const VectorBase<T, 4> &other);
        void AddToAll(T value);
        void SubtractFromAll(T value);
        void Normalize();
        void ScaleToLength(T newLength);
    
    public:
      typedef T VALUE_TYPE;
        [[nodiscard]] VectorBase<T, 4> Normalized() const;
        [[nodiscard]] T Magnitude() const;
        [[nodiscard]] T SqrMagnitude() const;
        [[nodiscard]] T Dot(const VectorBase<T, 4> &other) const;
        [[nodiscard]] T Distance(const VectorBase<T, 4> &b) const;
        [[nodiscard]] T SqrDistance(const VectorBase<T, 4> &b) const;
        [[nodiscard]] VectorBase<T, 4> Scale(const VectorBase<T, 4> &b) const;
        [[nodiscard]] VectorBase<T, 4> Lerp(const VectorBase<T, 4> &b, T t) const;
        [[nodiscard]] VectorBase<T, 4> LerpClamped(const VectorBase<T, 4> &b, T t) const;
        [[nodiscard]] VectorBase<T, 4> InverseLerp(const VectorBase<T, 4> &b, T t) const;
        [[nodiscard]] VectorBase<T, 4> MoveTowards(const VectorBase<T, 4> &target, T maxDistanceDelta) const;
        [[nodiscard]] VectorBase<T, 4> Reflect(const VectorBase<T, 4> &inNormal) const;
        [[nodiscard]] VectorBase<T, 4> ScaledToLength(T newLength) const;
        [[nodiscard]] T Sum() const;
        [[nodiscard]] T Difference() const;
        [[nodiscard]] T AbsDifference() const;
        [[nodiscard]] T Product() const;
        [[nodiscard]] T Quotient() const;
        [[nodiscard]] T MaxValue() const;
        [[nodiscard]] T MinValue() const;
        [[nodiscard]] T Average() const;
    
    public:
        [[nodiscard]]   int LexicographicCompare(const VectorBase<T, 4> &other) const;
        [[nodiscard]]   int MagnitudeCompare(const VectorBase<T, 4> &other) const;
        [[nodiscard]]   int SumCompare(const VectorBase<T, 4> &other) const;
       
    
    public:
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
struct fmt::formatter<Candy::Math::VectorBase<T, 4>> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::VectorBase<T, 4>& vec, FormatContext& ctx) {
    return format_to(ctx.out(), "({0}, {1}, {2}, {3})", vec.x, vec.y, vec.z, vec.w);
  }
};
template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 4> &vec);
#include "Vector4Base.inl"