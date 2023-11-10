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
    Math::Vector2 viewportSize;
    float zoomLevel=1.0f;
    
  private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
    void UpdateMatrices();
    void SetProjection(float left, float right, float bottom, float top);
    
  public:
    OrthographicCamera();
    explicit OrthographicCamera(const Math::Vector2& viewportSize, float zoomLevel=1.0f, float rotation = 0.0f);
    
  public:
    void SetZoomLevel(float value);
    void SetViewportSize(float width, float height);
    void SetViewportSize(const Math::Vector2& value);
    
    void SetPosition(const Math::Vector3& pos);
    void SetRotation(float rotation);
    [[nodiscard]] Math::Vector2 GetViewportSize()const;
    [[nodiscard]] float GetRotation()const;
    [[nodiscard]] float GetAspectRatio()const;
    
  private:
    friend class OrthographicCameraController;
  };
}