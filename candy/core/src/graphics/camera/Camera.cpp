#include <candy/graphics/camera/Camera.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  Camera::Camera(const Vector3& pos, const Vector3& upValue, float yawValue, float pitchValue)
  : localFront(Math::Vector3(0.0f, 0.0f, -1.0f)), position(pos), localUp(upValue), pitch(pitchValue), yaw(yawValue), roll(ROLL), zoom(ZOOM)
  {
    SetScreenSizeToApplicationWindow();
    UpdateCameraVectors();
  }
  void Camera::SetScreenSize(float width, float height){screenSize.Set(width, height);}
  void Camera::SetNearClip(float value){nearClip = value;}
  void Camera::SetFarClip(float value){farClip = value;}
  void Camera::SetClipRange(float near, float far){nearClip = near; farClip = far;}
  void Camera::SetZoom(float value){zoom = value;}
  
  [[nodiscard]] const Math::Vector3& Camera::GetPosition()const{return position;}
  [[nodiscard]] float Camera::GetZoom()const{return zoom;}
  [[nodiscard]] float Camera::GetAspectRatio()const{return screenSize.x/screenSize.y;}
  void Camera::SetScreenSizeToApplicationWindow()
  {
    SetScreenSize((float)Application::GetMainWindowReference().GetWidth(), (float)Application::GetMainWindowReference().GetHeight());
  }
  
  void Camera::UpdateCameraVectors()
  {
    // calculate the new front vector
    Math::Vector3 frontVec;
    frontVec.x = Math::Cos(Math::ToRadians(yaw)) * Math::Cos(Math::ToRadians(pitch));
    frontVec.y = Math::Sin(Math::ToRadians(pitch));
    frontVec.z = Math::Sin(Math::ToRadians(yaw)) * Math::Cos(Math::ToRadians(pitch));
    localFront = Math::Vector3::Normalize(frontVec);
    // also re-calculate the right and up vector
    localRight = Math::Vector3::Normalize(Math::Vector3::Cross(localFront, Math::Vector3::up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    localUp    = Math::Vector3::Normalize(Math::Vector3::Cross(localRight, localFront));
  }
  
  Math::Matrix4 Camera::GetViewMatrix()const
  {
    return Matrix4::LookAt(position, position+localFront, localUp);
  }
  
  Math::Matrix4 Camera::GetProjectionMatrix()const
  {
    Matrix4 proj =  Matrix4::Perspective(Math::ToRadians(zoom), screenSize.x/screenSize.y, nearClip, farClip);
    proj[1,1] *= -1;
    return proj;
  }
  
  Math::Matrix4 Camera::GetViewProjectionMatrix()const
  {
    return GetProjectionMatrix() * GetViewMatrix();
  }
}
