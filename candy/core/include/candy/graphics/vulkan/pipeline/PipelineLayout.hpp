#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "candy/graphics/shader/Shader.hpp"
namespace Candy::Graphics
{
  class PipelineLayout
  {
  private:
    VkPipelineLayout layout = VK_NULL_HANDLE;
    
  
  public:
    PipelineLayout();
    
  public:
    operator VkPipelineLayout()const{return layout;}
    operator VkPipelineLayout(){return layout;}
  
  public:
    
    //void Bake(const SharedPtr<Shader>& shader);
  };
}