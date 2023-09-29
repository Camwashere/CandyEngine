#pragma once
#include "candy/graphics/shader/Shader.hpp"
#include "VertexArray.hpp"
#include "vulkan/RenderPass.hpp"
#include "GraphicsContext.hpp"
#include "vulkan/pipeline/Pipeline.hpp"
#include <deque>
#include <ranges>
#include "UniformBuffer.hpp"
#include "candy/graphics/texture/Texture.hpp"
#include "vulkan/ImageView.hpp"
#include "candy/graphics/material/Material.hpp"
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include "candy/graphics/camera/PerspectiveCamera.hpp"
#include <candy/graphics/camera/EditorCamera.hpp>
#include "model/Mesh.hpp"
#include <candy/math/Matrix.hpp>
#include <candy/ui/Gizmo.hpp>

namespace Candy::Graphics
{
  struct CameraData
  {
    Math::Matrix4 viewMatrix{};
    Math::Matrix4 projectionMatrix{};
    Math::Matrix4 viewProjectionMatrix{};
    
    Math::Matrix4 viewMatrix2D{};
    Math::Matrix4 projectionMatrix2D{};
    Math::Matrix4 viewProjectionMatrix2D{};
  };
  
  class Renderer
  {
  private:
    static Renderer* instance;
    
  private:

    GraphicsContext* target;
    CameraData cameraData;
    std::array<UniquePtr<RenderPass>, 4> renderPasses{};
    uint8_t currentPassIndex=0;
    Color clearColor = Color::black;
    Gizmo gizmo;
    
  
  private:
    Renderer();
    
    
    
    
  public:
    static constexpr uint8_t viewportPassIndex=0;
    static constexpr uint8_t overlayPassIndex=1;
    static constexpr uint8_t selectionPassIndex=2;
    static constexpr uint8_t uiPassIndex=3;
    //static constexpr uint8_t selectionPassIndex=2;
    static void BeginScene(const PerspectiveCamera& camera);
    static void EndScene();
    static void Start();
    static void Init();
    static void SubmitMesh(const Mesh& mesh, const Math::Matrix4& transform);
    static void Submit(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertexArray, const Math::Matrix4& transform=Math::Matrix4::IDENTITY);
    static void SetTarget(GraphicsContext* target);
    static void BeginViewportPass();
    static void BeginSelectionPass();
    static void BeginOverlayPass();
    static void BeginUIPass();
    static void EndViewportPass();
    static void EndPass();
    
    static void UpdateCameraData(const CameraBase& camera3D, const CameraBase& camera2D);
    static FrameData& GetCurrentFrame();
    static FrameData& GetFrame(uint32_t index);
    static RenderPass& GetCurrentPass();
    static uint8_t GetCurrentPassIndex();
    static uint8_t GetViewportPassIndex();
    static uint8_t GetOverlayPassIndex();
    static uint8_t GetSelectionPassIndex();
    static uint8_t GetUIPassIndex();
    static RenderPass& GetRenderPass(uint8_t index);
    static RenderPass& GetViewportPass();
    static RenderPass& GetOverlayPass();
    
    static RenderPass& GetSelectionPass();
    static RenderPass& GetUIPass();
    static const CameraData& GetCameraData();
    
    static Gizmo& GetGizmo();
    
    static void SetClearColor(const Color& value);
    static Color GetClearColor();
   
    
    
  private:
    friend class RenderCommand;
    friend class Vulkan;
  };
}