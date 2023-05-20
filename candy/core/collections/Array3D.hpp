#pragma once
#include "MultiArray.hpp"


namespace Candy::Collections{
    template<typename T, std::size_t  SIZE, std::size_t SIZE_SQUARED=SIZE*SIZE>
    class Array3D : public MultiArray<T, SIZE, 3>
    {
    private:
        inline constexpr uint GetArrayIndex(std::size_t x, std::size_t y, std::size_t z)const{return y+x*SIZE+z*SIZE_SQUARED;}
        inline constexpr uint GetArrayIndex(const Math::Vector3Int& index)const{return index.y+index.x*SIZE+index.z*SIZE_SQUARED;}
    public:
        Array3D()=default;
        Array3D(const T* arrayData) : MultiArray<T, SIZE, 2>(arrayData){}
        Array3D(const MultiArray<T, SIZE, 2>& other) : MultiArray<T, SIZE, 2>(other){}
    public:
        inline constexpr T& operator[](std::size_t index){return this->data[index];}
        inline constexpr const T& operator[](std::size_t index)const{return this->data[index];}
        
        
        inline constexpr T& operator[](std::size_t xIndex, std::size_t yIndex, std::size_t zIndex){return this->data[GetArrayIndex(xIndex, yIndex, zIndex)];}
        inline constexpr const T& operator[](std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const{return this->data[GetArrayIndex(xIndex, yIndex, zIndex)];}
        inline constexpr T& operator[](const Math::Vector3Int& index){return this->data[GetArrayIndex(index)];}
        inline constexpr const T& operator[](const Math::Vector3Int& index)const{return this->data[GetArrayIndex(index)];}
    
    public:
        inline constexpr std::size_t SizeSquared()const{return SIZE_SQUARED;}
        inline constexpr std::size_t SizeCubed()const{return this->SizeTotal();}
    };
    
}