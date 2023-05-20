#pragma once
#include "../LinalgForwardDef.hpp"

namespace Candy::Math{
        // TODO Implement Expression Templates for faster math operations
        struct Vector2 : public VectorBase<float, 2>{
        public:
            static const Vector2 up;
            static const Vector2 down;
            static const Vector2 left;
            static const Vector2 right;
            static const Vector2 upLeft;
            static const Vector2 upRight;
            static const Vector2 downLeft;
            static const Vector2 downRight;
            static const Vector2 zero;
            static const Vector2 one;
            static const Vector2 negativeOne;
            static const Vector2 positiveInfinity;
            static const Vector2 negativeInfinity;
        
        public:
            static float Dot(const Vector2 &a, const Vector2 &b); // How closely are these two vectors aligned. A value of 0 means the vectors are orthogonal
            static float Determinant(const Vector2 &a, const Vector2 &b);
            
            static float Distance(const Vector2 &a, const Vector2 &b);
            
            static float SqrDistance(const Vector2 &a, const Vector2 &b);
            
            static float Slope(const Vector2 &start, const Vector2 &end);
            
            static Vector2 Scale(const Vector2 &a, const Vector2 &b);
            
            static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
            
            static Vector2 LerpClamped(const Vector2 &a, const Vector2 &b, float t);
            
            static Vector2 InverseLerp(const Vector2 &a, const Vector2 &b, float t);
            
            static float Angle(const Vector2 &from, const Vector2 &to);
            
            static float SignedAngle(const Vector2 &from, const Vector2 &to);
            
            static Vector2 PerpendicularClockwise(const Vector2 &vec);
            
            static Vector2 PerpendicularCounterClockwise(const Vector2 &vec);
            
            static Vector2 MoveTowards(const Vector2 &current, const Vector2 &target, float maxDistanceDelta);
            
            static Vector2 Reflect(const Vector2 &inDirection, const Vector2 &inNormal);
            
            static Vector2 Max(const Vector2 &a, const Vector2 &b);
            
            static Vector2 Min(const Vector2 &a, const Vector2 &b);
            
            static Vector2 Normalize(const Vector2 &vec);
        
        public:
            Vector2();
            
            explicit Vector2(float value);
            
            constexpr Vector2(float xValue, float yValue) : VectorBase<float, 2>(xValue, yValue){}
            
            constexpr Vector2(const Vector2 &other) : VectorBase<float, 2>(other){}
            
            template <typename E>
            constexpr Vector2(const VectorExpression<float, E>& expr) : VectorBase<float, 2>(expr){}
            
            
            explicit Vector2(const Vector3 &other);
            
            explicit Vector2(const Vector4 &other);
            
            explicit Vector2(const float *data);
            
            
            bool operator==(const Vector2 &other) const;
            
            bool operator!=(const Vector2 &other) const;
            
            bool operator<(const Vector2 &other) const;
            
            bool operator<=(const Vector2 &other) const;
            
            bool operator>(const Vector2 &other) const;
            
            bool operator>=(const Vector2 &other) const;
            
            bool operator<(float other) const;
            
            bool operator<=(float other) const;
            
            bool operator>(float other) const;
            
            bool operator>=(float other) const;
            
            
            Vector2 operator-() const;
            
            Vector2 operator^(const Vector2 &other) const;
            
            Vector2 operator^(const Vector3 &other) const;
            
            Vector2 operator^(float scalar) const;
            
            void operator+=(const Vector2 &other);
            
            void operator-=(const Vector2 &other);
            
            void operator*=(const Vector2 &other);
            
            void operator/=(const Vector2 &other);
            
            void operator+=(const Vector3 &other);
            
            void operator-=(const Vector3 &other);
            
            void operator*=(const Vector3 &other);
            
            void operator/=(const Vector3 &other);
            
            void operator*=(float scalar);
            
            void operator/=(float scalar);
            
            void operator*=(int scalar);
            
            void operator/=(int scalar);
            
            explicit operator std::string() const;
            
            explicit operator Vector3() const;
            
            explicit operator Vector4() const;
            
            std::ostream &operator<<(std::ostream &ostream) const;
            
            friend std::ostream &operator<<(std::ostream &ostream, const Vector2 &vec);
            
            friend Vector2 operator^(float scalar, const Vector2 &vec);
        
        public:
            void Set(float value);
            
            void Set(float xValue, float yValue);
            
            void Set(const Vector2 &other);
            
            void Add(float value);
            
            void Subtract(float value);
            
            
            void Normalize();
            
            void Clamp(float min, float max);
            
            void Clamp(float xMin, float yMin, float xMax, float yMax);
            
            void Clamp(const Vector2 &min, const Vector2 &max);
            
            void ScaleToLength(float newLength);
        
        public:
            Vector2 Normalized() const;
            
            float Magnitude() const;
            
            float SqrMagnitude() const;
            
            float Dot(const Vector2 &other) const;
            
            float Determinant(const Vector2 &b) const;
            
            float Distance(const Vector2 &b) const;
            
            float SqrDistance(const Vector2 &b) const;
            
            float Slope(const Vector2 &end) const;
            
            Vector2 Scale(const Vector2 &b) const;
            
            Vector2 Lerp(const Vector2 &b, float t) const;
            
            Vector2 LerpClamped(const Vector2 &b, float t) const;
            
            Vector2 InverseLerp(const Vector2 &b, float t) const;
            
            float Angle(const Vector2 &to) const;
            
            float SignedAngle(const Vector2 &to) const;
            
            Vector2 PerpendicularClockwise() const;
            
            Vector2 PerpendicularCounterClockwise() const;
            
            Vector2 MoveTowards(const Vector2 &target, float maxDistanceDelta) const;
            
            Vector2 Reflect(const Vector2 &inNormal) const;
            
            Vector2 ScaledToLength(float newLength) const;
            
            float Sum() const;
            
            float Difference() const;
            
            float AbsDifference() const;
            
            float Product() const;
            
            float Quotient() const;
            
            float MaxValue() const;
            
            float MinValue() const;
            
            float Average() const;
            
            Vector2 Clamped(float valueMin, float valueMax) const;
            
            Vector2 Clamped(float xMin, float yMin, float xMax, float yMax) const;
            
            Vector2 Clamped(const Vector2 &min, const Vector2 &max) const;
            
            bool InRangeInclusive(float minValue, float maxValue) const;
            
            bool InRangeInclusive(float xMin, float yMin, float xMax, float yMax) const;
            
            bool InRangeInclusive(const Vector2 &min, const Vector2 &max) const;
            
            bool InRangeInclusiveMin(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMin(float xMin, float yMin, float xMax, float yMax) const;
            
            bool InRangeInclusiveMin(const Vector2 &min, const Vector2 &max) const;
            
            bool InRangeInclusiveMax(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMax(float xMin, float yMin, float xMax, float yMax) const;
            
            bool InRangeInclusiveMax(const Vector2 &min, const Vector2 &max) const;
            
            bool InRangeExclusive(float minValue, float maxValue) const;
            
            bool InRangeExclusive(float xMin, float yMin, float xMax, float yMax) const;
            
            bool InRangeExclusive(const Vector2 &min, const Vector2 &max) const;
            
            bool EqualComponents() const;
            
            Vector2 xx() const;
            
            Vector2 xy() const;
            
            Vector2 yx() const;
            
            Vector2 yy() const;
            
            float ToVector1() const;
            
            Vector3 ToVector3() const;
            
            Vector4 ToVector4() const;
        
        public:
            int LexicographicCompare(const Vector2 &other) const;
            
            int MagnitudeCompare(const Vector2 &other) const;
            
            int SumCompare(const Vector2 &other) const;
            
        };
}