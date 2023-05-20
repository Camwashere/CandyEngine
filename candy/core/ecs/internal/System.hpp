#pragma once

#include "InternalBase.hpp"
#include "../entity/Entity.hpp"
namespace Candy::ECS::Internal {
    
    class System
    {
    public:
        std::set<uint32> entities;
        
    };
    
}


