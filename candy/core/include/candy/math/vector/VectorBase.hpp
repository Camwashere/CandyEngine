#pragma once
#include "VectorExpression.hpp"
#include "../MathOps.hpp"
namespace Candy::Math
{
    
    
    template<typename T, size_t DIMENSIONS>
    struct VectorBase : public VectorExpression<T, VectorBase<T, DIMENSIONS>>
    {
    public:
        static constexpr bool isLeaf = true;
    
    public:
        // How closely are these two vectors aligned. A value of 0 means the vectors are orthogonal
        static constexpr T Dot(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            T result = 0;
            for (size_t i = 0; i < DIMENSIONS; ++i)
            {
                result += a[i] * b[i];
            }
            return result;
        }
        
        static float Determinant(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            return a[0] * b[1] - a[1] * b[0];
        }
        
        static float Distance(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            return (b - a).Magnitude();
        }
        
        static T SqrDistance(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            return (b - a).SqrMagnitude();
        }
        
        static float Slope(const VectorBase<T, DIMENSIONS> &start, const VectorBase<T, DIMENSIONS> &end)
        {
            return (end[1] - start[1]) / (end[0] - start[0]);
        }
        
        static VectorBase<T, DIMENSIONS> Scale(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            VectorBase<T, DIMENSIONS> result;
            for (size_t i = 0; i < DIMENSIONS; ++i)
            {
                result[i] = a[i] * b[i];
            }
            return result;
        }
        
        
        static float Angle(const VectorBase<T, DIMENSIONS> &from, const VectorBase<T, DIMENSIONS> &to)
        {
            float d = (from[0] * to[0] + from[1] * to[1]) / (from.Magnitude() * to.Magnitude());
            return Math::Acos(Math::Clamp(d, -1.0f, 1.0f));
        }
        
        static float SignedAngle(const VectorBase<T, DIMENSIONS> &from, const VectorBase<T, DIMENSIONS> &to)
        {
            return Math::Atan2(from[0] * to[1] - from[1] * to[0], from[0] * to[0] + from[1] * to[1]);
        }
        
        static constexpr VectorBase<T, DIMENSIONS> PerpendicularClockwise(const VectorBase<T, DIMENSIONS> &vec)
        {
            return {vec[1], -vec[0]};
        }
        
        static constexpr VectorBase<T, DIMENSIONS> PerpendicularCounterClockwise(const VectorBase<T, DIMENSIONS> &vec)
        {
            return {-vec[1], vec[0]};
        }
        
        static VectorBase<T, DIMENSIONS> Reflect(const VectorBase<T, DIMENSIONS> &inDirection, const VectorBase<T, DIMENSIONS> &inNormal)
        {
            return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
        }
        
        static VectorBase<T, DIMENSIONS> Max(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            VectorBase<T, DIMENSIONS> result;
            for (size_t i = 0; i < DIMENSIONS; ++i)
            {
                result[i] = Math::Max(a[i], b[i]);
            }
            return result;
        }
        
        static VectorBase<T, DIMENSIONS> Min(const VectorBase<T, DIMENSIONS> &a, const VectorBase<T, DIMENSIONS> &b)
        {
            VectorBase<T, DIMENSIONS> result;
            for (size_t i = 0; i < DIMENSIONS; ++i)
            {
                result[i] = Math::Min(a[i], b[i]);
            }
            return result;
        }
        
        static VectorBase<T, DIMENSIONS> Normalize(const VectorBase<T, DIMENSIONS> &vec)
        {
            return vec / vec.Magnitude();
        }
        
        
    public:
        T data[DIMENSIONS];
        typedef T VALUE_TYPE;
        
    public:
        constexpr inline T& operator[](std::size_t index) noexcept {return data[index];}
        constexpr inline T operator[](std::size_t index) const {return data[index];}
    
    public:
        constexpr inline size_t Dimensions()const{return DIMENSIONS;}
        constexpr inline size_t Size()const{return DIMENSIONS;}
    };
    
    
    
    
    
    
    
    
    
    
    
    
   
    
    
    
}