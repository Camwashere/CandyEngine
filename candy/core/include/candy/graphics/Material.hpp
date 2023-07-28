#pragma once
#include "shader/Shader.hpp"
#include "Texture.hpp"
#include "vulkan/ImageView.hpp"
#include "vulkan/pipeline/PipelineLayout.hpp"
namespace Candy::Graphics
{
  class Material
  {
  public:
    Shader* shader=nullptr;
    Texture texture;
    ImageView textureImageView;
    VkPipelineLayout pipelineLayout=VK_NULL_HANDLE;
    
  private:
    std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts();
  public:
    void BakePipelineLayout();
    Shader* GetShader();
    
    void Destroy();
  };
}