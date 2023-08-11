#include <candy/graphics/camera/OrthographicCamera.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  void OrthographicCamera::RecalculateViewMatrix()
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position) * Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(rotation), Vector3(0, 0, 1));
    view = Matrix4::Inverse(transform);
    viewProjection = projection * view;
  }
  
  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : projection(Matrix4::Orthographic(left, right, bottom, top, -1.0f, 1.0f)), view(1.0f), rotation(0.0f)
  {
    CANDY_PROFILE_FUNCTION();
    
    viewProjection = projection * view;
  }
  
  void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
  {
    CANDY_PROFILE_FUNCTION();
    
    projection = Matrix4::Orthographic(left, right, bottom, top, -1.0f, 1.0f);
    viewProjection = projection * view;
  }
  
  const Math::Vector3 &OrthographicCamera::GetPosition() const
  {
    return position;
  }
  
  void OrthographicCamera::SetPosition(const Math::Vector3 &pos)
  {
    position = pos;
  }
  
  void OrthographicCamera::SetRotation(float rot)
  {
    rotation = rot;
  }
  
  const Math::Matrix4 &OrthographicCamera::GetProjectionMatrix() const
  {
    return projection;
  }
  
  const Math::Matrix4 &OrthographicCamera::GetViewMatrix() const
  {
    return view;
  }
  
  const Math::Matrix4 &OrthographicCamera::GetViewProjectionMatrix() const
  {
    return viewProjection;
  }
}