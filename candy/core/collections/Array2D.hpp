#pragma once
#include "MultiArray.hpp"
namespace Candy::Collections{
    template<typename T, std::size_t SIZE, std::size_t SIZE_SQUARED=SIZE*SIZE>
    class Array2D : public MultiArray<T, SIZE, 2>
    {
    public:
        Array2D()=default;
        Array2D(const T* arrayData) : MultiArray<T, SIZE, 2>(arrayData){}
        Array2D(const MultiArray<T, SIZE, 2>& other) : MultiArray<T, SIZE, 2>(other){}
    public:
        inline constexpr T& operator[](std::size_t index){return this->data[index];}
        inline constexpr const T& operator[](std::size_t index)const{return this->data[index];}
        inline constexpr T& operator[](std::size_t xIndex, std::size_t yIndex){return this->data[xIndex+yIndex*SIZE];}
        inline constexpr const T& operator[](std::size_t xIndex, std::size_t yIndex)const{return this->data[xIndex+yIndex*SIZE];}
    };
}