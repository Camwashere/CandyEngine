#pragma once
#include <cstdint>
#include <type_traits>
namespace Candy {
    template<class T>
    constexpr bool always_false=false;
    
    typedef unsigned int uint;
    typedef unsigned long ulong;
    typedef unsigned short ushort;
    typedef std::uint8_t uint8;
    typedef std::uint16_t uint16;
    typedef std::uint32_t uint32;
    typedef std::uint64_t uint64;
    typedef std::uintmax_t uintmax;
    
    typedef std::int8_t int8;
    typedef std::int16_t int16;
    typedef std::int32_t int32;
    typedef std::int64_t int64;
    typedef std::intmax_t intmax;
    
    
    
    
    struct Primitives
    {
        template<typename T>
        static consteval int FindPrimitiveTypeID()
        {
            if (std::is_same<T, int8>::value)
            {
                return 0;
            }
            if (std::is_same<T, uint8>::value)
            {
                return 1;
            }
            if (std::is_same<T, int16>::value)
            {
                return 2;
            }
            if (std::is_same<T, uint16>::value)
            {
                return 3;
            }
            if (std::is_same<T, int32>::value)
            {
                return 4;
            }
            if (std::is_same<T, uint32>::value)
            {
                return 5;
            }
            if (std::is_same<T, int64>::value)
            {
                return 6;
            }
            if (std::is_same<T, uint64>::value)
            {
                return 7;
            }
            if (std::is_same<T, float>::value)
            {
                return 8;
            }
            if (std::is_same<T, double>::value)
            {
                return 9;
            }
            return -1;
        }
    };
    
    
    
    
    
    
}