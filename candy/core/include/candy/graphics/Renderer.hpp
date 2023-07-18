#pragma once
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "vulkan/RenderPass.hpp"
#include "vulkan/pipeline/GraphicsPipeline.hpp"
#include "GraphicsContext.hpp"
#include "vulkan/pipeline/Pipeline.hpp"
#include <deque>
#include <ranges>
namespace Candy::Graphics
{
  
  
  class Renderer
  {
  private:
    SharedPtr<Shader> shader;
    SharedPtr<VertexArray> vertexArray;
    Pipeline pipeline;
    //GraphicsPipeline graphicsPipeline;
    GraphicsContext* target;
    
    
    
  private:
    void UpdatePushConstants();
    
    FrameData& GetCurrentFrame();
    
  public:
    explicit Renderer(GraphicsContext* target);
    
  public:
    void Draw();
    void Shutdown();
  };
}