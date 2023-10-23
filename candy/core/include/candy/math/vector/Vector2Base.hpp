#pragma once
#include <spdlog/fmt/ostr.h> // must be included
#include "VectorBase.hpp"
#include "VectorBaseStaticData.hpp"

namespace Candy::Math
{
    
    template<typename T>
    struct VectorBase<T, 2> : public VectorExpression<T, VectorBase<T, 2>>, public VectorBaseStaticData<T, 2>
    {
    public:
        static constexpr bool isLeaf = true;
    public: // Static Methods
        static VectorBase<T, 2> Clamp(const VectorBase<T, 2> &value, const VectorBase<T, 2> &min, const VectorBase<T, 2> &max);
        static T Length(const VectorBase<T, 2>& vec);
        static T SqrLength(const VectorBase<T, 2>& vec);
        static T Magnitude(const VectorBase<T, 2>& vec);
        static T SqrMagnitude(const VectorBase<T, 2>& vec);
        // How closely are these two vectors aligned. A value of 0 means the vectors are orthogonal
        static T Dot(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static T Determinant(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static T Distance(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static T SqrDistance(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static T Slope(const VectorBase<T, 2> &start, const VectorBase<T, 2> &end);
        static VectorBase<T, 2> Scale(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static VectorBase<T, 2> Lerp(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t);
        static VectorBase<T, 2> LerpClamped(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t);
        static VectorBase<T, 2> InverseLerp(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b, float t);
        static float Angle(const VectorBase<T, 2> &from, const VectorBase<T, 2> &to);
        static float SignedAngle(const VectorBase<T, 2> &from, const VectorBase<T, 2> &to);
        static VectorBase<T, 2> PerpendicularClockwise(const VectorBase<T, 2> &vec);
        static VectorBase<T, 2> PerpendicularCounterClockwise(const VectorBase<T, 2> &vec);
        static VectorBase<T, 2> MoveTowards(const VectorBase<T, 2> &current, const VectorBase<T, 2> &target, float maxDistanceDelta);
        static VectorBase<T, 2> Reflect(const VectorBase<T, 2> &inDirection, const VectorBase<T, 2> &inNormal);
        static VectorBase<T, 2> Max(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static VectorBase<T, 2> Min(const VectorBase<T, 2> &a, const VectorBase<T, 2> &b);
        static VectorBase<T, 2> Normalized(const VectorBase<T, 2>& vec);
        static void Normalize(VectorBase<T, 2>& vec);
    
    public: // Members
        union
        {
            T data[2] = {0, 0};
            struct{T x, y;};
            struct{T a, b;};
            struct{T min, max;};
            struct{T width, height;};
            struct{T first, second;};
            struct{T pitch, yaw;};
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
            Iterator operator++(int);
            Iterator &operator+=(int i);
            Iterator &operator--();
            Iterator operator--(int);
            Iterator &operator-=(int i);
            Iterator operator+(std::ptrdiff_t other) const;
            std::ptrdiff_t operator-(const Iterator &other) const;
            T &operator[](std::ptrdiff_t index) const;
            auto operator<=>(const Iterator &) const;
            
        };
    
    public: // Constructors
        VectorBase();
        explicit VectorBase(T value);
        constexpr VectorBase(T xValue, T yValue);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        explicit VectorBase(const VectorBase<U, 2> &other);
        
        template<typename U, typename E>
        requires(std::is_arithmetic_v<U>)
        VectorBase(const VectorExpression<U, E> &expr); //NOLINT
    
    public: // Operators
        bool operator==(const VectorBase<T, 2> &other) const;
        bool operator!=(const VectorBase<T, 2> &other) const;
        bool operator<(const VectorBase<T, 2> &other) const;
        bool operator<=(const VectorBase<T, 2> &other) const;
        bool operator>(const VectorBase<T, 2> &other) const;
        bool operator>=(const VectorBase<T, 2> &other) const;
        bool operator<(T other) const;
        bool operator<=(T other) const;
        bool operator>(T other) const;
        bool operator>=(T other) const;
        T &operator[](std::size_t index) noexcept;
        
        T operator[](std::size_t index) const;
        
        Iterator begin();
        Iterator end();
        
        VectorBase<T, 2> operator-() const;
        void operator+=(const VectorBase<T, 2> &other);
        void operator-=(const VectorBase<T, 2> &other);
        void operator*=(const VectorBase<T, 2> &other);
        void operator/=(const VectorBase<T, 2> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator+=(const VectorBase<U, 2> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator-=(const VectorBase<U, 2> &other);
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(const VectorBase<U, 2> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(const VectorBase<U, 2> &other);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator*=(U scalar);
        
        template<typename U>
        requires(std::is_convertible_v<U, T>)
        void operator/=(U scalar);
    
    
    public:
        typedef T VALUE_TYPE;
        void Set(T value);
        void Set(T xValue, T yValue);
        void Set(const VectorBase<T, 2> &other);
        void AddToAll(T value);
        void SubtractFromAll(T value);
        void Normalize();
        void ScaleToLength(T newLength);
    
    public:
        [[nodiscard]] VectorBase<T, 2> Normalized() const;
        [[nodiscard]] T Magnitude() const;
        [[nodiscard]] T SqrMagnitude() const;
        [[nodiscard]] T Length() const;
        [[nodiscard]] T SqrLength() const;
        [[nodiscard]] T Dot(const VectorBase<T, 2> &other) const;
        [[nodiscard]] T Determinant(const VectorBase<T, 2> &b) const;
        [[nodiscard]] T Distance(const VectorBase<T, 2> &b) const;
        [[nodiscard]] T SqrDistance(const VectorBase<T, 2> &b) const;
        [[nodiscard]] T Slope(const VectorBase<T, 2> &end) const;
        [[nodiscard]] VectorBase<T, 2> Scale(const VectorBase<T, 2> &b) const;
        [[nodiscard]] VectorBase<T, 2> Lerp(const VectorBase<T, 2> &b, T t) const;
        [[nodiscard]] VectorBase<T, 2> LerpClamped(const VectorBase<T, 2> &b, T t) const;
        [[nodiscard]] VectorBase<T, 2> InverseLerp(const VectorBase<T, 2> &b, T t) const;
        [[nodiscard]] T Angle(const VectorBase<T, 2> &to) const;
        [[nodiscard]] T SignedAngle(const VectorBase<T, 2> &to) const;
        [[nodiscard]] VectorBase<T, 2> PerpendicularClockwise() const;
        [[nodiscard]] VectorBase<T, 2> PerpendicularCounterClockwise() const;
        [[nodiscard]] VectorBase<T, 2> MoveTowards(const VectorBase<T, 2> &target, T maxDistanceDelta) const;
        [[nodiscard]] VectorBase<T, 2> Reflect(const VectorBase<T, 2> &inNormal) const;
        [[nodiscard]] VectorBase<T, 2> ScaledToLength(T newLength) const;
        [[nodiscard]] T Sum() const;
        [[nodiscard]] T Difference() const;
        [[nodiscard]] T AbsDifference() const;
        [[nodiscard]] T Product() const;
        [[nodiscard]] T Quotient() const;
        [[nodiscard]] T MaxValue() const;
        [[nodiscard]] T MinValue() const;
        [[nodiscard]] T Average() const;
        
        
    
    public:
        [[nodiscard]]   VectorBase<T, 2> xx() const;
        [[nodiscard]]   VectorBase<T, 2> xy() const;
        [[nodiscard]]   VectorBase<T, 2> yx() const;
        [[nodiscard]]   VectorBase<T, 2> yy() const;
        [[nodiscard]]   T ToVector1() const;
        [[nodiscard]]   VectorBase<T, 3> ToVector3() const;
        [[nodiscard]]   VectorBase<T, 4> ToVector4() const;
        [[nodiscard]]   std::string ToString() const;
    
    public:
        [[nodiscard]]   int LexicographicCompare(const VectorBase<T, 2> &other) const;
        [[nodiscard]]   int MagnitudeCompare(const VectorBase<T, 2> &other) const;
        [[nodiscard]]   int SumCompare(const VectorBase<T, 2> &other) const;
        [[nodiscard]]   size_t Dimensions() const;
        [[nodiscard]]   size_t Size() const;
    };
  
  template<typename T>
  inline VectorBase<T, 2> Abs(const VectorBase<T, 2> &vec)
  {
    return VectorBase<T, 2>(Abs(vec.x), Abs(vec.y));
  }
}


template <typename T>
struct fmt::formatter<Candy::Math::VectorBase<T, 2>> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::VectorBase<T, 2>& vec, FormatContext& ctx) {
    return format_to(ctx.out(), "({0}, {1})", vec.x, vec.y);
  }
};
template<typename T>
std::ostream &operator<<(std::ostream &ostream, const Candy::Math::VectorBase<T, 2> &vec);

#include "Vector2Base.inl"