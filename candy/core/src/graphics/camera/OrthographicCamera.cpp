#include <candy/graphics/camera/OrthographicCamera.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  void OrthographicCamera::UpdateMatrices()
  {
    UpdateViewMatrix();
    UpdateProjectionMatrix();
  }
  void OrthographicCamera::UpdateViewMatrix()
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position) * Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(rotation), Vector3(0, 0, 1));
    viewMatrix = Matrix4::Inverse(transform);
    
  }
  
  void OrthographicCamera::UpdateProjectionMatrix()
  {
    CANDY_PROFILE_FUNCTION();
    float aspectRatio = GetAspectRatio();
    SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    
  }
  OrthographicCamera::OrthographicCamera(const Math::Vector2& viewSize, float zoom, float rot) : CameraBase(Math::Vector3::zero), viewportSize(viewSize), zoomLevel(zoom), rotation(rot)
  {
    CANDY_PROFILE_FUNCTION();
    UpdateMatrices();
  }
  
  void OrthographicCamera::SetViewportSize(float width, float height)
  {
    CANDY_PROFILE_FUNCTION();
    viewportSize.Set(width, height);
    UpdateProjectionMatrix();
  }
  void OrthographicCamera::SetViewportSize(const Math::Vector2& value)
  {
    SetViewportSize(value.x, value.y);
  }
  void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
  {
    CANDY_PROFILE_FUNCTION();
    projectionMatrix = Matrix4::Orthographic(left, right, bottom, top, 0.0f, 1.0f);
    projectionMatrix[1,1] *= -1;
  }
  
  void OrthographicCamera::SetZoomLevel(float value)
  {
    zoomLevel = value;
    UpdateProjectionMatrix();
  }
  
  void OrthographicCamera::SetPosition(const Math::Vector3& pos)
  {
    position = pos;
    UpdateViewMatrix();
  }
  void OrthographicCamera::SetRotation(float rot)
  {
    rotation = rot;
    UpdateViewMatrix();
  }
  
  float OrthographicCamera::GetRotation()const
  {
    return rotation;
  }
  float OrthographicCamera::GetAspectRatio()const
  {
    return viewportSize.x / viewportSize.y;
  }
  
  
}