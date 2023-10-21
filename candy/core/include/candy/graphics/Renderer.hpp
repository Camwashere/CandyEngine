#pragma once
#include <cstdint>
#include <candy/graphics/Color.hpp>
#include <candy/graphics/FrameResources.hpp>

namespace Candy::Math
{
  class Matrix4;
}

namespace Candy::ECS
{
  class Scene;
}

struct VkSurfaceFormatKHR;
namespace Candy::Graphics
{
  
  class PerspectiveCamera;
  class GraphicsContext;
  class Shader;
  class Mesh;
  class VertexArray;
  class CameraBase;
  class RenderPass;
  
  class Renderer
  {

  public:
    static constexpr uint8_t viewportChainIndex=0;
    
    static constexpr uint8_t viewportPassIndex=0;
    static constexpr uint8_t overlayPassIndex=1;
    static constexpr uint8_t gumPassIndex=2;
    static constexpr uint8_t selectionPassIndex=3;
    
    static constexpr uint8_t editorChainIndex=1;
    static constexpr uint8_t uiPassIndex=0;
    
    static void BeginScene(const PerspectiveCamera& camera);
    static void RenderScene(const SharedPtr<ECS::Scene>& scene);
    static bool RenderScenePass(const SharedPtr<ECS::Scene>& scene, uint8_t passIndex);
    static void EndScene();
    static void Init(VkSurfaceFormatKHR surfaceFormat);
    
    static VkDescriptorSet UpdateImGuiViewportTexture();
    static void CreateViewport(Math::Vector2u size);
    static Math::Vector2u GetViewportImageSize();
    static void CleanViewport();
    static RenderTarget& GetViewportTarget();
    static RenderTarget& GetSelectionTarget();
    static int ReadViewportPixelData(int x, int y);

    static void SetTarget(GraphicsContext* target);
    static void BeginViewportChain();
  
    static void BeginEditorChain();
    static void BeginGumPass();
    static void EndGumPass();
    static void EndChains();
    
   
    
    static void UpdateCameraData(const CameraBase& camera3D, const CameraBase& camera2D);
    static FrameResources& GetCurrentFrame();
    static FrameResources& GetFrame(uint32_t index);
    static VkRenderPass GetCurrentPass();
    static uint8_t GetCurrentPassIndex();
    static uint8_t GetViewportPassIndex();
    static uint8_t GetOverlayPassIndex();
    static uint8_t GetGumPassIndex();
    static uint8_t GetSelectionPassIndex();
    static uint8_t GetUIPassIndex();
    static const RenderPass& GetRenderPass(uint32_t index);
    static VkRenderPass GetRenderPassHandle(uint32_t index);
    static const RenderPass& GetViewportPass();
    static const RenderPass& GetOverlayPass();
    static const RenderPass& GetSelectionPass();
    static const RenderPass& GetUIPass();
    
    
    
    static void SetClearColor(const Color& value);
    static Color GetClearColor();
   
    
    
  private:
    friend class RenderCommand;
    friend class Vulkan;
  };
}