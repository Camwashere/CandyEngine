#include <candy/graphics/camera/CameraBase.hpp>

namespace Candy::Graphics
{
  
  CameraBase::CameraBase(const Math::Vector3& pos) : position(pos)
  {
  
  }
  
  CameraBase::CameraBase(const Math::Vector3& pos, const Math::Matrix4& projection, const Math::Matrix4& view) : position(pos), projectionMatrix(projection), viewMatrix(view)
  {
  
  }
  
  void CameraBase::SetViewMatrix(const Math::Matrix4& view)
  {
    viewMatrix = view;
  }
  void CameraBase::SetProjectionMatrix(const Math::Matrix4& projection)
  {
    projectionMatrix = projection;
  }
  /*void CameraBase::SetPosition(const Math::Vector3& pos)
  {
    position = pos;
  }*/
  
  
  const Math::Vector3& CameraBase::GetPosition()const
  {
    return position;
  }
  const Math::Matrix4& CameraBase::GetViewMatrix()const
  {
    return viewMatrix;
  }
  const Math::Matrix4& CameraBase::GetProjectionMatrix()const
  {
    return projectionMatrix;
  }
  
  Math::Matrix4 CameraBase::GetViewProjectionMatrix()const
  {
    return projectionMatrix * viewMatrix;
  }
  
  
}