#include <candy/graphics/camera/PerspectiveCameraController.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  using namespace Events;
  PerspectiveCameraController::PerspectiveCameraController(const Math::Vector3& pos) : camera(pos), movementSpeed(MOVEMENT_SPEED), mouseSensitivity(MOUSE_SENSITIVITY), scrollSensitivity(SCROLL_SENSITIVITY), rollSpeed(ROLL_SPEED)
  {
    prevMousePos = camera.viewportSize/2.0f;
  }
  
  void PerspectiveCameraController::OnUpdate()
  {
    CANDY_PROFILE_FUNCTION();
    float deltaTime = Application::DeltaTime();
    float velocity = movementSpeed * deltaTime;
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
      camera.position += camera.localFront * velocity;
    }
    else if (Input::IsKeyPressed(Key::S))
    {
      camera.position -= camera.localFront * velocity;
    }
    if (Input::IsKeyPressed(Key::A))
    {
      camera.position -= camera.localRight * velocity;
    }
    else if (Input::IsKeyPressed(Key::D))
    {
      camera.position += camera.localRight * velocity;
    }
    
    if (canRoll)
    {
      if (Input::IsKeyPressed(Key::Q))
      {
        camera.roll -= deltaTime * rollSpeed;
      }
      else if (Input::IsKeyPressed(Key::E))
      {
        camera.roll += deltaTime * rollSpeed;
      }
      else
      {
        camera.roll = 0.0f;
      }
    }
    
    
    camera.UpdateCameraVectors();
  }
  void PerspectiveCameraController::OnEvent(Events::Event& event)
  {
    CANDY_PROFILE_FUNCTION();
    Events::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Events::MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(PerspectiveCameraController::OnMouseScroll));
    dispatcher.Dispatch<Events::WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(PerspectiveCameraController::OnWindowResized));
  }
  
  bool PerspectiveCameraController::OnMouseScroll(Events::MouseScrollEvent& event)
  {
    CANDY_PROFILE_FUNCTION();
    float deltaTime = Application::DeltaTime();
    float velocity = scrollSensitivity * deltaTime;
    Vector3 direction = Vector3::Cross(camera.localUp, camera.localRight)*event.GetOffsetY();
    camera.position += direction*velocity;
    camera.UpdateCameraVectors();
    return false;
  }
  bool PerspectiveCameraController::OnWindowResized(Events::WindowResizeEvent& event)
  {
    CANDY_PROFILE_FUNCTION();
    camera.SetViewportSize((float)event.GetWidth(), (float)event.GetHeight());
    camera.UpdateCameraVectors();
    return false;
  }
  void PerspectiveCameraController::MousePan(const Math::Vector2& mouseDelta, float velocity)
  {
    CANDY_PROFILE_FUNCTION();
    float xOffset = mouseDelta.x;
    float yOffset=mouseDelta.y;
    Vector3 directionA = Vector3::Cross(camera.localUp, camera.localFront)*xOffset;
    Vector3 directionB = Vector3::Cross(camera.localFront, camera.localRight)*yOffset;
    Vector3 direction = (directionA+directionB);
    
    camera.position += direction*velocity;
  }
  
  void PerspectiveCameraController::MouseRotate(const Math::Vector2& mouseDelta)
  {
    CANDY_PROFILE_FUNCTION();
    Vector2 offset = mouseDelta * mouseSensitivity;
    
    camera.pitch += offset.y;
    camera.yaw += offset.x;
    
    if (constrainPitch)
    {
      if (camera.pitch > 89.0f)
      {
        camera.pitch = 89.0f;
      }
      if (camera.pitch < -89.0f)
      {
        camera.pitch = -89.0f;
      }
    }
  }
  
  void PerspectiveCameraController::SetMovementSpeed(float value)
  {
    movementSpeed = value;
  }
  void PerspectiveCameraController::SetRollSpeed(float value)
  {
    rollSpeed = value;
  }
  void PerspectiveCameraController::SetMouseSensitivity(float value)
  {
    mouseSensitivity = value;
  }
  void PerspectiveCameraController::SetScrollSensitivity(float value)
  {
    scrollSensitivity = value;
  }
  void PerspectiveCameraController::SetPanSensitivity(const Math::Vector2& value)
  {
    panSensitivity = value;
  }
  void PerspectiveCameraController::SetPanSensitivity(float x, float y)
  {
    panSensitivity.Set(x, y);
  }
  void PerspectiveCameraController::SetCanRoll(bool value)
  {
    canRoll = value;
  }
  void PerspectiveCameraController::SetConstrainPitch(bool value)
  {
    constrainPitch = value;
  }
  
  PerspectiveCamera& PerspectiveCameraController::GetCamera()
  {
    return camera;
  }
  const PerspectiveCamera& PerspectiveCameraController::GetCamera()const
  {
    return camera;
  }
}