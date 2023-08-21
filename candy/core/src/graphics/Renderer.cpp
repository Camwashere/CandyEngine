#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/app/Application.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer3D.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  
  struct SceneData
  {
    Matrix4 viewMatrix{};
    Matrix4 projectionMatrix{};
  };
  
  static SceneData sceneData{};
  Renderer::Renderer() : target(nullptr)
  {
  
  }
  
  Renderer* Renderer::instance = nullptr;
  
  

  void Renderer::Init()
  {
    Renderer::instance = new Renderer();
    
  }
  void Renderer::SubmitMesh(const Mesh& mesh, const Math::Matrix4& transform)
  {
    if (mesh.IsValid())
    {
    
    }
  }
  void Renderer::Submit(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertexArray, const Math::Matrix4& transform)
  {
    shader->SetMatrix("proj", sceneData.projectionMatrix);
    shader->SetMatrix("view", sceneData.viewMatrix);
    shader->SetMatrix("model", transform);
    shader->Commit();
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  
  }
  void Renderer::Start()
  {
    instance->target->SwapBuffers();
    Renderer::BeginViewportPass();
  }
 
  void Renderer::SetTarget(GraphicsContext* target)
  {
    instance->target = target;
    VkSurfaceFormatKHR surfaceFormat = instance->target->GetSurfaceFormat();
    const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
    instance->renderPasses[viewportPassIndex] = CreateUniquePtr<RenderPass>(surfaceFormat.format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    instance->renderPasses[selectionPassIndex] = CreateUniquePtr<RenderPass>(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    instance->renderPasses[uiPassIndex] = CreateUniquePtr<RenderPass>(surfaceFormat.format, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
  }
  void Renderer::BeginViewportPass()
  {
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(viewportPassIndex);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    
    clearValues[0].color = {0.2f, 0.2f, 0.2f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetViewportPass().BeginPass(GetCurrentFrame().viewportData.viewportFrameBuffer, size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }
  void Renderer::BeginSelectionPass()
  {
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(selectionPassIndex);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color.int32[0]=-1;
    //clearValues[0].color = {0.2f, 0.2f, 0.2f, 1.0f};
    //clearValues[0].color = {-1.0f, -1.0f, -1.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetSelectionPass().BeginPass(GetCurrentFrame().viewportData.selectionFrameBuffer, size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }
  void Renderer::BeginUIPass()
  {
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(uiPassIndex);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = {0.2f, 0.2f, 0.2f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetUIPass().BeginPass(instance->target->swapChain->GetCurrentFrameBuffer(), size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }

  
  void Renderer::BeginScene(const Camera& camera)
  {
    sceneData.viewMatrix = camera.GetViewMatrix();
    sceneData.projectionMatrix = camera.GetProjectionMatrix();
  }
  void Renderer::EndScene()
  {
  
  }

  void Renderer::SetClearColor(Color color)
  {
    GetViewportPass().SetClearColor(color);
  }
  void Renderer::EndViewportPass()
  {
  
  }
  void Renderer::EndPass()
  {
    RenderCommand::Submit();
  }
  RenderPass& Renderer::GetCurrentPass()
  {
    return *instance->renderPasses[instance->currentPassIndex];
  }
  RenderPass& Renderer::GetUIPass()
  {
    return *instance->renderPasses[uiPassIndex];
  }

  RenderPass& Renderer::GetViewportPass()
  {
    return *instance->renderPasses[viewportPassIndex];
  }
  RenderPass& Renderer::GetSelectionPass()
  {
    return *instance->renderPasses[selectionPassIndex];
  }
  FrameData& Renderer::GetCurrentFrame(){return instance->target->GetCurrentFrame();}
  FrameData& Renderer::GetFrame(uint32_t index){return instance->target->GetFrame(index);}
  


  

}