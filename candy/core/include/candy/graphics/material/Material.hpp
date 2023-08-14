#pragma once
#include "candy/graphics/shader/Shader.hpp"
#include "MaterialData.hpp"
namespace Candy::Graphics
{
  
  
  class Material
  {
  private:
    Shader* shader=nullptr;
    std::vector<MaterialParameter> parameters;
    std::vector<MaterialTextureParameter> textureParameters;
    std::unordered_map<std::string, size_t> nameToParameterMap;
    std::unordered_map<std::string, size_t> nameToTextureParameterMap;
    std::vector<VkWriteDescriptorSet> writes;
    size_t bufferSize=0;
    //Texture texture;
    //ImageView textureImageView;
  private:
    void CalculateParameterLayout();
    void CalculateBufferSize();
    
  
    
    
  public:
    void SetShader(Shader* shader);
    void SetParameter(const std::string& name, const ShaderData::Value& value);
    void SetTexture(const std::string& name, const std::filesystem::path& path);
    void Bind();
    //TODO: Temporary function. Binding sets other than material will be moved to something else
    void Bind(uint32_t set);
    
    Shader* GetShader();
  };
}