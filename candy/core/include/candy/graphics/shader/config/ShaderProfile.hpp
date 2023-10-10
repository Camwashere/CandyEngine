#pragma once
#include <vector>
#include "candy/graphics/shader/ShaderProperty.hpp"
#include "candy/collections/GenericBuffer.hpp"
#include "candy/graphics/Color.hpp"
#include <candy/graphics/shader/config/ShaderEnums.hpp>
#include <candy/graphics/shader/config/ShaderProfileSettings.hpp>
#include <candy/graphics/shader/config/ShaderDynamicState.hpp>
namespace Candy::Graphics
{
  class SpecializationConstantInput
  {
  private:
    std::string name;
    ShaderData::Type type;
    Collections::GenericBuffer value;
    
  public:
    template<typename T>
    SpecializationConstantInput(std::string  constantName, T constantValue) : name(std::move(constantName)), type(ShaderData::TypeFrom<T>())
    {
      size_t size = ShaderData::TypeSize(type);
      CANDY_CORE_ASSERT(size > 0, "INVALID SPECIALIZATION CONSTANT TYPE");
      value.Add(constantValue);
    }
    
    [[nodiscard]] const std::string& GetName()const;
    [[nodiscard]] ShaderData::Type GetType()const;
    [[nodiscard]] const Collections::GenericBuffer& GetValue()const;
    [[nodiscard]] size_t GetSize()const;
  };
  
  
  
  class ShaderConfiguration
  {
  private:
    VkPipeline pipeline = VK_NULL_HANDLE;
    ShaderConfigurationSettings settings;
    uint32_t renderPassIndex;
    
  public:
    explicit ShaderConfiguration(uint32_t renderPassIndex);
    ShaderConfiguration(ShaderConfigurationSettings  configSettings, uint32_t defaultRenderPassIndex);
    
    friend class ShaderProfile;
  };

  class ShaderLayout;
  class SpecConstantData;
  
  
  class ShaderProfile
  {
  private:
    ShaderProfileSettings settings;
    std::vector<ShaderConfiguration> configurations;
    uint32_t activeConfig=0;
    
  private:
    [[nodiscard]] std::vector<VkDynamicState> GetDynamicStates()const;
    [[nodiscard]] VkPipelineViewportStateCreateInfo GetViewportState()const;
    [[nodiscard]] VkPipelineMultisampleStateCreateInfo GetMultisampling()const;
    [[nodiscard]] VkPipelineInputAssemblyStateCreateInfo GetInputAssembly()const;
    [[nodiscard]] VkPipelineDepthStencilStateCreateInfo GetDepthStencil()const;
    [[nodiscard]] std::vector<VkPipelineColorBlendAttachmentState> GetColorBlendAttachments()const;
    [[nodiscard]] VkPipelineRasterizationStateCreateInfo GetRasterizer()const;
    
  private:
    std::vector<SpecConstantData> GetSpecializationConstantLayout(const std::vector<VkPipelineShaderStageCreateInfo>& createInfos, const ShaderLayout& layout);
    void OnBind()const;
    void DynamicStateBind(DynamicStateType type) const;
    void BakeInternal(const std::vector<std::vector<SpecConstantData>>& profileCreateInfos, const ShaderLayout& shaderLayout);
    
  public:
    ShaderProfile(ShaderProfileSettings profileSettings);
    ShaderProfile(ShaderProfileSettings profileSettings, const std::vector<ShaderConfigurationSettings>& shaderConfigs);
    
    [[nodiscard]] VkPipeline GetActivePipeline()const;
    [[nodiscard]] VkPipelineBindPoint GetBindPoint()const;
    [[nodiscard]] uint32_t GetActiveRenderPassIndex()const;
    void Bind()const;
    void Bake(const std::vector<VkPipelineShaderStageCreateInfo>& baseCreateInfos, const ShaderLayout& layout);
    
    
    friend class Shader;
    friend class RenderCommand;
  
  };
  
  
}