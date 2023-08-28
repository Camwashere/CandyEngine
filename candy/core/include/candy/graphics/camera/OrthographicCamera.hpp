#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/math/Vector.hpp>
#include "CameraBase.hpp"
namespace Candy::Graphics
{
  class OrthographicCamera : public CameraBase
  {
  private:
    float rotation;
    
  private:
    void RecalculateViewMatrix();
    
  public:
    OrthographicCamera(float left, float right, float bottom, float top);
    
  public:
    void SetProjection(float left, float right, float bottom, float top);
    void SetPosition(const Math::Vector3& pos);
    void SetRotation(float rotation);
    [[nodiscard]] float GetRotation()const;
  };
}