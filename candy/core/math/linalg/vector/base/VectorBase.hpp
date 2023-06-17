#pragma once

#include <array>
#include <initializer_list>
#include <iostream>
#include "../../../general/MathOps.hpp"
#include "VectorExpression.hpp"

namespace Candy::Math{
    
    template<typename T, size_t DIMENSIONS>
    requires (DIMENSIONS>0)
    struct VectorBase : public VectorExpression<T, VectorBase<T, DIMENSIONS>>{
    public:
        static constexpr bool isLeaf=true;
        std::array<T, DIMENSIONS> data;
    
    public:
        constexpr VectorBase() {data.fill(0);}
        constexpr VectorBase(const T& value){data.fill(value);}
        constexpr VectorBase(const T&& value){data.fill(value);}
        constexpr VectorBase(const T* values){data.fill(values);}
        constexpr VectorBase(T* values){data.fill(values);}
        constexpr VectorBase(const VectorBase<T, DIMENSIONS>& other) : data(other.data){}
        template<typename...Args>
        requires(Numeric<Args...>)
        VectorBase(Args... args)
        {
            size_t size = sizeof...(args);
            int cap = Math::Min(size, DIMENSIONS);
            int count=0;
            for (auto& i : {args...})
            {
                data[count]=i;
                count++;
                if(count==DIMENSIONS)
                {
                    break;
                }
            }
        }
        template <typename U, typename E>
        requires(Numeric<U>)
        constexpr VectorBase(VectorExpression<U,E> const& expr)
        {
            for (uint i=0; i<expr.Size(); ++i)
            {
                data[i] = expr[i];
            }
        }
    public:
        constexpr inline auto& operator[](uint index) noexcept {return data[index];}
        constexpr inline const auto& operator[](uint index) const {return data[index];}
    
    
    public:
        constexpr inline size_t Dimensions()const{return DIMENSIONS;}
        constexpr inline size_t Size()const{return DIMENSIONS;}
    };
    template<typename T>
    struct VectorBase<T, 2> : public VectorExpression<T, VectorBase<T, 2>>
    {
    public:
        static constexpr bool isLeaf=true;
        union
        {
            std::array<T, 2> data;
            struct{T x, y;};
            struct{T min, max;};
        };
    public:
        constexpr VectorBase() {data.fill(0);}
        constexpr VectorBase(const T& value){data.fill(value);}
        constexpr VectorBase(const T&& value){data.fill(value);}
        constexpr VectorBase(const T* values){data.fill(values);}
        constexpr VectorBase(const VectorBase<T, 2>& other) : data(other.data){}
        constexpr VectorBase(T xValue, T yValue) : x(xValue), y(yValue){}
        template<Numeric<T>...Args>
        VectorBase(Args... args)
        {
            size_t size = sizeof...(args);
            int cap = Math::Min(size, Size());
            int count=0;
            for (auto& i : {args...})
            {
                data[count]=i;
                count++;
                if(count==2)
                {
                    break;
                }
            }
        }
        template <typename U, typename E>
        requires(Numeric<U>)
        constexpr VectorBase(const VectorExpression<U,E>& expr)
        {
            data[0] = expr[0];
            data[1] = expr[1];
        }
    
    public:
        constexpr inline T& operator[](uint index) noexcept {return data[index];}
        constexpr inline T operator[](uint index) const {return data[index];}
    
    public:
        constexpr inline size_t Dimensions()const{return 2;}
        constexpr inline size_t Size()const{return 2;}
        
    };
    template<typename T>
    struct VectorBase<T, 3> : public VectorExpression<T, VectorBase<T, 3>> {
    public:
        static constexpr bool isLeaf=true;
        union
        {
            std::array<T, 3> data;
            struct{T x, y, z;};
            struct{T r, g, b;};
        };
    public:
        constexpr VectorBase() {data.fill(0);}
        constexpr VectorBase(const T& value){data.fill(value);}
        constexpr VectorBase(const T&& value){data.fill(value);}
        constexpr VectorBase(const T* values){data.fill(values);}
        constexpr VectorBase(const VectorBase<T, 3>& other) : data(other.data){}
        constexpr VectorBase(T xValue, T yValue, T zValue) : x(xValue), y(yValue), z(zValue){}
        
        template <typename U, typename E>
        requires(Numeric<U>)
        VectorBase(VectorExpression<U,E> const& expr)
        {
            data[0] = expr[0];
            data[1] = expr[1];
            data[2] = expr[2];
        }
    
    public:
        constexpr inline size_t Dimensions()const{return 3;}
        constexpr inline size_t Size()const{return 3;}
    public:
        constexpr inline T& operator[](uint index) noexcept {return data[index];}
        constexpr inline T operator[](uint index) const {return data[index];}
    };
    
    template<typename T>
    struct VectorBase<T, 4> : public VectorExpression<T, VectorBase<T, 4>> {
    public:
        static constexpr bool isLeaf=true;
        union
        {
            std::array<T, 4> data;
            struct{T x, y, z, w;};
            struct{T r, g, b, a;};
            struct{T x1, y1, x2, y2;};
        };
    public:
        constexpr VectorBase() {data.fill(0);}
        constexpr VectorBase(const T& value){data.fill(value);}
        constexpr VectorBase(const T&& value){data.fill(value);}
        constexpr VectorBase(const T* values){
            for (int i=0; i<Size(); i++)
            {
                data[i] = values[i];
            }
        }
        constexpr VectorBase(const VectorBase<T, 4>& other) : data(other.data){}
        constexpr VectorBase(T xValue, T yValue, T zValue, T wValue) : x(xValue), y(yValue), z(zValue), w(wValue){}
        
        template <typename U, typename E>
        requires(Numeric<U>)
        constexpr VectorBase(VectorExpression<U,E> const& expr)
        {
            data[0] = expr[0];
            data[1] = expr[1];
            data[2] = expr[2];
            data[3] = expr[3];
        }
    public:
        constexpr inline size_t Dimensions()const{return 4;}
        constexpr inline size_t Size()const{return 4;}
    public:
        constexpr inline T& operator[](uint index) noexcept {return data[index];}
        constexpr inline T operator[](uint index) const {return data[index];}
    };
    
    
    
    
}