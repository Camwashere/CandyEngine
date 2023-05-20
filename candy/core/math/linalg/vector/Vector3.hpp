#pragma once
#include "../LinalgForwardDef.hpp"

namespace Candy::Math{
        struct Vector3 : public VectorBase<float, 3> {
        public:
            static const Vector3 up;
            static const Vector3 down;
            static const Vector3 left;
            static const Vector3 right;
            static const Vector3 forward;
            static const Vector3 back;
            static const Vector3 upLeft;
            static const Vector3 upRight;
            static const Vector3 upForward;
            static const Vector3 upBack;
            static const Vector3 leftBack;
            static const Vector3 rightBack;
            static const Vector3 leftForward;
            static const Vector3 rightForward;
            static const Vector3 upLeftForward;
            static const Vector3 upLeftBack;
            static const Vector3 upRightForward;
            static const Vector3 upRightBack;
            static const Vector3 downLeft;
            static const Vector3 downRight;
            static const Vector3 downForward;
            static const Vector3 downBack;
            static const Vector3 downLeftForward;
            static const Vector3 downLeftBack;
            static const Vector3 downRightForward;
            static const Vector3 downRightBack;
            static const Vector3 zero;
            static const Vector3 one;
            static const Vector3 negativeOne;
            
            
            static const Vector3 positiveInfinity;
            static const Vector3 negativeInfinity;
        public:
        
        public:
            static float Dot(const Vector3 &a, const Vector3 &b);
            
            static float Distance(const Vector3 &a, const Vector3 &b);
            
            static float SqrDistance(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Cross(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Scale(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t);
            
            static Vector3 LerpClamped(const Vector3 &a, const Vector3 &b, float t);
            
            static Vector3 InverseLerp(const Vector3 &a, const Vector3 &b, float t);
            
            static Vector3 MoveTowards(const Vector3 &current, const Vector3 &target, float maxDistanceDelta);
            
            static Vector3 Reflect(const Vector3 &inDirection, const Vector3 &inNormal);
            
            static Vector3 Max(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Min(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Average(const Vector3 &a, const Vector3 &b);
            
            static Vector3 Normalize(const Vector3 &vec);
        
        
        public:
        
        public:
            Vector3();
            
            explicit Vector3(float value);
            
            constexpr Vector3(float xValue, float yValue, float zValue = 0) : VectorBase<float, 3>(xValue, yValue, zValue) {}
            
            Vector3(const Vector2 &vec, float zValue);
            
            Vector3(const Vector3 &other);
            
            Vector3(const Vector2 &other);
            
            Vector3(const Vector4 &other);
            
            template<typename E>
            Vector3(const VectorExpression<float, E> &expr) : VectorBase<float, 3>(expr) {}
        
        public:
            bool operator==(const Vector3 &other) const;
            
            bool operator!=(const Vector3 &other) const;
            
            Vector3 operator^(const Vector3 &other) const;
            
            Vector3 operator^(float scalar) const;
            
            void operator+=(const Vector3 &other);
            
            void operator-=(const Vector3 &other);
            
            void operator*=(const Vector3 &other);
            
            void operator/=(const Vector3 &other);
            
            void operator*=(float scalar);
            
            void operator/=(float scalar);
            
            
            explicit operator Vector2() const;
            
            explicit operator Vector4() const;
            
            explicit operator std::string() const;
            
            
            std::ostream &operator<<(std::ostream &ostream) const;
            
            
            friend std::ostream &operator<<(std::ostream &ostream, const Vector3 &vec);
            
            friend Vector3 operator^(float scalar, const Vector3 &vec);
        
        public:
            float *CombineToArray(const Vector2 &other) const;
        
        public:
            void Set(float value);
            
            void Set(float xValue, float yValue, float zValue);
            
            void Set(const Vector2 &vec);
            
            void Set(const Vector3 &vec);
            
            void Set(const Vector4 &vec);
            
            void Normalize();
            
            void Clamp(float min, float max);
            
            void Clamp(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
            
            void Clamp(const Vector3 &min, const Vector3 &max);
            
            void ScaleToLength(float newLength);
        
        public:
            Vector3 Normalized() const;
            
            float Magnitude() const;
            
            float SqrMagnitude() const;
            
            float Dot(const Vector3 &other) const;
            
            Vector3 Cross(const Vector3 &other) const;
            
            float Distance(const Vector3 &b) const;
            
            float SqrDistance(const Vector3 &b) const;
            
            Vector3 Scale(const Vector3 &b) const;
            
            Vector3 Lerp(const Vector3 &b, float t) const;
            
            Vector3 LerpClamped(const Vector3 &b, float t) const;
            
            Vector3 InverseLerp(const Vector3 &b, float t) const;
            
            Vector3 MoveTowards(const Vector3 &target, float maxDistanceDelta) const;
            
            Vector3 Reflect(const Vector3 &inNormal) const;
            
            Vector3 ScaledToLength(float newLength) const;
            
            float Sum() const;
            
            float Product() const;
            
            float Average() const;
            
            float MaxValue() const;
            
            float MinValue() const;
            
            Vector3 Clamped(float valueMin, float valueMax) const;
            
            Vector3 Clamped(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const;
            
            Vector3 Clamped(const Vector3 &min, const Vector3 &max) const;
            
            bool InRangeInclusive(float minValue, float maxValue) const;
            
            bool InRangeInclusive(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const;
            
            bool InRangeInclusive(const Vector3 &min, const Vector3 &max) const;
            
            bool InRangeInclusiveMin(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMin(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const;
            
            bool InRangeInclusiveMin(const Vector3 &min, const Vector3 &max) const;
            
            bool InRangeInclusiveMax(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMax(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const;
            
            bool InRangeInclusiveMax(const Vector3 &min, const Vector3 &max) const;
            
            bool InRangeExclusive(float minValue, float maxValue) const;
            
            bool InRangeExclusive(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) const;
            
            bool InRangeExclusive(const Vector3 &min, const Vector3 &max) const;
        
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
            
            
            Vector3 xxx() const;
            
            Vector3 xxy() const;
            
            Vector3 xxz() const;
            
            Vector3 xyx() const;
            
            Vector3 xyy() const;
            
            Vector3 xyz() const;
            
            Vector3 xzx() const;
            
            Vector3 xzy() const;
            
            Vector3 xzz() const;
            
            Vector3 yxx() const;
            
            Vector3 yxy() const;
            
            Vector3 yxz() const;
            
            Vector3 yyx() const;
            
            Vector3 yyy() const;
            
            Vector3 yyz() const;
            
            Vector3 yzx() const;
            
            Vector3 yzy() const;
            
            Vector3 yzz() const;
            
            Vector3 zxx() const;
            
            Vector3 zxy() const;
            
            Vector3 zxz() const;
            
            Vector3 zyx() const;
            
            Vector3 zyy() const;
            
            Vector3 zyz() const;
            
            Vector3 zzx() const;
            
            Vector3 zzy() const;
            
            Vector3 zzz() const;
        
        
        public:
            int LexicographicCompare(const Vector3 &other) const;
            
            int MagnitudeCompare(const Vector3 &other) const;
            
            int SumCompare(const Vector3 &other) const;
            
        };
}