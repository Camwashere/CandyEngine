#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>
#include <candy/event/Events.hpp>
#include <candy/graphics/camera/CameraController.hpp>
#include <candy/ecs/Scene.hpp>
#include <candy/ecs/Entity.hpp>
namespace Candy
{
  class Viewport
  {
  private:
    bool isFocused=false;
    bool isHovered=false;
    
    ECS::Scene* activeScene;
    Graphics::CameraController cameraController;
    Math::Rectangle bounds;
    ECS::Entity hoveredEntity;
    Math::Vector2 size;
    
  private:
    void OnOverlayRender();
  public:
    Viewport(ECS::Scene* scene);
    
  public:
    void OnAttach();
    void OnUpdate();
    void OnEvent(Events::Event& event);
    void OnRenderUI();
    
    bool IsHovered()const;
    ECS::Entity GetHoveredEntity()const;
    
  private:
    friend class EditorLayer;
    
  };
}