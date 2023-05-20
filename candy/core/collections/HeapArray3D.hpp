#pragma once
#include <Candy/Math.hpp>
namespace Candy::Collections {
    template<typename T>
    class HeapArray3D
    {
    private:
        const std::size_t size;
        const std::size_t sizeSquared;
        const std::size_t sizeCubed;
        T* data;
    
    private:
        /*constexpr std::size_t Index2D(std::size_t xIndex, std::size_t yIndex)const{return yIndex+xIndex*size;}
        constexpr std::size_t Index2D(const Math::Vector2Int& index)const{return index.x+index.y*size;}*/
        constexpr std::size_t Index3D(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const{return yIndex+xIndex*size+zIndex*sizeSquared;}
        constexpr std::size_t Index3D(const Math::Vector3Int& index)const{return index.y + index.x*size+index.z*sizeSquared;}
    
    public:
        HeapArray3D(std::size_t arraySize) : size(arraySize), sizeSquared(size*size), sizeCubed(sizeSquared*size), data(new T[sizeCubed]){}
        ~HeapArray3D() {delete[] data;}
    
    public:
        T& operator[](std::size_t index){return data[index];}
        const T& operator[](std::size_t index)const{return data[index];}
        
        /*T& operator[](std::size_t xIndex, std::size_t yIndex){return data[Index2D(xIndex, yIndex)];}
        const T& operator[](std::size_t xIndex, std::size_t yIndex)const{return data[Index2D(xIndex, yIndex)];}
        T& operator[](const Math::Vector2Int& index){return data[Index2D(index)];}
        const T& operator[](const Math::Vector2Int& index)const{return data[Index2D(index)];}*/
        
        T& operator[](std::size_t xIndex, std::size_t yIndex, std::size_t zIndex){return data[Index3D(xIndex, yIndex, zIndex)];}
        const T& operator[](std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const{return data[Index3D(xIndex, yIndex, zIndex)];}
        T& operator[](const Math::Vector3Int& index){return data[Index3D(index)];}
        const T& operator[](const Math::Vector3Int& index)const{return data[Index3D(index)];}
    
    public:
        constexpr std::size_t Size()const{return size;}
        constexpr std::size_t SizeSquared()const{return sizeSquared;}
        constexpr std::size_t SizeCubed()const{return sizeCubed;}
        constexpr std::size_t SizeTotal()const{return sizeCubed;}
        
        
        
        
        
    };
}
