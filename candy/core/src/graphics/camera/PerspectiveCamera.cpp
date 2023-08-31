#include <candy/graphics/camera/PerspectiveCamera.hpp>
#include <candy/event/Events.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  using namespace Events;
  PerspectiveCamera::PerspectiveCamera() : CameraBase(Vector3::zero), localFront(Math::Vector3(0.0f, 0.0f, 1.0f)), localUp(Vector3::up), pitch(PITCH), yaw(YAW), roll(ROLL), fov(FOV)
  {
    UpdateMatrices();
  }
  PerspectiveCamera::PerspectiveCamera(const Vector3& pos, const Vector3& upValue, float yawValue, float pitchValue)
  : CameraBase(pos), localFront(Math::Vector3(0.0f, 0.0f, 1.0f)), localUp(upValue), pitch(pitchValue), yaw(yawValue), roll(ROLL), fov(FOV)
  {
    UpdateMatrices();
  }
  
  void PerspectiveCamera::UpdateViewMatrix()
  {
    viewMatrix = Matrix4::LookAt(position, position+localFront, localUp);
  }
  void PerspectiveCamera::UpdateProjectionMatrix()
  {
    projectionMatrix = Matrix4::Perspective(Math::ToRadians(fov), GetAspectRatio(), nearClip, farClip);
    projectionMatrix[1,1] *= -1;
    
  }
  
  void PerspectiveCamera::UpdateMatrices()
  {
    UpdateProjectionMatrix();
    UpdateViewMatrix();
  }
  void PerspectiveCamera::UpdateCameraVectors()
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
    UpdateViewMatrix();
    
    
    
    // Calculate the new front vector
    /*Math::Vector3 front;
    front.x = Math::Cos(ToRadians(yaw)) * Math::Cos(ToRadians(pitch));
    front.y = Math::Sin(ToRadians(pitch));
    front.z = Math::Sin(ToRadians(yaw)) * Math::Cos(ToRadians(pitch));
    localFront = Math::Vector3::Normalize(front);
    
    // Create the rotation matrix for the roll
    Math::Matrix4 rollRotationMatrix = Math::Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(roll), localFront);
    
    // Rotate the front vector by the roll matrix
    localFront = rollRotationMatrix * localFront;
    localUp =  rollRotationMatrix * localUp;
    
    // Calculate the right and up vector using the world up vector
    localRight  = Math::Vector3::Normalize(Math::Vector3::Cross(localFront, localUp));
    localUp     = Math::Vector3::Normalize(Math::Vector3::Cross(localRight, localFront));*/
    
    //UpdateViewMatrix();
  }
  float PerspectiveCamera::GetFov()const{return fov;}
  float PerspectiveCamera::GetAspectRatio()const{return viewportSize.x/viewportSize.y;}
  
 
  
  
  
  Math::Vector3 PerspectiveCamera::GetLocalUp() const
  {
    return localUp;
  }
  
  Math::Vector3 PerspectiveCamera::GetLocalRight() const
  {
    return localRight;
  }
  
  Math::Vector3 PerspectiveCamera::GetLocalForward() const
  {
    return localFront;
  }
  
  float PerspectiveCamera::GetDistance() const
  {
    return distance;
  }
  void PerspectiveCamera::SetDistance(float value)
  {
    distance = value;
  }
  void PerspectiveCamera::SetViewportSize(float width, float height)
  {
    viewportSize.Set(width, height);
    UpdateProjectionMatrix();
  }
  void PerspectiveCamera::SetViewportSize(const Math::Vector2& value)
  {
    SetViewportSize(value.x, value.y);
  }
  
  void PerspectiveCamera::SetNearClip(float value){nearClip = value;}
  void PerspectiveCamera::SetFarClip(float value){farClip = value;}
  void PerspectiveCamera::SetClipRange(float near, float far){nearClip = near; farClip = far;}
  void PerspectiveCamera::SetFov(float value){fov = value;}
  
  
  
  
  float PerspectiveCamera::GetPitch() const
  {
    return pitch;
  }
  float PerspectiveCamera::GetYaw() const
  {
    return yaw;
  }
  float PerspectiveCamera::GetRoll()const
  {
    return roll;
  }
}