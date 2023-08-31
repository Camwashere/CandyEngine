#pragma once
#include "PerspectiveCamera.hpp"
#include <candy/event/Events.hpp>
namespace Candy::Graphics
{
  class CameraController
  {
  private:
    static constexpr float MOVEMENT_SPEED = 1.0f;
    static constexpr float MOUSE_SENSITIVITY = 0.5f;
    static constexpr float SCROLL_SENSITIVITY = 4.5f;
  private:
    PerspectiveCamera* camera;
    
    Math::Vector2 prevMousePos;
    
    float movementSpeed;
    float rotationSpeed=180.0f;
    float mouseSensitivity;
    float scrollSensitivity;
    
    bool canRotate=true;
  
  private:
    bool OnMouseScroll(Events::MouseScrollEvent& event);
    bool OnWindowResized(Events::WindowResizeEvent& event);
    Math::Vector2 PanSpeed();
    void MousePan(const Math::Vector2& mouseDelta, float velocity);
    void MouseRotate(const Math::Vector2& mouseDelta, bool constrainPitch);
  
  public:
    CameraController();
    explicit CameraController(PerspectiveCamera* camera);
    ~CameraController();
  
  public:
    void OnUpdate();
    void OnEvent(Events::Event& event);
    void OnResize(float width, float height);
    void LockRotation();
    void UnlockRotation();
    [[nodiscard]] bool CanRotate()const;
    void SetRotationEnabled(bool value);
    void SetCamera(PerspectiveCamera* cameraObject);
    PerspectiveCamera& GetCamera();
    [[nodiscard]] const PerspectiveCamera& GetCamera()const;
    
    [[nodiscard]] bool HasCamera()const;
    [[nodiscard]] bool NeedsCamera()const;
    
    
  };
}