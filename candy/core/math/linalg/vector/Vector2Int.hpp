#pragma once
#include "../LinalgForwardDef.hpp"
namespace Candy::Math{
    struct Vector2Int : public VectorBase<int, 2> {
        static const Vector2Int up;
        static const Vector2Int down;
        static const Vector2Int left;
        static const Vector2Int right;
        static const Vector2Int upLeft;
        static const Vector2Int upRight;
        static const Vector2Int downLeft;
        static const Vector2Int downRight;
        static const Vector2Int zero;
        static const Vector2Int one;
        static const Vector2Int negativeOne;
        static const Vector2Int positiveInfinity;
        static const Vector2Int negativeInfinity;
    public:
        static int Dot(const Vector2Int &a, const Vector2Int &b);
        
        static float Distance(const Vector2Int &a, const Vector2Int &b);
        
        static int SqrDistance(const Vector2Int &a, const Vector2Int &b);
        
        static Vector2Int Scale(const Vector2Int &a, const Vector2Int &b);
        
        static Vector2Int Lerp(const Vector2Int &a, const Vector2Int &b, int t);
        
        static Vector2Int LerpClamped(const Vector2Int &a, const Vector2Int &b, int t);
        
        static Vector2Int InverseLerp(const Vector2Int &a, const Vector2Int &b, int t);
        
        static Vector2Int MoveTowards(const Vector2Int &current, const Vector2Int &target, int maxDistanceDelta);
        
        static Vector2Int Reflect(const Vector2Int &inDirection, const Vector2Int &inNormal);
        
        static Vector2Int Max(const Vector2Int &a, const Vector2Int &b);
        
        static Vector2Int Min(const Vector2Int &a, const Vector2Int &b);
    
    
    
    public:
    
    public:
        Vector2Int();
        explicit Vector2Int(int value);
        constexpr Vector2Int(int xValue, int yValue) : VectorBase<int, 2>(xValue, yValue) {}
        template<typename E>
        Vector2Int(const VectorExpression<int, E> &expr) : VectorBase<int, 2>(expr) {}
    
    public:
        bool operator==(const Vector2Int &other) const;
        
        bool operator!=(const Vector2Int &other) const;
        
        bool operator<(const Vector2Int &other) const;
        
        bool operator<=(const Vector2Int &other) const;
        
        bool operator>(const Vector2Int &other) const;
        
        bool operator>=(const Vector2Int &other) const;
        
        bool operator<(int other) const;
        
        bool operator<=(int other) const;
        
        bool operator>(int other) const;
        
        bool operator>=(int other) const;
        
        
        Vector2Int operator-() const;
        
        Vector2Int operator*(const Vector2Int &other) const;
        
        Vector2Int operator/(const Vector2Int &other) const;
        
        Vector2Int operator^(const Vector2Int &other) const;
        
        Vector2Int operator^(int scalar) const;
        
        void operator+=(const Vector2Int &other);
        void operator-=(const Vector2Int &other);
        void operator*=(const Vector2Int &other);
        void operator/=(const Vector2Int &other);
        
        void operator+=(const Vector3Int &other);
        void operator-=(const Vector3Int &other);
        void operator*=(const Vector3Int &other);
        void operator/=(const Vector3Int &other);
        
        void operator*=(int scalar);
        
        void operator/=(int scalar);
        
        explicit operator std::string() const;
        
        std::ostream &operator<<(std::ostream &ostream) const;
        
        
        friend std::ostream &operator<<(std::ostream &ostream, const Vector2Int &vec);
        
        
        friend Vector2Int operator^(int scalar, const Vector2Int &vec);
    
    public:
        void Set(int value);
        
        void Set(int xValue, int yValue);
        
        void Set(const Vector2Int &vec);
        
        void Clamp(int min, int max);
        
        void Clamp(int xMin, int yMin, int xMax, int yMax);
        
        void Clamp(const Vector2Int &min, const Vector2Int &max);
    
    public:
        
        int SqrMagnitude() const;
        
        int Dot(const Vector2Int &other) const;
        
        float Distance(const Vector2Int &b) const;
        
        int SqrDistance(const Vector2Int &b) const;
        
        Vector2Int Scale(const Vector2Int &b) const;
        
        Vector2Int Lerp(const Vector2Int &b, int t) const;
        
        Vector2Int LerpClamped(const Vector2Int &b, int t) const;
        
        Vector2Int InverseLerp(const Vector2Int &b, int t) const;
        
        Vector2Int MoveTowards(const Vector2Int &target, int maxDistanceDelta) const;
        
        Vector2Int Reflect(const Vector2Int &inNormal) const;
        
        int Sum() const;
        
        int Product() const;
        
        int Average() const;
        
        int MaxValue() const;
        
        int MinValue() const;
        
        Vector2Int Clamped(int valueMin, int valueMax) const;
        
        Vector2Int Clamped(int xMin, int yMin, int xMax, int yMax) const;
        
        Vector2Int Clamped(const Vector2Int &min, const Vector2Int &max) const;
        
        bool InRangeInclusive(int minValue, int maxValue) const;
        
        bool InRangeInclusive(int xMin, int yMin, int xMax, int yMax) const;
        
        bool InRangeInclusive(const Vector2Int &min, const Vector2Int &max) const;
        
        bool InRangeInclusiveMin(int minValue, int maxValue) const;
        
        bool InRangeInclusiveMin(int xMin, int yMin, int xMax, int yMax) const;
        
        bool InRangeInclusiveMin(const Vector2Int &min, const Vector2Int &max) const;
        
        bool InRangeInclusiveMax(int minValue, int maxValue) const;
        
        bool InRangeInclusiveMax(int xMin, int yMin, int xMax, int yMax) const;
        
        bool InRangeInclusiveMax(const Vector2Int &min, const Vector2Int &max) const;
        
        bool InRangeExclusive(int minValue, int maxValue) const;
        
        bool InRangeExclusive(int xMin, int yMin, int xMax, int yMax) const;
        
        bool InRangeExclusive(const Vector2Int &min, const Vector2Int &max) const;
    
    public:
        Vector2Int xx() const;
        Vector2Int xy() const;
        Vector2Int yx() const;
        Vector2Int yy() const;
    
    public:
        int LexicographicCompare(const Vector2Int &other) const;
        
        int MagnitudeCompare(const Vector2Int &other) const;
        
        int SumCompare(const Vector2Int &other) const;
        
    };
}

