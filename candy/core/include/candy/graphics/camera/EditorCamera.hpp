#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/event/Events.hpp>
#include <candy/math/Quaternion.hpp>
namespace Candy::Graphics
{
  class EditorCamera
  {
  private:
    static constexpr float YAW=-90.0f;
    static constexpr float PITCH       =  0.0f;
    static constexpr float ROLL        =  0.0f;
    static constexpr float FOV        =  45.0f;
    static constexpr float MOVEMENT_SPEED = 1.0f;
    static constexpr float ROLL_SPEED = 90.0f;
    static constexpr float MOUSE_SENSITIVITY = 0.5f;
    static constexpr float SCROLL_SENSITIVITY = 4.5f;
    
  private:
    Math::Vector3 position;
    Math::Vector3 localFront;
    Math::Vector3 localUp;
    Math::Vector3 localRight;
    
    // Euler Angles
    
    float pitch, yaw, roll;
    
    // Projection attributes
    float fov;
    Math::Vector2 viewportSize;
    float nearClip=0.1f, farClip=100.0f;
    
    Math::Matrix4 viewMatrix;
    Math::Matrix4 projectionMatrix;
    Math::Matrix4 viewMatrix2D;
    Math::Matrix4 orthographicProjectionMatrix;
    
    float movementSpeed;
    float rollSpeed;
    float mouseSensitivity;
    float scrollSensitivity;
    Math::Vector2 panSensitivity;
    float distance = 10.0f;
    Math::Vector3 focalPoint = { 0.0f, 0.0f, 0.0f };
    Math::Vector2 prevMousePos;
    Math::Vector2 panSpeed = { 0.001f, 0.001f };
    
    bool canRoll=true;
    
  
  private:
    void UpdateCameraVectors();
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
    
    
    Math::Vector2 CalculatePanSpeed() const;
    float GetRollSpeed() const;
    float CalculateZoomSpeed() const;
    
    bool OnMouseScroll(Events::MouseScrollEvent& event);
    bool OnWindowResized(Events::WindowResizeEvent& event);
    void MousePan(const Math::Vector2& mouseDelta, float velocity);
    void MouseRotate(const Math::Vector2& mouseDelta, bool constrainPitch);
    
  public:
    EditorCamera() = default;
    explicit EditorCamera(const Math::Vector3& pos, const Math::Vector3& upValue=Math::Vector3::up, float yawValue=YAW, float pitchValue=PITCH);
    void SetNearClip(float value);
    void SetFarClip(float value);
    void SetClipRange(float near, float far);
    void SetFov(float value);
    
    [[nodiscard]] float GetFov()const;
    [[nodiscard]] float GetAspectRatio()const;
  
  
    void OnUpdate();
    void OnEvent(Events::Event& e);
    
    [[nodiscard]] float GetDistance() const;
    void SetDistance(float value);
    void SetViewportSize(float width, float height);
    void SetViewportSize(const Math::Vector2& value);
    [[nodiscard]] const Math::Matrix4& GetViewMatrix() const;
    [[nodiscard]] const Math::Matrix4& GetViewMatrix2D() const;
    [[nodiscard]] const Math::Matrix4& GetProjectionMatrix()const;
    [[nodiscard]] const Math::Matrix4& GetOrthographicProjectionMatrix()const;
    [[nodiscard]] Math::Matrix4 GetViewProjectionMatrix() const;
    [[nodiscard]] Math::Matrix4 GetViewProjectionMatrix2D()const;
    
    [[nodiscard]] Math::Vector3 GetLocalUp() const;
    [[nodiscard]] Math::Vector3 GetLocalRight() const;
    [[nodiscard]] Math::Vector3 GetLocalForward() const;
    [[nodiscard]] const Math::Vector3& GetPosition() const;
    
    [[nodiscard]] float GetPitch() const;
    [[nodiscard]] float GetYaw() const;
    [[nodiscard]] float GetRoll()const;
    
  
  
  
  };
}