#pragma once
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "vulkan/RenderPass.hpp"
#include "vulkan/pipeline/GraphicsPipeline.hpp"
#include "GraphicsContext.hpp"
#include "vulkan/pipeline/Pipeline.hpp"
#include <deque>
#include <ranges>
#include "UniformBuffer.hpp"
namespace Candy::Graphics
{
  
  
  class Renderer
  {
  private:
    SharedPtr<Shader> shader;
    SharedPtr<VertexArray> vertexArray;
    Pipeline pipeline;
    GraphicsContext* target;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<SharedPtr<UniformBuffer>> uniformBuffers;
    
    
    
  private:
    void CreateDescriptorPool();
    void CreateDescriptorSets();
    void CreateUniformBuffers();
    void UpdateUniformBuffer();
    void UpdatePushConstants();
    FrameData& GetCurrentFrame();
    
  public:
    explicit Renderer(GraphicsContext* target);
    
  public:
    void Draw();
    void Shutdown();
  };
}