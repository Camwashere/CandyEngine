#pragma once
#include "candy/graphics/shader/Shader.hpp"
#include "VertexArray.hpp"
#include "vulkan/RenderPass.hpp"
#include "GraphicsContext.hpp"
#include "vulkan/pipeline/Pipeline.hpp"
#include <deque>
#include <ranges>
#include "UniformBuffer.hpp"
#include "Texture.hpp"
#include "vulkan/ImageView.hpp"
#include "Material.hpp"
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
namespace Candy::Graphics
{
  
  
  class Renderer
  {
  private:
    static Renderer* instance;
    
  private:
    std::vector<Material*> materials{};
    GraphicsContext* target;
    UniquePtr<RenderPass> renderPass;
    
  private:
    
    static VkRenderPassBeginInfo BeginRenderPass();
    
  private:
    Renderer();
    static VkPipelineLayout GetPipelineLayout();
    
  public:
    static void Submit(Material* material);
    static void Start();
    static void Init();
    static void SetTarget(GraphicsContext* target);
    static void InitRenderPass(VkSurfaceKHR surface);
    static void BeginPass();
    static void EndPass();
    static FrameData& GetCurrentFrame();
    static VkRenderPass GetRenderPass();
    
  private:
    friend class Vulkan;
  };
}