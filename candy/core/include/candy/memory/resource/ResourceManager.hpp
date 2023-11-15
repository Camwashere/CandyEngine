#pragma once
#include <candy/memory/asset/AssetManager.hpp>
#include <CandyPch.hpp>
#include "ShaderManager.hpp"

namespace Candy
{
  class ResourceManager
  {
  private:
    SharedPtr<AssetManager> assetManager;
    ShaderManager shaderManager;
    
    
  public:
  
  };
}