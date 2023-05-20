#pragma once
#include "../LinalgForwardDef.hpp"

namespace Candy::Math{
        class Vector4 : public VectorBase<float, 4> {
        public:
            static const Vector4 up;
            static const Vector4 down;
            static const Vector4 left;
            static const Vector4 right;
            static const Vector4 forward;
            static const Vector4 back;
            static const Vector4 zero;
            static const Vector4 one;
            static const Vector4 negativeOne;
            static const Vector4 positiveInfinity;
            static const Vector4 negativeInfinity;
        
        public:
            static float Dot(const Vector4 &a, const Vector4 &b);
            
            static float Distance(const Vector4 &a, const Vector4 &b);
            
            static float SqrDistance(const Vector4 &a, const Vector4 &b);
            
            static Vector4 Scale(const Vector4 &a, const Vector4 &b);
            
            static Vector4 Lerp(const Vector4 &a, const Vector4 &b, float t);
            
            static Vector4 LerpClamped(const Vector4 &a, const Vector4 &b, float t);
            
            static Vector4 InverseLerp(const Vector4 &a, const Vector4 &b, float t);
            
            static Vector4 MoveTowards(const Vector4 &current, const Vector4 &target, float maxDistanceDelta);
            
            static Vector4 Reflect(const Vector4 &inDirection, const Vector4 &inNormal);
            
            static Vector4 Max(const Vector4 &a, const Vector4 &b);
            
            static Vector4 Min(const Vector4 &a, const Vector4 &b);
            
            static Vector4 Average(const Vector4 &a, const Vector4 &b);
            
            static Vector4 Normalize(const Vector4 &vec);
        
        
        public:
            Vector4();
            
            explicit Vector4(float value);
            
            constexpr Vector4(float xValue, float yValue, float zValue = 0, float wValue = 0) : VectorBase<float, 4>(
                    xValue, yValue, zValue, wValue) {}
            
            Vector4(const Vector3 &vec, float wValue);
            
            explicit Vector4(const Vector2 &vec);
            
            explicit Vector4(const Vector3 &vec);
            
            constexpr Vector4(const Vector4 &other) : VectorBase<float, 4>(other){}
            
            template<typename E>
            constexpr Vector4(const VectorExpression<float, E> &expr) : VectorBase<float, 4>(expr) {}
        
        public:
            bool operator==(const Vector4 &other) const;
            
            bool operator!=(const Vector4 &other) const;
            
            
            Vector4 operator^(const Vector4 &other) const;
            
            
            Vector4 operator^(float scalar) const;
            
            void operator+=(const Vector4 &other);
            
            void operator-=(const Vector4 &other);
            
            void operator*=(const Vector4 &other);
            
            void operator/=(const Vector4 &other);
            
            void operator*=(float scalar);
            
            void operator/=(float scalar);
            
            
            explicit operator Vector2() const;
            
            explicit operator Vector3() const;
            
            explicit operator std::string() const;
            
            
            std::ostream &operator<<(std::ostream &ostream) const;
            
            
            friend std::ostream &operator<<(std::ostream &ostream, const Vector4 &vec);
        
        
        public:
            void Set(float value);
            
            void Set(float xValue, float yValue, float zValue, float wValue);
            
            void Normalize();
            
            void Clamp(float min, float max);
            
            void Clamp(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax, float wMax);
            
            void Clamp(const Vector4 &min, const Vector4 &max);
        
        public:
            Vector4 Normalized() const;
            
            float Magnitude() const;
            
            float SqrMagnitude() const;
            
            float Dot(const Vector4 &other) const;
            
            float Distance(const Vector4 &b) const;
            
            float SqrDistance(const Vector4 &b) const;
            
            Vector4 Scale(const Vector4 &b) const;
            
            Vector4 Lerp(const Vector4 &b, float t) const;
            
            Vector4 LerpClamped(const Vector4 &b, float t) const;
            
            Vector4 InverseLerp(const Vector4 &b, float t) const;
            
            Vector4 MoveTowards(const Vector4 &target, float maxDistanceDelta) const;
            
            Vector4 Reflect(const Vector4 &inNormal) const;
            
            float Sum() const;
            
            float Product() const;
            
            float MaxValue() const;
            
            float MinValue() const;
            
            Vector4 Clamped(float valueMin, float valueMax) const;
            
            Vector4 Clamped(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                            float wMax) const;
            
            Vector4 Clamped(const Vector4 &min, const Vector4 &max) const;
            
            bool InRangeInclusive(float minValue, float maxValue) const;
            
            bool InRangeInclusive(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                  float wMax) const;
            
            bool InRangeInclusive(const Vector4 &min, const Vector4 &max) const;
            
            bool InRangeInclusiveMin(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMin(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                     float wMax) const;
            
            bool InRangeInclusiveMin(const Vector4 &min, const Vector4 &max) const;
            
            bool InRangeInclusiveMax(float minValue, float maxValue) const;
            
            bool InRangeInclusiveMax(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                     float wMax) const;
            
            bool InRangeInclusiveMax(const Vector4 &min, const Vector4 &max) const;
            
            bool InRangeExclusive(float minValue, float maxValue) const;
            
            bool InRangeExclusive(float xMin, float yMin, float zMin, float wMin, float xMax, float yMax, float zMax,
                                  float wMax) const;
            
            bool InRangeExclusive(const Vector4 &min, const Vector4 &max) const;
            
            int LexicographicCompare(const Vector4 &other) const;
            
            int MagnitudeCompare(const Vector4 &other) const;
            
            int SumCompare(const Vector4 &other) const;
            
        };
    
}



