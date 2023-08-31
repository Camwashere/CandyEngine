#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include "CameraBase.hpp"
namespace Candy::Graphics
{
  class PerspectiveCamera : public CameraBase
  {
  private:
    static constexpr float YAW=-90.0f;
    static constexpr float PITCH       =  0.0f;
    static constexpr float ROLL        =  0.0f;
    static constexpr float FOV        =  45.0f;
    
  
  private:
    Math::Vector3 localFront;
    Math::Vector3 localUp;
    Math::Vector3 localRight;
    
    // Euler Angles
    
    float pitch, yaw, roll;
    
    // Projection attributes
    float fov;
    Math::Vector2 viewportSize;
    float nearClip=0.1f, farClip=100.0f;
    
    
    float distance = 10.0f;
    Math::Vector3 focalPoint = { 0.0f, 0.0f, 0.0f };
    
  private:
    void UpdateCameraVectors();
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
    void UpdateMatrices();
    
  
  public:
    PerspectiveCamera();
    explicit PerspectiveCamera(const Math::Vector3& pos, const Math::Vector3& upValue=Math::Vector3::up, float yawValue=YAW, float pitchValue=PITCH);
    void SetNearClip(float value);
    void SetFarClip(float value);
    void SetClipRange(float near, float far);
    void SetFov(float value);
    
    [[nodiscard]] float GetFov()const;
    [[nodiscard]] float GetAspectRatio()const;
    
    
    
    [[nodiscard]] float GetDistance() const;
    void SetDistance(float value);
    void SetViewportSize(float width, float height);
    void SetViewportSize(const Math::Vector2& value);
    
    
    [[nodiscard]] Math::Vector3 GetLocalUp() const;
    [[nodiscard]] Math::Vector3 GetLocalRight() const;
    [[nodiscard]] Math::Vector3 GetLocalForward() const;
    
    
    [[nodiscard]] float GetPitch() const;
    [[nodiscard]] float GetYaw() const;
    [[nodiscard]] float GetRoll()const;
  

  
  private:
    friend class CameraController;
    friend class PerspectiveCameraController;
    friend class EditorCamera;
  };
}