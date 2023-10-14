#include <candy/graphics/Renderer.hpp>
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
#include "CandyEngine.hpp"
#include <candy/graphics/vulkan/RenderPassConfig.hpp>
#include <candy/graphics/vulkan/RenderChainScheduler.hpp>
#include <CandyPch.hpp>
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
    
    RenderChainScheduler chains;
    
    RenderChainPassKey currentChainKey{0, 0};
    Color clearColor = Color::black;
  };
  
  static RendererData data;
  
  
  

  void Renderer::Init(VkSurfaceFormatKHR surfaceFormat)
  {
    CANDY_PROFILE_FUNCTION();
    Font::Init(CandyEngine::GetInternalConfigDirectory() / "font/atlasGeneratorSettings.yml", CandyEngine::GetInternalAssetsDirectory() / "fonts");
    SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    
    
    data.chains.AddPass("Viewport", "3D", RenderPassBuilder::FastBuild(surfaceFormat.format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    
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
    .AddDefaultDependency()
    .AddStandardClearValues();
    
    
    data.chains.AddPass("Viewport", "2D", builder.GetConfig());
    RenderPassConfig selectionConfig = RenderPassBuilder::FastBuild(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    selectionConfig.defaultClearValues.resize(2);
    selectionConfig.defaultClearValues[0].color.int32[0]=-1;
    selectionConfig.defaultClearValues[1].depthStencil = {1.0f, 0};
    data.chains.AddPass("Viewport", "Selection", RenderPassBuilder::FastBuild(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    
    data.chains.AddPass("Editor", "UI", RenderPassBuilder::FastBuild(surfaceFormat.format, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR));
  }
  

  void Renderer::SetTarget(GraphicsContext* target)
  {
    CANDY_PROFILE_FUNCTION();
    data.target = target;
  }
  bool Renderer::NextPass()
  {
    if (data.chains.NextPass())
    {
      RenderCommand::EndRenderPass();
      BeginPass(data.chains.GetCurrentRenderPass());
      return true;
    }
    return false;
  }
  void Renderer::BeginPass(RenderPass& renderPass)
  {
    RenderTarget* target = renderPass.GetCurrentTarget();
    CANDY_CORE_ASSERT(target != nullptr, "Render pass cannot begin with a null render target!");
    BeginPass(renderPass, target->frameBuffer);
  }
  void Renderer::BeginPass(RenderPass& renderPass, VkFramebuffer frameBuffer)
  {
    data.currentChainKey = data.chains.GetCurrentKey();
    Vector2u size = {data.target->swapChain->extent.width, data.target->swapChain->extent.height};
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = renderPass;
    beginPassInfo.framebuffer = frameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    
    beginPassInfo.clearValueCount = renderPass.GetClearValues().size();
    beginPassInfo.pClearValues = renderPass.GetClearValues().data();
    
    
    RenderCommand::BeginRenderPass(&beginPassInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
    
  }
  void Renderer:: BeginViewportChain()
  {
    CANDY_PROFILE_FUNCTION();
    RenderTarget& viewportTarget = data.target->viewportTarget;
    RenderTarget& selectionTarget = data.target->selectionTarget;
    data.chains[viewportChainIndex, viewportPassIndex].SetRenderTarget(viewportTarget);
    data.chains[viewportChainIndex, overlayPassIndex].SetRenderTarget(viewportTarget);
    data.chains[viewportChainIndex, selectionPassIndex].SetRenderTarget(selectionTarget);
    data.chains.Begin();
    BeginPass(data.chains.GetCurrentRenderPass());
    
  }
  void Renderer::BeginEditorChain()
  {
    CANDY_PROFILE_FUNCTION();
    bool success = data.chains.NextChain();
    CANDY_CORE_ASSERT(success, "Failed to begin editor chain");
    RenderCommand::EndRenderPass();
    VkFramebuffer framebuffer = data.target->swapChain->GetCurrentFrameBuffer();
    BeginPass(data.chains.GetCurrentRenderPass(), framebuffer);
  }
  
  void Renderer::EndChains()
  {
    data.chains.End();
  }
  void Renderer::BeginScene(const PerspectiveCamera& camera)
  {
    CANDY_PROFILE_FUNCTION();
    sceneData.viewMatrix = camera.GetViewMatrix();
    sceneData.projectionMatrix = camera.GetProjectionMatrix();
  }
  
  void Renderer::RenderScene(const SharedPtr<ECS::Scene>& scene)
  {
    do
    {
      RenderChainPassKey key = data.chains.GetCurrentKey();
      RenderScenePass(scene, key.passIndex);
    }
    while(NextPass());
    
    scene->ClearUpdateFlags();
  }
  
  void Renderer::RenderScenePass(const SharedPtr<ECS::Scene>& scene, uint8_t passIndex)
  {
    switch(passIndex)
    {
      case viewportPassIndex:
        scene->RenderScene3D();
        break;
      case overlayPassIndex:
        scene->RenderScene2D();
        break;
      case selectionPassIndex:
        Renderer3D::RenderSelectionBuffer();
        Renderer2D::RenderSelectionBuffer();
        break;
      default:
        CANDY_CORE_ASSERT(false, "Invalid pass index");
    }
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
    return data.chains.GetCurrentRenderPass();
  }
  uint8_t Renderer::GetCurrentPassIndex()
  {
    return data.chains.GetCurrentPassIndex();
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
    return data.chains[editorChainIndex, uiPassIndex];
  }

  const RenderPass& Renderer::GetRenderPass(uint32_t index)
  {
    return data.chains[viewportChainIndex, index];
  }
  VkRenderPass Renderer::GetRenderPassHandle(uint32_t index)
  {
    return data.chains[viewportChainIndex, index];
  }
  const RenderPass& Renderer::GetViewportPass()
  {
    return data.chains[viewportChainIndex, viewportPassIndex];
  }
  const RenderPass& Renderer::GetOverlayPass()
  {
    return data.chains[viewportChainIndex, overlayPassIndex];
  }
  const RenderPass& Renderer::GetSelectionPass()
  {
    return data.chains[viewportChainIndex, selectionPassIndex];
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