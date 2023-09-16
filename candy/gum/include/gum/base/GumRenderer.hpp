#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
#include "GumTree.hpp"
namespace Candy::Gum
{
  
  class GumRenderer
  {
  public:
    struct Stats
    {
      uint32_t drawCalls = 0;
      uint32_t objectCount=0;
      uint32_t quadCount = 0;
      uint32_t vertexCount = 0;
      uint32_t indexCount = 0;
      uint32_t lineCount=0;
      uint32_t textCount=0;
    };
    static void Init();
    
    
  
  };
}