#pragma once
#include <Candy/CandyEngineBase.hpp>
#include <Candy/Math.hpp>
namespace Candy::Collections{
    template<typename T, std::size_t SIZE, std::size_t DIMENSIONS, std::size_t ARRAY_SIZE=Math::Pow<DIMENSIONS>(SIZE)>
    requires(DIMENSIONS>1)
    class MultiArray
    {
    protected:
        T data[ARRAY_SIZE];
    
    protected:
        MultiArray()=default;
        MultiArray(const T* arrayData){memcpy(data, arrayData, ARRAY_SIZE);}
        MultiArray(const MultiArray<T, SIZE, DIMENSIONS>& other) {memcpy(data, other.data, ARRAY_SIZE);}
    
    public:
        inline constexpr std::size_t SizeTotal()const{return ARRAY_SIZE;}
        inline constexpr std::size_t Dimensions()const{return DIMENSIONS;}
        inline constexpr std::size_t Size()const{return SIZE;}
    };

}