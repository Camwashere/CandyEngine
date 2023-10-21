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
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/vulkan/DeletionQueue.hpp>
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
    std::vector<RenderTarget> renderTargets;
    PixelBuffer* selectionPixelBuffer=nullptr;
    RenderChainScheduler chains;
    Math::Vector2u viewportImageSize;
    
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
    data.chains.AddPass("Viewport", "Gum", builder.GetConfig());
    
    RenderPassConfig selectionConfig = RenderPassBuilder::FastBuild(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    selectionConfig.defaultClearValues.resize(2);
    selectionConfig.defaultClearValues[0].color.int32[0]=-1;
    selectionConfig.defaultClearValues[1].depthStencil = {1.0f, 0};
    data.chains.AddPass("Viewport", "Selection", RenderPassBuilder::FastBuild(VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    
    
    
    
    data.chains.AddPass("Editor", "UI", RenderPassBuilder::FastBuild(surfaceFormat.format, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR));
    
    data.chains[0].SetActivePass("Selection", false);
    
    data.renderTargets.resize(2);
  }
  
  Math::Vector2u Renderer::GetViewportImageSize()
  {
    return data.viewportImageSize;
  }
  int Renderer::ReadViewportPixelData(int x, int y)
  {
    if (data.selectionPixelBuffer != nullptr)
    {
      if (data.chains[0].IsPassActive(selectionPassIndex))
      {
        return data.selectionPixelBuffer->ReadPixel(x, y);
      }
      
    }
    return -1;
  }
  void Renderer::CreateViewport(Math::Vector2u size)
  {
    data.viewportImageSize = size;
    VkFormat depthFormat = GraphicsContext::FindDepthFormat();
    RenderTarget& viewportTarget = GetViewportTarget();
    //RenderTarget& selectionTarget = GetSelectionTarget();
    
    viewportTarget.imageResources.resize(2);
    //selectionTarget.imageResources.resize(1);
    
    viewportTarget.imageResources[0].image.Create(size, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    viewportTarget.imageResources[0].imageView.Set(viewportTarget.imageResources[0].image);
    
    viewportTarget.imageResources[1].image.Create(Math::Vector2u(size.width, size.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    viewportTarget.imageResources[1].imageView.Set(viewportTarget.imageResources[1].image, VK_IMAGE_ASPECT_DEPTH_BIT);
    
    
    
    //selectionTarget.imageResources[0].image.Create(size, VK_FORMAT_R32_SINT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    //selectionTarget.imageResources[0].imageView.Set(selectionTarget.imageResources[0].image);
    
    viewportTarget.frameBuffer.Set(Renderer::GetViewportPass(), size, {viewportTarget.imageResources[0].imageView, viewportTarget.imageResources[1].imageView});
    //selectionTarget.frameBuffer.Set(Renderer::GetSelectionPass(), size, {selectionTarget.imageResources[0].imageView, viewportTarget.imageResources[1].imageView});
    
    RenderCommand::TransitionImageLayout(viewportTarget.imageResources[0].image, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    //RenderCommand::TransitionImageLayout(selectionTarget.imageResources[0].image, VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    RenderCommand::TransitionImageLayout(viewportTarget.imageResources[1].image, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    
    data.selectionPixelBuffer = new PixelBuffer(size);
  }
  
  void Renderer::CleanViewport()
  {
    CANDY_PROFILE_FUNCTION();
    RenderTarget& viewportTarget = GetViewportTarget();
    //RenderTarget& selectionTarget = GetSelectionTarget();
    
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[1].image);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[1].imageView);
    
    //Vulkan::DeletionQueue().Delete(&selectionTarget.frameBuffer);
    //Vulkan::DeletionQueue().Delete(&selectionTarget.imageResources[0].image);
    //Vulkan::DeletionQueue().Delete(&selectionTarget.imageResources[0].imageView);
    
    Vulkan::DeletionQueue().Delete(data.selectionPixelBuffer);
    delete data.selectionPixelBuffer;
    
    Vulkan::DeletionQueue().Delete(&viewportTarget.frameBuffer);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[0].image);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[0].imageView);
  }
  VkDescriptorSet Renderer::UpdateImGuiViewportTexture()
  {
    return ImGui_ImplVulkan_AddTexture(GetViewportTarget().imageResources[0].imageView.GetSampler(), GetViewportTarget().imageResources[0].imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }
  
  RenderTarget& Renderer::GetViewportTarget()
  {
    return data.renderTargets[0];
  }
  RenderTarget& Renderer::GetSelectionTarget()
  {
    return data.renderTargets[1];
  }
  void Renderer::SetTarget(GraphicsContext* target)
  {
    CANDY_PROFILE_FUNCTION();
    data.target = target;
  }

  void Renderer:: BeginViewportChain()
  {
    CANDY_PROFILE_FUNCTION();
    
    data.chains[viewportChainIndex, viewportPassIndex].SetRenderTarget(GetViewportTarget());
    data.chains[viewportChainIndex, overlayPassIndex].SetRenderTarget(GetViewportTarget());
    data.chains[viewportChainIndex, gumPassIndex].SetRenderTarget(GetViewportTarget());
    //data.chains[viewportChainIndex, selectionPassIndex].SetRenderTarget(GetSelectionTarget());
    
    data.chains.Begin({data.target->swapChain->extent.width, data.target->swapChain->extent.height});
    
  }
  void Renderer::BeginEditorChain()
  {
    CANDY_PROFILE_FUNCTION();
    data.chains.SetSwapChainTarget(data.target->swapChain->GetCurrentFrameBuffer());
    bool success = data.chains.NextChain();
    CANDY_CORE_ASSERT(success, "Failed to begin editor chain");
  }
  void Renderer::BeginGumPass()
  {
    bool beganGum = data.chains.NextPass();
    CANDY_CORE_ASSERT(beganGum, "Failed to begin gum pass");
  }
  void Renderer::EndGumPass()
  {
    CANDY_PROFILE_FUNCTION();
    //CANDY_CORE_ASSERT(data.chains.NextPass());
    
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
      if (!RenderScenePass(scene, key.passIndex))
      {
        break;
      }
    }
    while(data.chains.NextPass());
    
    scene->ClearUpdateFlags();
  }
  
  bool Renderer::RenderScenePass(const SharedPtr<ECS::Scene>& scene, uint8_t passIndex)
  {
    switch(passIndex)
    {
      case viewportPassIndex:
        scene->RenderScene3D();
        return true;
        break;
      case overlayPassIndex:
        scene->RenderScene2D();
        return false;
        break;
      case selectionPassIndex:
        Renderer3D::RenderSelectionBuffer();
        Renderer2D::RenderSelectionBuffer();
        return false;
        break;
      default:
        CANDY_CORE_ASSERT(false, "Invalid pass index");
        return false;
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
  uint8_t Renderer::GetGumPassIndex()
  {
    return gumPassIndex;
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