#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/event/Events.hpp>
#include <candy/math/Quaternion.hpp>
#include "PerspectiveCamera.hpp"
namespace Candy::Graphics
{
  class PerspectiveCameraController
  {
  private:
    static constexpr float MOVEMENT_SPEED = 1.0f;
    static constexpr float ROLL_SPEED = 90.0f;
    static constexpr float MOUSE_SENSITIVITY = 0.5f;
    static constexpr float SCROLL_SENSITIVITY = 4.5f;
    
  private:
    PerspectiveCamera camera;
    float movementSpeed;
    float rollSpeed;
    float mouseSensitivity;
    float scrollSensitivity;
    Math::Vector2 panSensitivity;
    Math::Vector2 prevMousePos;
    Math::Vector2 panSpeed = { 0.001f, 0.001f };
    
    bool canRoll=true;
    bool constrainPitch=true;
    
  private:
    bool OnMouseScroll(Events::MouseScrollEvent& event);
    bool OnWindowResized(Events::WindowResizeEvent& event);
    void MousePan(const Math::Vector2& mouseDelta, float velocity);
    void MouseRotate(const Math::Vector2& mouseDelta);
    
  public:
    explicit PerspectiveCameraController(const Math::Vector3& pos);
    
  public:
    void OnUpdate();
    void OnEvent(Events::Event& e);
    
  public:
    void SetMovementSpeed(float value);
    void SetRollSpeed(float value);
    void SetMouseSensitivity(float value);
    void SetScrollSensitivity(float value);
    void SetPanSensitivity(const Math::Vector2& value);
    void SetPanSensitivity(float x, float y);
    void SetCanRoll(bool value);
    void SetConstrainPitch(bool value);
    
    PerspectiveCamera& GetCamera();
    [[nodiscard]] const PerspectiveCamera& GetCamera()const;
  };
}