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
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
namespace Candy::Graphics
{
  
  
  class Renderer
  {
  private:
    static Renderer instance;
    
  private:
    Pipeline pipeline;
    GraphicsContext* target;
    
  private:
    static FrameData& GetCurrentFrame();
    
  private:
    Renderer();
    
    
  public:
    //TODO Finish immediate submit
    static void ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function);
    static void Submit(Material* material);
    static void Start();
    static void SetTarget(GraphicsContext* target);
    static void BeginPass();
    static void EndPass();
    static void BindDescriptorSets(uint32_t uniformOffset);
    static void PushConstants(ShaderData::Stage stage, uint32_t dataSize, const void* data);
    static void PushConstants(ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data);
    static void SetUniform(uint32_t offset, uint32_t size, const void* data);
    static void DrawIndexed(const SharedPtr<VertexArray>& vertexArray);
    static void Shutdown();
  private:
    friend class Vulkan;
  };
}