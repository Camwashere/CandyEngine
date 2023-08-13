#pragma once
#include "ShaderData.hpp"
#include "../UniformBuffer.hpp"
#include <candy/math/Matrix.hpp>
#include "../vulkan/pipeline/Pipeline.hpp"
#include <candy/graphics/BufferLayout.hpp>
#include "ShaderProperty.hpp"
namespace Candy::Graphics
{

  class ShaderLayout
  {
  private:
    Pipeline pipeline;
    
    
  public:
    std::vector<ShaderSet> sets{};
    std::vector<ShaderPushProperty*> pushProperties;
    std::vector<ShaderPushBlock> pushBlocks;
    BufferLayout vertexLayout;
    
    std::unordered_map<std::string, uint32_t> pushBlockMap;
    std::unordered_map<std::string, uint32_t> pushPropertyMap;

    
  private:
    VkPipelineLayout BakePipelineLayout();
    std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts();
    VkDescriptorType GetDescriptorType(size_t setIndex);
    void BakePipeline(VkRenderPass renderPass, const std::vector<VkPipelineShaderStageCreateInfo>& createInfos);
    
  public:
    ShaderLayout();
    void BindAll();
    void Bind(uint32_t set);
    uint32_t PushConstant(const std::string& name, const void* data);
    void PushConstant(uint32_t id, const void* data);
    uint32_t SetUniform(const std::string& name, const void* data);
    void SetUniform(uint32_t id, const void* data);

    std::vector<VkPushConstantRange> GetPushConstantRanges();
    std::vector<VkVertexInputBindingDescription> GetVertexBindingDescriptions()const;
    std::vector<VkVertexInputAttributeDescription> GetVertexAttributeDescriptions()const;
    
  public:
    uint32_t AddBlock(const ShaderBlock& block);
    void AddPushBlock(const ShaderPushBlock& block);
    void AddPushProperty(uint32_t pushBlockID, ShaderPushProperty* property);
    void AddVertexInput(const std::string& name, ShaderData::Type type, uint32_t location);
    void AddTexture(const ShaderTexture& texture);

  public:
    [[nodiscard]] VkPipeline GetPipeline()const;
    [[nodiscard]] VkPipelineLayout GetPipelineLayout()const;
    
  private:
    friend class Shader;
  
    
  };
}