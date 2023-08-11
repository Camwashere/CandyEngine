#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
#include "GumTree.hpp"
namespace Candy::Gum
{
  
  class GumRenderer
  {
  private:
    SharedPtr<Graphics::Shader> shader;
    UniquePtr<Graphics::RenderPass> renderPass;
    GumTree tree;
    
  public:
    GumRenderer();
    
    
  
  };
}