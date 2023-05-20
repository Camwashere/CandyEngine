#pragma once

#include "../LinalgForwardDef.hpp"

namespace Candy::Math{
        struct Vector3Int : public VectorBase<int, 3> {
            static const Vector3Int up;
            static const Vector3Int down;
            static const Vector3Int left;
            static const Vector3Int right;
            static const Vector3Int forward;
            static const Vector3Int back;
            static const Vector3Int upLeft;
            static const Vector3Int upRight;
            static const Vector3Int upForward;
            static const Vector3Int upBack;
            static const Vector3Int leftBack;
            static const Vector3Int rightBack;
            static const Vector3Int leftForward;
            static const Vector3Int rightForward;
            static const Vector3Int upLeftForward;
            static const Vector3Int upLeftBack;
            static const Vector3Int upRightForward;
            static const Vector3Int upRightBack;
            static const Vector3Int downLeft;
            static const Vector3Int downRight;
            static const Vector3Int downForward;
            static const Vector3Int downBack;
            static const Vector3Int downLeftForward;
            static const Vector3Int downLeftBack;
            static const Vector3Int downRightForward;
            static const Vector3Int downRightBack;
            static const Vector3Int zero;
            static const Vector3Int one;
            static const Vector3Int negativeOne;
            
            
            static const Vector3Int positiveInfinity;
            static const Vector3Int negativeInfinity;
        public:
            static int Dot(const Vector3Int &a, const Vector3Int &b);
            
            static float Distance(const Vector3Int &a, const Vector3Int &b);
            
            static int SqrDistance(const Vector3Int &a, const Vector3Int &b);
            
            static Vector3Int Cross(const Vector3Int &a, const Vector3Int &b);
            
            static Vector3Int Scale(const Vector3Int &a, const Vector3Int &b);
            
            static Vector3Int Lerp(const Vector3Int &a, const Vector3Int &b, int t);
            
            static Vector3Int LerpClamped(const Vector3Int &a, const Vector3Int &b, int t);
            
            static Vector3Int InverseLerp(const Vector3Int &a, const Vector3Int &b, int t);
            
            static Vector3Int MoveTowards(const Vector3Int &current, const Vector3Int &target, int maxDistanceDelta);
            
            static Vector3Int Reflect(const Vector3Int &inDirection, const Vector3Int &inNormal);
            
            static Vector3Int Max(const Vector3Int &a, const Vector3Int &b);
            
            static Vector3Int Min(const Vector3Int &a, const Vector3Int &b);
            
            static Vector3Int Average(const Vector3Int &a, const Vector3Int &b);
        
        
        
        public:
        
        public:
            Vector3Int();
            
            explicit Vector3Int(int value);
            
            constexpr Vector3Int(int xValue, int yValue, int zValue = 0) : VectorBase<int, 3>(xValue, yValue, zValue) {}
            
            Vector3Int(const Vector2 &vec, int zValue);
            
            Vector3Int(const Vector3Int &other);
            
            Vector3Int(const Vector2 &other);
            
            Vector3Int(const Vector4 &other);
            
            template<typename E>
            Vector3Int(const VectorExpression<int, E> &expr) : VectorBase<int, 3>(expr) {}
        
        public:
            bool operator==(const Vector3Int &other) const;
            
            bool operator!=(const Vector3Int &other) const;
            
            Vector3Int operator*(const Vector3Int &other) const;
            
            Vector3Int operator/(const Vector3Int &other) const;
            
            Vector3Int operator^(const Vector3Int &other) const;
            
            Vector3Int operator^(int scalar) const;
            
            void operator+=(const Vector3Int &other);
            
            void operator-=(const Vector3Int &other);
            
            void operator*=(const Vector3Int &other);
            
            void operator/=(const Vector3Int &other);
            
            void operator*=(int scalar);
            
            void operator/=(int scalar);
            
            explicit operator Vector2() const;
            
            explicit operator Vector3() const;
            
            explicit operator Vector4() const;
            
            explicit operator std::string() const;
            
            
            std::ostream &operator<<(std::ostream &ostream) const;
            
            
            friend std::ostream &operator<<(std::ostream &ostream, const Vector3Int &vec);
            
            
            friend Vector3Int operator^(int scalar, const Vector3Int &vec);
        
        public:
            void Set(int value);
            
            void Set(int xValue, int yValue, int zValue);
            
            void Set(const Vector2 &vec);
            
            void Set(const Vector3Int &vec);
            
            void Set(const Vector4 &vec);
            
            void Clamp(int min, int max);
            
            void Clamp(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax);
            
            void Clamp(const Vector3Int &min, const Vector3Int &max);
        
        public:
            
            float Magnitude() const;
            
            int SqrMagnitude() const;
            
            int Dot(const Vector3Int &other) const;
            
            Vector3Int Cross(const Vector3Int &other) const;
            
            float Distance(const Vector3Int &b) const;
            
            int SqrDistance(const Vector3Int &b) const;
            
            Vector3Int Scale(const Vector3Int &b) const;
            
            Vector3Int Lerp(const Vector3Int &b, int t) const;
            
            Vector3Int LerpClamped(const Vector3Int &b, int t) const;
            
            Vector3Int InverseLerp(const Vector3Int &b, int t) const;
            
            Vector3Int MoveTowards(const Vector3Int &target, int maxDistanceDelta) const;
            
            Vector3Int Reflect(const Vector3Int &inNormal) const;
            
            int Sum() const;
            
            int Product() const;
            
            int Average() const;
            
            int MaxValue() const;
            
            int MinValue() const;
            
            Vector3Int Clamped(int valueMin, int valueMax) const;
            
            Vector3Int Clamped(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const;
            
            Vector3Int Clamped(const Vector3Int &min, const Vector3Int &max) const;
            
            bool InRangeInclusive(int minValue, int maxValue) const;
            
            bool InRangeInclusive(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const;
            
            bool InRangeInclusive(const Vector3Int &min, const Vector3Int &max) const;
            
            bool InRangeInclusiveMin(int minValue, int maxValue) const;
            
            bool InRangeInclusiveMin(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const;
            
            bool InRangeInclusiveMin(const Vector3Int &min, const Vector3Int &max) const;
            
            bool InRangeInclusiveMax(int minValue, int maxValue) const;
            
            bool InRangeInclusiveMax(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const;
            
            bool InRangeInclusiveMax(const Vector3Int &min, const Vector3Int &max) const;
            
            bool InRangeExclusive(int minValue, int maxValue) const;
            
            bool InRangeExclusive(int xMin, int yMin, int zMin, int xMax, int yMax, int zMax) const;
            
            bool InRangeExclusive(const Vector3Int &min, const Vector3Int &max) const;
        
        public:
            Vector2 xx() const;
            
            Vector2 xy() const;
            
            Vector2 xz() const;
            
            Vector2 yx() const;
            
            Vector2 yy() const;
            
            Vector2 yz() const;
            
            Vector2 zx() const;
            
            Vector2 zy() const;
            
            Vector2 zz() const;
            
            
            Vector3Int xxx() const;
            
            Vector3Int xxy() const;
            
            Vector3Int xxz() const;
            
            Vector3Int xyx() const;
            
            Vector3Int xyy() const;
            
            Vector3Int xyz() const;
            
            Vector3Int xzx() const;
            
            Vector3Int xzy() const;
            
            Vector3Int xzz() const;
            
            Vector3Int yxx() const;
            
            Vector3Int yxy() const;
            
            Vector3Int yxz() const;
            
            Vector3Int yyx() const;
            
            Vector3Int yyy() const;
            
            Vector3Int yyz() const;
            
            Vector3Int yzx() const;
            
            Vector3Int yzy() const;
            
            Vector3Int yzz() const;
            
            Vector3Int zxx() const;
            
            Vector3Int zxy() const;
            
            Vector3Int zxz() const;
            
            Vector3Int zyx() const;
            
            Vector3Int zyy() const;
            
            Vector3Int zyz() const;
            
            Vector3Int zzx() const;
            
            Vector3Int zzy() const;
            
            Vector3Int zzz() const;
        
        
        public:
            int LexicographicCompare(const Vector3Int &other) const;
            
            int MagnitudeCompare(const Vector3Int &other) const;
            
            int SumCompare(const Vector3Int &other) const;
            
        };
    
}

