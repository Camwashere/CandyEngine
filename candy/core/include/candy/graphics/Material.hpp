#pragma once
#include "Texture.hpp"
#include "vulkan/ImageView.hpp"
//#include "vulkan/pipeline/PipelineLayout.hpp"
#include "shader/Shader.hpp"
namespace Candy::Graphics
{
  class Material
  {
  public:
    Shader* shader=nullptr;
    Texture texture;
    ImageView textureImageView;
    
  public:
    void Bind();
    Shader* GetShader();
  };
}