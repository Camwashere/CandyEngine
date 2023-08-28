#pragma once
#include <candy/math/Matrix.hpp>
namespace Candy::Graphics
{
  class CameraBase
  {
  protected:
    Math::Matrix4 projectionMatrix;
    Math::Matrix4 viewMatrix;
    Math::Vector3 position;
    
  public:
    CameraBase()=default;
    explicit CameraBase(const Math::Vector3& pos);
    CameraBase(const Math::Vector3& pos, const Math::Matrix4& projection, const Math::Matrix4& view=Math::Matrix4::IDENTITY);
    CameraBase(const CameraBase& other)=default;
    
    
  public:
    void SetViewMatrix(const Math::Matrix4& view);
    void SetProjectionMatrix(const Math::Matrix4& projection);
    
    
    [[nodiscard]] const Math::Vector3& GetPosition()const;
    [[nodiscard]] const Math::Matrix4& GetViewMatrix()const;
    [[nodiscard]] const Math::Matrix4& GetProjectionMatrix()const;
    [[nodiscard]] Math::Matrix4 GetViewProjectionMatrix()const;
  };
}