#pragma once
#include <cstdint>
#include <concepts>
#include <cmath>
template<typename... T>
concept FloatingPoint = requires{std::is_floating_point_v<T...>;};
namespace Candy::Math
{
    template<typename T>
    struct Limit
    {
        static constexpr T Max(){return 0;}
        static constexpr T Min(){return 0;}
        static constexpr bool IsSpecialized(){return false;}
        
    };
    
    template<FloatingPoint T>
    struct Limit<T>
    {
        static constexpr T Max(){return FP_INFINITE;}
        static constexpr T Min(){return -FP_INFINITE;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    
    template<>
    struct Limit<std::uint8_t>
    {
        static constexpr std::uint8_t Max(){return UINT8_MAX;}
        static constexpr std::uint8_t Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::uint16_t>
    {
        static constexpr std::uint16_t Max(){return UINT16_MAX;}
        static constexpr std::uint16_t Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::uint32_t>
    {
        static constexpr std::uint32_t Max(){return UINT32_MAX;}
        static constexpr std::uint32_t Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    template<>
    struct Limit<std::uint64_t>
    {
        static constexpr std::uint64_t Max(){return UINT64_MAX;}
        static constexpr std::uint64_t Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::int8_t>
    {
        static constexpr std::int8_t Max(){return INT8_MAX;}
        static constexpr std::int8_t Min(){return INT8_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::int16_t>
    {
        static constexpr std::int16_t Max(){return INT16_MAX;}
        static constexpr std::int16_t Min(){return INT16_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::int32_t>
    {
        static constexpr std::int32_t Max(){return INT32_MAX;}
        static constexpr std::int32_t Min(){return INT32_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<std::int64_t>
    {
        static constexpr std::int64_t Max(){return INT64_MAX;}
        static constexpr std::int64_t Min(){return INT64_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<bool>
    {
        static constexpr bool Max(){return true;}
        static constexpr bool Min(){return false;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<char>
    {
        static constexpr char Max(){return CHAR_MAX;}
        static constexpr char Min(){return CHAR_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    
    
    
}