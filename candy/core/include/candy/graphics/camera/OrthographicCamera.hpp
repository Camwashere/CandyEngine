#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/math/Vector.hpp>
namespace Candy::Graphics
{
  class OrthographicCamera
  {
  private:
    Math::Matrix4 projection;
    Math::Matrix4 view;
    Math::Matrix4 viewProjection;
    Math::Vector3 position;
    float rotation;
    
  private:
    void RecalculateViewMatrix();
    
  public:
    OrthographicCamera(float left, float right, float bottom, float top);
    
    void SetProjection(float left, float right, float bottom, float top);
    
    [[nodiscard]] const Math::Vector3& GetPosition()const;
    void SetPosition(const Math::Vector3& pos);
    
    [[nodiscard]] float GetRotation()const{return rotation;}
    
    void SetRotation(float rotation);
    
    [[nodiscard]] const Math::Matrix4& GetProjectionMatrix()const;
    [[nodiscard]] const Math::Matrix4& GetViewMatrix()const;
    [[nodiscard]] const Math::Matrix4& GetViewProjectionMatrix()const;
  };
}