#include <candy/graphics/camera/EditorCamera.hpp>
#include <candy/event/Events.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  using namespace Events;
  EditorCamera::EditorCamera(const Math::Vector3& pos, const Math::Vector2& viewportSize) : perspective(pos), orthographic(viewportSize)
  {
    prevMousePos = viewportSize/2.0f;
  }
  
  
  
  void EditorCamera::OnUpdate()
  {
    float deltaTime = Application::DeltaTime();
    float velocity = settings.movementSpeed * deltaTime;
    const Vector2& mousePos = Input::GetMousePosition();
    Vector2 mouseDelta = {mousePos.x-prevMousePos.x, prevMousePos.y-mousePos.y};
    prevMousePos = mousePos;
    
    if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
    {
      MouseRotate(mouseDelta);
    }
    if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
    {
      MousePan(mouseDelta, velocity);
    }
    
    
    if(Input::IsKeyPressed(Key::W))
    {
      perspective.position += perspective.localFront * velocity;
    }
    else if (Input::IsKeyPressed(Key::S))
    {
      perspective.position -= perspective.localFront * velocity;
    }
    if (Input::IsKeyPressed(Key::A))
    {
      perspective.position -= perspective.localRight * velocity;
    }
    else if (Input::IsKeyPressed(Key::D))
    {
      perspective.position += perspective.localRight * velocity;
    }
    
    if (settings.canRoll)
    {
      if (Input::IsKeyPressed(Key::Q))
      {
        perspective.roll -= deltaTime * settings.rollSpeed;
      }
      else if (Input::IsKeyPressed(Key::E))
      {
        perspective.roll += deltaTime * settings.rollSpeed;
      }
      else
      {
        perspective.roll = 0.0f;
      }
    }
    
    
    perspective.UpdateCameraVectors();
    //orthographic.OnUpdate();
  }
  void EditorCamera::OnEvent(Events::Event& event)
  {
    Events::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Events::MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(EditorCamera::OnMouseScroll));
    dispatcher.Dispatch<Events::WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(EditorCamera::OnWindowResized));
    
  }
  
  bool EditorCamera::OnMouseScroll(Events::MouseScrollEvent& event)
  {
    float deltaTime = Application::DeltaTime();
    float velocity = settings.scrollSensitivity * deltaTime;
    Vector3 direction = Vector3::Cross(perspective.localUp, perspective.localRight)*event.GetOffsetY();
    perspective.position += direction*velocity;
    perspective.UpdateCameraVectors();
    return false;
  }
  bool EditorCamera::OnWindowResized(Events::WindowResizeEvent& event)
  {
    SetViewportSize((float)event.GetWidth(), (float)event.GetHeight());
    //perspective.UpdateCameraVectors();
    return false;
  }
  void EditorCamera::MousePan(const Math::Vector2& mouseDelta, float velocity)
  {
    float xOffset = mouseDelta.x;
    float yOffset=mouseDelta.y;
    Vector3 directionA = Vector3::Cross(perspective.localUp, perspective.localFront)*xOffset;
    Vector3 directionB = Vector3::Cross(perspective.localFront, perspective.localRight)*yOffset;
    Vector3 direction = (directionA+directionB);
    
    perspective.position += direction*velocity;
  }
  
  void EditorCamera::MouseRotate(const Math::Vector2& mouseDelta)
  {
    Vector2 offset = mouseDelta * settings.mouseSensitivity;
    
    perspective.pitch += offset.y;
    perspective.yaw += offset.x;
    
    if (settings.constrainPitch)
    {
      if (perspective.pitch > 89.0f)
      {
        perspective.pitch = 89.0f;
      }
      if (perspective.pitch < -89.0f)
      {
        perspective.pitch = -89.0f;
      }
    }
  }
  void EditorCamera::SetViewportSize(float width, float height)
  {
    perspective.SetViewportSize(width, height);
    orthographic.SetViewportSize(width, height);
    //orthographic.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel)
  }
  void EditorCamera::SetViewportSize(const Math::Vector2& value)
  {
    SetViewportSize(value.x, value.y);
    
  }
  
  const CameraBase& EditorCamera::GetCamera3D()const
  {
    return perspective;
  }
  const CameraBase& EditorCamera::GetCamera2D()const
  {
    return orthographic;
  }
  Math::Matrix4 EditorCamera::GetViewMatrix3D()const
  {
    return perspective.GetViewMatrix();
  }
  Math::Matrix4 EditorCamera::GetProjectionMatrix3D()const
  {
    return perspective.GetProjectionMatrix();
  }
  Math::Matrix4 EditorCamera::GetViewMatrix2D()const
  {
    return orthographic.GetViewMatrix();
  }
  Math::Matrix4 EditorCamera::GetProjectionMatrix2D()const
  {
    return orthographic.GetProjectionMatrix();
  }
}