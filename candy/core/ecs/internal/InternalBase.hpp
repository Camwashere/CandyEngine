#pragma once

#include <queue>
#include <array>
#include <set>
#include <boost/dynamic_bitset.hpp>
#include <memory>
#include <unordered_map>
#include <Candy/CandyEngineBase.hpp>
#include <iostream>
namespace Candy::ECS::Internal {
    const uint32 MAX_COMPONENTS = 1000;
    typedef boost::dynamic_bitset<uint32> Signature;
    typedef uint32 ComponentType;
}


