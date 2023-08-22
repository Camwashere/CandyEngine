#include <candy/graphics/camera/CameraController.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  CameraController::CameraController() : camera(nullptr), movementSpeed(MOVEMENT_SPEED), mouseSensitivity(MOUSE_SENSITIVITY), scrollSensitivity(SCROLL_SENSITIVITY)
  {
    prevMousePos = Vector2::zero;
    
    
  }
  CameraController::CameraController(Camera* cameraValue) : camera(cameraValue), movementSpeed(MOVEMENT_SPEED), mouseSensitivity(MOUSE_SENSITIVITY), scrollSensitivity(SCROLL_SENSITIVITY)
  {
    prevMousePos = camera->screenSize/2.0f;
    
  }
  CameraController::~CameraController()=default;
  
  void CameraController::OnUpdate()
  {
    float deltaTime = Application::DeltaTime();
    float velocity = movementSpeed * deltaTime;
    const Vector2& mousePos = Input::GetMousePosition();
    Vector2 mouseDelta = {mousePos.x-prevMousePos.x, prevMousePos.y-mousePos.y};
    prevMousePos = mousePos;
    
    if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
    {
      MouseRotate(mouseDelta, true);
    }
    if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
    {
      MousePan(mouseDelta, velocity);
    }
    
    
    if(Input::IsKeyPressed(Key::W))
    {
      camera->position += camera->localFront * velocity;
    }
    else if (Input::IsKeyPressed(Key::S))
    {
      camera->position -= camera->localFront * velocity;
    }
    if (Input::IsKeyPressed(Key::A))
    {
      camera->position -= camera->localRight * velocity;
    }
    else if (Input::IsKeyPressed(Key::D))
    {
      camera->position += camera->localRight * velocity;
    }
    
    if (canRotate)
    {
      if (Input::IsKeyPressed(Key::Q))
      {
        camera->roll -= deltaTime * rotationSpeed;
      }
      else if (Input::IsKeyPressed(Key::E))
      {
        camera->roll += deltaTime * rotationSpeed;
      }
    }
    
    
    camera->UpdateCameraVectors();
    
  }
  
  Math::Vector2 CameraController::PanSpeed()
  {
    float x = Math::Min(camera->screenSize.x / 1000.0f, 2.4f); // max = 2.4f
    float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;
    
    float y = Math::Min(camera->screenSize.y / 1000.0f, 2.4f); // max = 2.4f
    float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;
    return {xFactor, yFactor};
  }
  
  void CameraController::MousePan(const Math::Vector2& mouseDelta, float velocity)
  {
    float xOffset = mouseDelta.x;
    float yOffset=mouseDelta.y;
    Vector3 directionA = Vector3::Cross(camera->localUp, camera->localFront)*xOffset;
    Vector3 directionB = Vector3::Cross(camera->localFront, camera->localRight)*yOffset;
    Vector3 direction = (directionA+directionB);
    
    camera->position += direction*velocity;
    
  }
  void CameraController::MouseRotate(const Math::Vector2& mouseDelta, bool constrainPitch)
  {
    Vector2 offset = mouseDelta * mouseSensitivity;
    
    camera->pitch += offset.y;
    camera->yaw += offset.x;
    
    if (constrainPitch)
    {
      if (camera->pitch > 89.0f)
      {
        camera->pitch = 89.0f;
      }
      if (camera->pitch < -89.0f)
      {
        camera->pitch = -89.0f;
      }
    }
    
  }
  void CameraController::OnEvent(Events::Event& event)
  {
    Events::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Events::MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(CameraController::OnMouseScroll));
    dispatcher.Dispatch<Events::WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(CameraController::OnWindowResized));
  }
  void CameraController::OnResize(float width, float height)
  {
    camera->SetScreenSize(width, height);
    camera->UpdateCameraVectors();
  }
  bool CameraController::OnMouseScroll(Events::MouseScrollEvent& event)
  {
    
    float deltaTime = Application::DeltaTime();
    float velocity = scrollSensitivity * deltaTime;
    Vector3 direction = Vector3::Cross(camera->localUp, camera->localRight)*event.GetOffsetY();
    camera->position += direction*velocity;
    camera->UpdateCameraVectors();
    return false;
  }
  bool CameraController::OnWindowResized(Events::WindowResizeEvent& event)
  {
    camera->SetScreenSize((float)event.GetWidth(), (float)event.GetHeight());
    camera->UpdateCameraVectors();
    return false;
  }
  
  void CameraController::LockRotation(){canRotate=false;}
  void CameraController::UnlockRotation(){canRotate=true;}
  [[nodiscard]] bool CameraController::CanRotate()const{return canRotate;}
  void CameraController::SetRotationEnabled(bool value){canRotate=value;}
  void CameraController::SetCamera(Camera* cameraObject){camera=cameraObject;}
  Camera& CameraController::GetCamera(){return *camera;}
  [[nodiscard]] const Camera& CameraController::GetCamera()const{return *camera;}
  
  [[nodiscard]] bool CameraController::HasCamera()const{return camera!=nullptr;}
  [[nodiscard]] bool CameraController::NeedsCamera()const{return camera==nullptr;}
}