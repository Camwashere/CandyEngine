#pragma once
#include "Asset.hpp"
#include <unordered_map>
namespace Candy
{
  class AssetManager
  {
  private:
    std::unordered_map<uint32_t, AssetData> assetData;
    std::unordered_map<uint32_t, Asset> assets;
  
  };
}