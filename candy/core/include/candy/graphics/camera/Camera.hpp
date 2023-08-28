#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include "CameraBase.hpp"
namespace Candy::Graphics
{
  class Camera : public CameraBase
  {
  private:
    static constexpr float YAW=-90.0f;
    static constexpr float PITCH       =  0.0f;
    static constexpr float ROLL        =  0.0f;
    static constexpr float ZOOM        =  45.0f;
  private:
   
    Math::Vector3 localFront;
    Math::Vector3 localUp;
    Math::Vector3 localRight;
    
    // Euler Angles
    
    float pitch, yaw, roll;
    
    // Projection attributes
    float zoom;
    Math::Vector2 screenSize;
    float nearClip=0.1f, farClip=100.0f;
    
    
  
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
    
    [[nodiscard]] float GetZoom()const;
    [[nodiscard]] float GetAspectRatio()const;
  

  
  private:
    friend class CameraController;
  };
}