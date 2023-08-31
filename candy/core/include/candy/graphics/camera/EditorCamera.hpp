#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/event/Events.hpp>
#include <candy/math/Quaternion.hpp>
#include "CameraBase.hpp"
#include "PerspectiveCameraController.hpp"
#include "OrthographicCameraController.hpp"
namespace Candy::Graphics
{
  struct EditorCameraSettings
  {
    float movementSpeed = 1.0f;
    float rollSpeed = 90.0f;
    float mouseSensitivity = 0.5f;
    float scrollSensitivity = 4.5f;
    Math::Vector2 panSensitivity = { 0.001f, 0.001f };
    bool canRoll = true;
    bool constrainPitch = true;
  };
  class EditorCamera
  {
  private:
    PerspectiveCamera perspective;
    OrthographicCamera orthographic;
    Math::Vector2 prevMousePos;
    EditorCameraSettings settings;
    
  private:
    bool OnMouseScroll(Events::MouseScrollEvent& event);
    bool OnWindowResized(Events::WindowResizeEvent& event);
    void MousePan(const Math::Vector2& mouseDelta, float velocity);
    void MouseRotate(const Math::Vector2& mouseDelta);
    
  public:
    EditorCamera(const Math::Vector3& pos, const Math::Vector2& viewportSize);
    
  public:
    void OnUpdate();
    void OnEvent(Events::Event& e);
    
  public:
    void SetViewportSize(float width, float height);
    void SetViewportSize(const Math::Vector2& value);
    
    
    [[nodiscard]] const CameraBase& GetCamera3D()const;
    [[nodiscard]] const CameraBase& GetCamera2D()const;
    [[nodiscard]] Math::Matrix4 GetViewMatrix3D()const;
    [[nodiscard]] Math::Matrix4 GetProjectionMatrix3D()const;
    [[nodiscard]] Math::Matrix4 GetViewMatrix2D()const;
    [[nodiscard]] Math::Matrix4 GetProjectionMatrix2D()const;

    
  
  
  
  };
}