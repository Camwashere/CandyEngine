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
#include "candy/graphics/material/Material.hpp"
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include <candy/graphics/camera/Camera.hpp>
#include "model/Mesh.hpp"
#include <candy/math/Matrix.hpp>
namespace Candy::Graphics
{
  
  
  class Renderer
  {
  private:
    static Renderer* instance;
    
  private:

    GraphicsContext* target;
    std::array<UniquePtr<RenderPass>, 2> renderPasses{};
    uint8_t currentPassIndex=0;
    
  private:
    static void SetClearColor(Color color);
    
  private:
    Renderer();
    
    
    
    
  public:
    static constexpr uint8_t viewportPassIndex=0;
    static constexpr uint8_t uiPassIndex=1;
    static void BeginScene(const Camera& camera);
    static void EndScene();
    static void Start();
    static void Init();
    static void SetTarget(GraphicsContext* target);
    static void BeginViewportPass();
    static void BeginUIPass();
    static void EndViewportPass();
    static void EndPass();
    static FrameData& GetCurrentFrame();
    static FrameData& GetFrame(uint32_t index);
    static RenderPass& GetCurrentPass();
    static RenderPass& GetUIPass();
    static RenderPass& GetViewportPass();
    
    
  private:
    friend class RenderCommand;
    friend class Vulkan;
  };
}