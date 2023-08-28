#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>
#include <candy/event/Events.hpp>
#include <candy/graphics/camera/CameraController.hpp>
#include <candy/graphics/camera/EditorCamera.hpp>
#include <candy/graphics/camera/OrthographicCameraController.hpp>
#include <candy/ecs/Scene.hpp>
#include <candy/ecs/Entity.hpp>
namespace Candy
{
  class EditorLayer;
}
namespace Candy
{
  
  class Viewport
  {
  private:
    bool isFocused=false;
    bool isHovered=false;
    EditorLayer* parent;
    //ECS::Scene* activeScene;
    Graphics::OrthographicCameraController orthographicCameraController;
    Graphics::EditorCamera editorCamera;
    Math::Rectangle bounds;
    ECS::Entity hoveredEntity;
    Math::Vector2 size;
    int gizmoType=0;
    
    
  private:
    void OnOverlayRender();
  public:
    explicit Viewport(EditorLayer* parentLayer);
    
  public:
    void OnAttach();
    void OnUpdate();
    void OnEvent(Events::Event& event);
    void OnRenderUI();
    
    [[nodiscard]] bool IsHovered()const;
    [[nodiscard]] ECS::Entity GetHoveredEntity()const;
    
  private:
    friend class EditorLayer;
    
  };
}