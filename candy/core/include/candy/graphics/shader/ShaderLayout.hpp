#pragma once
#include "ShaderData.hpp"
#include "../UniformBuffer.hpp"
#include <candy/math/Matrix.hpp>
#include <candy/graphics/BufferLayout.hpp>
#include "ShaderProperty.hpp"
#include "candy/graphics/shader/config/ShaderSettings.hpp"
namespace Candy::Graphics
{

  class ShaderLayout
  {
  private:
    //const ShaderSettings settings;
    VkPipelineLayout pipelineLayout;
    //Pipeline pipeline;
    
    
  public:
    std::vector<ShaderSet> sets{};
    std::vector<ShaderPushProperty*> pushProperties;
    std::vector<ShaderPushBlock> pushBlocks;
    std::vector<ShaderSpecializationConstant> specConstants;
    BufferLayout vertexLayout;
    size_t materialBufferSize;
    size_t globalBufferSize;
    std::unordered_map<std::string, uint32_t> pushBlockMap;
    std::unordered_map<std::string, uint32_t> pushPropertyMap;
    std::unordered_map<std::string, uint32_t> specConstantMap;

    
  private:
    //TODO Don't make this require render pass index, this function is currently the reason why overlay2D needs a seperate descriptor set
    void BakePipelineLayout(uint32_t renderPassIndex);
    VkDescriptorType GetDescriptorType(size_t setIndex);
    //void BakePipeline(const std::vector<VkPipelineShaderStageCreateInfo>& createInfos);
    
  public:
    explicit ShaderLayout();
    void BindAllDescriptorSets(uint32_t renderPassIndex);
    void BindDescriptorSet(uint32_t renderPassIndex, uint32_t set);
    uint32_t GetPushID(const std::string& name)const;
    uint32_t PushConstant(const std::string& name, const void* data);
    void PushConstant(uint32_t id, const void* data);
    uint32_t SetUniform(const std::string& name, const void* data);
    void SetUniform(uint32_t id, const void* data);

    std::vector<VkPushConstantRange> GetPushConstantRanges();
    std::vector<VkVertexInputBindingDescription> GetVertexBindingDescriptions()const;
    std::vector<VkVertexInputAttributeDescription> GetVertexAttributeDescriptions()const;
    
  public:
    void AddSpecConstant(const ShaderSpecializationConstant& specConstant);
    bool HasSpecConstant(const std::string& name)const;
    bool GetSpecConstant(const std::string& name, ShaderSpecializationConstant* specConstant)const;
    uint32_t AddBlock(const ShaderBlock& block);
    void AddPushBlock(const ShaderPushBlock& block);
    void AddPushProperty(uint32_t pushBlockID, ShaderPushProperty* property);
    void AddVertexInput(const std::string& name, ShaderData::Type type, uint32_t location);
    void AddTexture(const ShaderTexture& texture);

  public:
    [[nodiscard]] VkPipelineLayout GetPipelineLayout()const{return pipelineLayout;}
    [[nodiscard]] size_t GetMaterialBufferSize()const{return materialBufferSize;}
    [[nodiscard]] size_t GetGlobalBufferSize()const{return globalBufferSize;}
    
  private:
    friend class Shader;
  
    
  };
}