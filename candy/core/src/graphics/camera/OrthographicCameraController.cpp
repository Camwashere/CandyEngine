#include <candy/graphics/camera/OrthographicCameraController.hpp>
#include <CandyPch.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Events;
  OrthographicCameraController::OrthographicCameraController(const Math::Vector2& viewSize, bool move, bool zoom, bool rot)
  : camera(viewSize), canMove(move), canZoom(zoom), canRotate(rot)
  {
    
  }
  
  void OrthographicCameraController::OnUpdate()
  {
    CANDY_PROFILE_FUNCTION();
    float ts = Application::DeltaTime();
    if (canMove)
    {
      if (Input::IsKeyPressed(Key::A))
      {
        cameraPosition.x -= Math::Cos(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y -= Math::Sin(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
      }
      else if (Input::IsKeyPressed(Key::D))
      {
        cameraPosition.x += Math::Cos(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y += Math::Sin(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
      }
      
      if (Input::IsKeyPressed(Key::W))
      {
        cameraPosition.x += -Math::Sin(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y += Math::Cos(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
      }
      else if (Input::IsKeyPressed(Key::S))
      {
        cameraPosition.x -= -Math::Sin(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y -= Math::Cos(Math::ToRadians(cameraRotation)) * cameraTranslationSpeed * ts;
      }
    }
    
    
    if (canRotate)
    {
      if (Input::IsKeyPressed(Key::Q))
        cameraRotation += cameraRotationSpeed * ts;
      if (Input::IsKeyPressed(Key::E))
        cameraRotation -= cameraRotationSpeed * ts;
      
      if (cameraRotation > 180.0f)
        cameraRotation -= 360.0f;
      else if (cameraRotation <= -180.0f)
        cameraRotation += 360.0f;
      
      camera.SetRotation(cameraRotation);
    }
    
    camera.SetPosition(cameraPosition);
    
    cameraTranslationSpeed = camera.zoomLevel;
  }
  
  void OrthographicCameraController::OnEvent(Event& e)
  {
    CANDY_PROFILE_FUNCTION();
    
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScroll));
    dispatcher.Dispatch<WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResize));
    dispatcher.Dispatch<FrameBufferResizeEvent>(CANDY_BIND_EVENT_FUNCTION(OrthographicCameraController::OnFrameBufferResize));
  }
  
  void OrthographicCameraController::OnResize(float width, float height)
  {
    //aspectRatio = width / height;
    //camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    camera.SetViewportSize(width, height);
  }
  
  bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
  {
    CANDY_PROFILE_FUNCTION();
    if (canZoom)
    {
      camera.zoomLevel -= e.GetOffsetY() * 0.25f;
      camera.zoomLevel = Math::Max(camera.zoomLevel, 0.25f);
      camera.SetZoomLevel(camera.zoomLevel);
      //camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }
    
    return false;
  }
  
  bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
  {
    CANDY_PROFILE_FUNCTION();
    
    OnResize((float)e.GetWidth(), (float)e.GetHeight());
    return false;
  }
  bool OrthographicCameraController::OnFrameBufferResize(Events::FrameBufferResizeEvent& e)
  {
    CANDY_PROFILE_FUNCTION();
    OnResize((float)e.GetWidth(), (float)e.GetHeight());
    return false;
  }
  void OrthographicCameraController::EnableZoom(bool enable)
  {
    canZoom = enable;
  }
  void OrthographicCameraController::EnableRotation(bool enable)
  {
    canRotate = enable;
  }
  bool OrthographicCameraController::CanZoom()const
  {
    return canZoom;
  }
  bool OrthographicCameraController::CanRotate()const
  {
    return canRotate;
  }
  OrthographicCamera& OrthographicCameraController::GetCamera() { return camera; }
  const OrthographicCamera& OrthographicCameraController::GetCamera() const { return camera; }
  
}