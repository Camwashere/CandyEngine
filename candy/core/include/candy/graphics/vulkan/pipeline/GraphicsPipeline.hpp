#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "../../VertexArray.hpp"
#include "../../Shader.hpp"
#include "../RenderPass.hpp"
namespace Candy::Graphics
{
  struct UniformBufferObject {
    alignas(16) Math::Matrix4 model;
    alignas(16) Math::Matrix4 view;
    alignas(16) Math::Matrix4 proj;
    
    
  };
    class GraphicsPipeline
    {
    private:
        VkPipelineLayout pipelineLayout=VK_NULL_HANDLE;
        VkPipeline pipeline=VK_NULL_HANDLE;
        
    public:
        GraphicsPipeline()=default;
        
    public:
        void CreatePipelineLayout(VkDescriptorSetLayout descriptorSetLayout);
        void Create(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Shader>& shader, const RenderPass& renderPass, VkDescriptorSetLayout descriptorSetLayout=VK_NULL_HANDLE);
        void Destroy();
        
    public:
        [[nodiscard]] VkPipelineLayout Layout()const;
        [[nodiscard]] VkPipeline Pipeline()const;
    };
}
