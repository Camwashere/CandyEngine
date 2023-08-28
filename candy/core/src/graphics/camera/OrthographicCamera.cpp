#include <candy/graphics/camera/OrthographicCamera.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  void OrthographicCamera::RecalculateViewMatrix()
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position) * Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(rotation), Vector3(0, 0, 1));
    viewMatrix = Matrix4::Inverse(transform);
    
  }
  
  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : CameraBase(Vector3::zero, Matrix4::Orthographic(left, right, bottom, top, 0.0f, 1.0f)), rotation(0.0f)
  {
    CANDY_PROFILE_FUNCTION();
    projectionMatrix[1,1] *= -1;
  }
  
  void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
  {
    CANDY_PROFILE_FUNCTION();
    projectionMatrix = Matrix4::Orthographic(left, right, bottom, top, 0.0f, 1.0f);
    projectionMatrix[1,1] *= -1;
  }
  
  void OrthographicCamera::SetPosition(const Math::Vector3& pos)
  {
    position = pos;
    RecalculateViewMatrix();
  }
  void OrthographicCamera::SetRotation(float rot)
  {
    rotation = rot;
    RecalculateViewMatrix();
  }
  
  float OrthographicCamera::GetRotation()const
  {
    return rotation;
  }
  
  
}