#pragma once
#include "PrimitiveTypes.hpp"

namespace Candy
{
    class UUID
    {
    private:
        uint64 value;
        
    public:
        UUID();
        UUID(uint64 uuid);
        UUID(const UUID&)=default;
        
        operator uint64() const{return value;}
    };
}

namespace std {
    template <typename T> struct hash;
    
    template<>
    struct hash<Candy::UUID>
    {
        std::size_t operator()(const Candy::UUID& uuid) const
        {
            return (Candy::uint64)uuid;
        }
    };
    
}