#pragma once
#include "OrthographicCamera.hpp"
#include <candy/event/Events.hpp>
namespace Candy::Graphics
{
  class OrthographicCameraController
  {
  
  private:
    float aspectRatio;
    float zoomLevel = 1.0f;
    OrthographicCamera camera;
    
    bool canRotate;
    bool canZoom;
    
    Math::Vector3 cameraPosition = { 0.0f, 0.0f, 0.0f };
    float cameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
    float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;
  
  private:
    bool OnMouseScroll(Events::MouseScrollEvent& e);
    bool OnWindowResize(Events::WindowResizeEvent& e);
    bool OnFrameBufferResize(Events::FrameBufferResizeEvent& e);
    
  public:
    explicit OrthographicCameraController(float aspectRatio, bool canZoom=false, bool canRotate = false);
    
  public:
    void OnUpdate();
    void OnEvent(Events::Event& e);
    
    void OnResize(float width, float height);
    
    void EnableZoom(bool enable);
    void EnableRotation(bool enable);
    [[nodiscard]] bool CanZoom()const;
    [[nodiscard]] bool CanRotate()const;
    OrthographicCamera& GetCamera();
    [[nodiscard]] const OrthographicCamera& GetCamera() const;
    
    [[nodiscard]] float GetZoomLevel() const;
    void SetZoomLevel(float level);
  
  };
  
}