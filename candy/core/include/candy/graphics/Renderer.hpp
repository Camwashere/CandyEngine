#pragma once
#include "candy/graphics/shader/Shader.hpp"
#include "VertexArray.hpp"
#include "vulkan/RenderPass.hpp"
#include "vulkan/pipeline/GraphicsPipeline.hpp"
#include "GraphicsContext.hpp"
#include "vulkan/pipeline/Pipeline.hpp"
#include <deque>
#include <ranges>
#include "UniformBuffer.hpp"
#include "Texture.hpp"
#include "vulkan/ImageView.hpp"
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
    Texture texture;
    ImageView textureImageView;
    
    
    
    
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
  
    
  public:
    void Draw();
    void Shutdown();
  };
}