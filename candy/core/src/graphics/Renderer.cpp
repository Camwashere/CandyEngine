#include <candy/graphics/Renderer.hpp>
#include "candy/graphics/shader/Shader.hpp"
#include <candy/graphics/vulkan/RenderPass.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include "candy/graphics/camera/PerspectiveCamera.hpp"
#include <candy/graphics/camera/EditorCamera.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/ui/Gizmo.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/app/Application.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include "candy/graphics/font/Font.hpp"
#include "candy/graphics/Renderer2D.hpp"
#include <candy/graphics/vulkan/RenderPassConfig.hpp>
#include <candy/graphics/vulkan/RenderPassScheduler.hpp>

namespace Candy::Graphics
{
  using namespace Math;
  
  
  struct SceneData
  {
    Matrix4 viewMatrix{};
    Matrix4 projectionMatrix{};
  };
  
  struct CameraData
  {
    Math::Matrix4 viewMatrix{};
    Math::Matrix4 projectionMatrix{};
    Math::Matrix4 viewProjectionMatrix{};
    
    Math::Matrix4 viewMatrix2D{};
    Math::Matrix4 projectionMatrix2D{};
    Math::Matrix4 viewProjectionMatrix2D{};
  };
  
  static SceneData sceneData{};

  
  
  struct RendererData
  {
    GraphicsContext* target=nullptr;
    CameraData cameraData;
    
    RenderPassScheduler renderPasses;
    
    uint8_t currentPassIndex = 0;
    Color clearColor = Color::black;
  };
  
  static RendererData data;
  
  
  

  void Renderer::Init(VkSurfaceFormatKHR surfaceFormat)
  {
    CANDY_PROFILE_FUNCTION();
    Font::Init("config/font/atlasGeneratorSettings.yml", "assets/fonts");
    SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    
    
    //const VkFormat requestSurfaceImageFormat[] = {VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM};
    
    data.renderPasses.AddPass("Viewport3D", RenderPassBuilder::FastBuild(surfaceFormat.format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    
    RenderPassBuilder builder;
    builder.AddAttachment(PassAttachmentBuilder(surfaceFormat.format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
      .SetMainOps(VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE)
      .SetStencilOps(VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetSamples(VK_SAMPLE_COUNT_1_BIT).Build())
    .AddAttachment(PassAttachmentBuilder(GraphicsContext::FindDepthFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
      .SetMainOps(VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetStencilOps(VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetSamples(VK_SAMPLE_COUNT_1_BIT).Build())
      .AddSubpass(SubpassBuilder(VK_PIPELINE_BIND_POINT_GRAPHICS).AddColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL).SetDepthAttachment(1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL))
    .AddDefaultDependency();
    
    
    data.renderPasses.AddPass("Overlay2D", builder.GetConfig());
    data.renderPasses.AddPass("Color Picking", RenderPassBuilder::FastBuild(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    data.renderPasses.AddPass("UI", RenderPassBuilder::FastBuild(surfaceFormat.format, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR));
    
  }
  

  void Renderer::SetTarget(GraphicsContext* target)
  {
    CANDY_PROFILE_FUNCTION();
    data.target = target;
  }
  
  void Renderer::BeginPass()
  {
  
  }
  void Renderer:: BeginViewportPass()
  {
    CANDY_PROFILE_FUNCTION();
    data.currentPassIndex = viewportPassIndex;
    
    
    std::array<VkClearValue, 2> clearValues{};
    
    
    clearValues[0].color = {data.clearColor.r, data.clearColor.g, data.clearColor.b, data.clearColor.a};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {data.target->swapChain->extent.width, data.target->swapChain->extent.height};
    
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = data.renderPasses[viewportPassIndex];
    beginPassInfo.framebuffer = GetCurrentFrame().viewportData.viewportFrameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    
    beginPassInfo.clearValueCount = clearValues.size();
    beginPassInfo.pClearValues = clearValues.data();
    
    
    RenderCommand::BeginRenderPass(&beginPassInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }
  void Renderer::BeginOverlayPass()
  {
    CANDY_PROFILE_FUNCTION();
    data.currentPassIndex = overlayPassIndex;
    
    std::array<VkClearValue, 2> clearValues{};
    
    
    clearValues[0].color = {data.clearColor.r, data.clearColor.g, data.clearColor.b, data.clearColor.a};
    clearValues[1].depthStencil = {1.0f, 0};

    Vector2u size = {data.target->swapChain->extent.width, data.target->swapChain->extent.height};
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = data.renderPasses[overlayPassIndex];
    beginPassInfo.framebuffer = GetCurrentFrame().viewportData.viewportFrameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    
    beginPassInfo.clearValueCount = clearValues.size();
    beginPassInfo.pClearValues = clearValues.data();
    
    
    RenderCommand::NextRenderPass(&beginPassInfo);
  }
  
  void Renderer::BeginSelectionPass()
  {
    CANDY_PROFILE_FUNCTION();
    data.currentPassIndex = selectionPassIndex;
    
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color.int32[0]=-1;
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {data.target->swapChain->extent.width, data.target->swapChain->extent.height};
    
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = data.renderPasses[selectionPassIndex];
    beginPassInfo.framebuffer = GetCurrentFrame().viewportData.selectionFrameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    
    beginPassInfo.clearValueCount = clearValues.size();
    beginPassInfo.pClearValues = clearValues.data();
    
    
    RenderCommand::NextRenderPass(&beginPassInfo);
    
    
    
    
  }
  void Renderer::BeginUIPass()
  {
    CANDY_PROFILE_FUNCTION();
    data.currentPassIndex = uiPassIndex;
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = {data.clearColor.r, data.clearColor.g, data.clearColor.b, data.clearColor.a};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {data.target->swapChain->extent.width, data.target->swapChain->extent.height};
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = data.renderPasses[uiPassIndex];
    beginPassInfo.framebuffer = data.target->swapChain->GetCurrentFrameBuffer();
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    
    beginPassInfo.clearValueCount = clearValues.size();
    beginPassInfo.pClearValues = clearValues.data();
    
    
    RenderCommand::NextRenderPass(&beginPassInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }

  
  void Renderer::BeginScene(const PerspectiveCamera& camera)
  {
    CANDY_PROFILE_FUNCTION();
    sceneData.viewMatrix = camera.GetViewMatrix();
    sceneData.projectionMatrix = camera.GetProjectionMatrix();
  }
  
  void Renderer::RenderScene(const SharedPtr<ECS::Scene>& scene)
  {
    scene->RenderScene3D();
    BeginOverlayPass();
    scene->RenderScene2D();
    Renderer::BeginSelectionPass();
    Renderer3D::RenderSelectionBuffer();
    Renderer2D::RenderSelectionBuffer();
    
    scene->ClearUpdateFlags();
  }
  void Renderer::EndScene()
  {
  
  }
  void Renderer::UpdateCameraData(const CameraBase& camera3D, const CameraBase& camera2D)
  {
    CANDY_PROFILE_FUNCTION();
    data.cameraData.viewMatrix = camera3D.GetViewMatrix();
    data.cameraData.projectionMatrix = camera3D.GetProjectionMatrix();
    data.cameraData.viewProjectionMatrix = data.cameraData.projectionMatrix * data.cameraData.viewMatrix;
    
    data.cameraData.viewMatrix2D = camera2D.GetViewMatrix();
    data.cameraData.projectionMatrix2D = camera2D.GetProjectionMatrix();
    data.cameraData.viewProjectionMatrix2D = data.cameraData.projectionMatrix2D * data.cameraData.viewMatrix2D;
    RenderCommand::SetUniform(0, sizeof(CameraData), &data.cameraData);
    
   
    size_t cameraTypeSize = sizeof(Matrix4)*3;
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = *GetCurrentFrame().uniformBuffer;
    bufferInfo.offset=0;
    bufferInfo.range = cameraTypeSize;
    
    builder.AddBufferWrite(0, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 0);
    
    VkDescriptorBufferInfo bufferInfo2{};
    bufferInfo2.buffer = *GetCurrentFrame().uniformBuffer;
    bufferInfo2.offset = cameraTypeSize;
    bufferInfo2.range = cameraTypeSize;
    
    builder.AddBufferWrite(1, &bufferInfo2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 0);
    
    
    
    VkDescriptorSet descriptorSet = GetCurrentFrame().GlobalDescriptor();
    builder.Write(descriptorSet);
    
  }
  
  
  void Renderer::EndViewportPass()
  {
  
  }
  
  VkRenderPass Renderer::GetCurrentPass()
  {
    return data.renderPasses[data.currentPassIndex];
  }
  uint8_t Renderer::GetCurrentPassIndex()
  {
    return data.currentPassIndex;
  }
  uint8_t Renderer::GetViewportPassIndex()
  {
    return viewportPassIndex;
  }
  uint8_t Renderer::GetOverlayPassIndex()
  {
    return overlayPassIndex;
  }
  uint8_t Renderer::GetSelectionPassIndex()
  {
    return selectionPassIndex;
  }
  uint8_t Renderer::GetUIPassIndex()
  {
    return uiPassIndex;
  }
  const RenderPass& Renderer::GetUIPass()
  {
    //return data.editorPasses[0];
    return data.renderPasses[uiPassIndex];
  }
  /*const CameraData& Renderer::GetCameraData()
  {
    return data.cameraData;
  }*/
  const RenderPass& Renderer::GetRenderPass(uint32_t index)
  {
    CANDY_CORE_ASSERT(index < data.renderPasses.GetTotalPassCount());
    //return data.renderPasses[index];
    return data.renderPasses[index];
  }
  VkRenderPass Renderer::GetRenderPassHandle(uint32_t index)
  {
    return data.renderPasses[index];
  }
  const RenderPass& Renderer::GetViewportPass()
  {
    return data.renderPasses[viewportPassIndex];
  }
  const RenderPass& Renderer::GetOverlayPass()
  {
    return data.renderPasses[overlayPassIndex];
  }
  const RenderPass& Renderer::GetSelectionPass()
  {
    return data.renderPasses[selectionPassIndex];
  }
  
  void Renderer::SetClearColor(const Color& value)
  {
    data.clearColor = value;
  }
  Color Renderer::GetClearColor()
  {
    return data.clearColor;
  }
  FrameResources& Renderer::GetCurrentFrame(){return data.target->GetCurrentFrame();}
  FrameResources& Renderer::GetFrame(uint32_t index){return data.target->GetFrame(index);}
  


  

}