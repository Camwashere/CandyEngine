#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
namespace Candy::Graphics
{
  class Camera
  {
  private:
    static constexpr float YAW=-90.0f;
    static constexpr float PITCH       =  0.0f;
    static constexpr float ROLL        =  0.0f;
    static constexpr float ZOOM        =  45.0f;
  private:
    Math::Vector3 position;
    Math::Vector3 localFront;
    Math::Vector3 localUp;
    Math::Vector3 localRight;
    
    // Euler Angles
    
    float pitch, yaw, roll;
    
    // Projection attributes
    float zoom;
    Math::Vector2 screenSize;
    float nearClip=0.1f, farClip=100.0f;
    
    Math::Matrix4 viewMatrix;
    Math::Matrix4 projectionMatrix;
  
  private:
    void UpdateCameraVectors();
    void SetScreenSizeToApplicationWindow();
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
  
  
  public:
    explicit Camera(const Math::Vector3& pos, const Math::Vector3& upValue=Math::Vector3::up, float yawValue=YAW, float pitchValue=PITCH);
  
  public:
    void SetScreenSize(float width, float height);
    void SetNearClip(float value);
    void SetFarClip(float value);
    void SetClipRange(float near, float far);
    void SetZoom(float value);
    
    [[nodiscard]] const Math::Vector3& GetPosition()const;
    [[nodiscard]] float GetZoom()const;
    [[nodiscard]] float GetAspectRatio()const;
  
  public:
    [[nodiscard]] Math::Matrix4 GetViewMatrix()const;
    [[nodiscard]] Math::Matrix4 GetProjectionMatrix()const;
    [[nodiscard]] Math::Matrix4 GetViewProjectionMatrix()const;
  
  private:
    friend class CameraController;
  };
}