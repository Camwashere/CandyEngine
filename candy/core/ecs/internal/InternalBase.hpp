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
    typedef boost::dynamic_bitset<std::uint32_t> Signature;
    typedef std::uint32_t ComponentType;
}


