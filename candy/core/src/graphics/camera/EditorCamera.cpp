#include <candy/graphics/camera/EditorCamera.hpp>
#include <candy/event/Events.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  using namespace Events;
  EditorCamera::EditorCamera(const Vector3& pos, const Vector3& upValue, float yawValue, float pitchValue)
  : CameraBase(pos), localFront(Math::Vector3(0.0f, 0.0f, 1.0f)), localUp(upValue), pitch(pitchValue), yaw(yawValue), roll(ROLL), fov(FOV),
  movementSpeed(MOVEMENT_SPEED), mouseSensitivity(MOUSE_SENSITIVITY), scrollSensitivity(SCROLL_SENSITIVITY), rollSpeed(ROLL_SPEED)
  {
    prevMousePos = viewportSize/2.0f;
    UpdateProjectionMatrix();
    UpdateViewMatrix();
  }
  
  void EditorCamera::UpdateViewMatrix()
  {
    viewMatrix = Matrix4::LookAt(position, position+localFront, localUp);
    //viewMatrix2D = Matrix4::Translate(Matrix4::IDENTITY, Vector3(position.x, position.y, 0.0f));
  }
  void EditorCamera::UpdateProjectionMatrix()
  {
    projectionMatrix = Matrix4::Perspective(Math::ToRadians(fov), GetAspectRatio(), nearClip, farClip);
    projectionMatrix[1,1] *= -1;
    //orthographicProjectionMatrix = Matrix4::Orthographic(0.0f, viewportSize.x, 0.0f, viewportSize.y, 0.0f, 1.0f);
    //orthographicProjectionMatrix[1,1]*=-1;
  }
  void EditorCamera::UpdateCameraVectors()
  {
    // calculate the new front vector
    Math::Vector3 frontVec;
    frontVec.x = Math::Cos(Math::ToRadians(yaw)) * Math::Cos(Math::ToRadians(pitch));
    frontVec.y = Math::Sin(Math::ToRadians(pitch));
    frontVec.z = Math::Sin(Math::ToRadians(yaw)) * Math::Cos(Math::ToRadians(pitch));
    localFront = Math::Vector3::Normalize(frontVec);
    // also re-calculate the right and up vector
    localRight = Math::Vector3::Normalize(Math::Vector3::Cross(localFront, Math::Vector3::up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    localUp    = Math::Vector3::Normalize(Math::Vector3::Cross(localRight, localFront));
    UpdateViewMatrix();
    
    
    
    // Calculate the new front vector
    /*Math::Vector3 front;
    front.x = Math::Cos(ToRadians(yaw)) * Math::Cos(ToRadians(pitch));
    front.y = Math::Sin(ToRadians(pitch));
    front.z = Math::Sin(ToRadians(yaw)) * Math::Cos(ToRadians(pitch));
    localFront = Math::Vector3::Normalize(front);
    
    // Create the rotation matrix for the roll
    Math::Matrix4 rollRotationMatrix = Math::Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(roll), localFront);
    
    // Rotate the front vector by the roll matrix
    localFront = rollRotationMatrix * localFront;
    localUp =  rollRotationMatrix * localUp;
    
    // Calculate the right and up vector using the world up vector
    localRight  = Math::Vector3::Normalize(Math::Vector3::Cross(localFront, localUp));
    localUp     = Math::Vector3::Normalize(Math::Vector3::Cross(localRight, localFront));*/
    
    //UpdateViewMatrix();
  }
  float EditorCamera::GetFov()const{return fov;}
  float EditorCamera::GetAspectRatio()const{return viewportSize.x/viewportSize.y;}
  
  /*const Math::Matrix4& EditorCamera::GetViewMatrix2D() const
  {
    //return viewMatrix;
    return viewMatrix2D;
  }
  
  const Math::Matrix4& EditorCamera::GetOrthographicProjectionMatrix()const
  {
    //return projectionMatrix;
    return orthographicProjectionMatrix;
  }
  
  
  Math::Matrix4 EditorCamera::GetViewProjectionMatrix2D()const
  {
    return orthographicProjectionMatrix*viewMatrix2D;
  }*/
  Math::Vector2 EditorCamera::CalculatePanSpeed() const
  {
    float x = Math::Min(viewportSize.width / 1000.0f, 2.4f); // max = 2.4f
    float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;
    
    float y = Math::Min(viewportSize.height / 1000.0f, 2.4f); // max = 2.4f
    float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;
    
    return { xFactor, yFactor };
  }
  
  float EditorCamera::GetRollSpeed() const
  {
    return rollSpeed;
  }
  
  float EditorCamera::CalculateZoomSpeed() const
  {
    float d = distance * 0.2f;
    d = Math::Max(d, 0.0f);
    float speed = d * d;
    speed = Math::Min(speed, 100.0f); // max speed = 100
    return speed;
  }
  
  void EditorCamera::OnUpdate()
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
      position += localFront * velocity;
    }
    else if (Input::IsKeyPressed(Key::S))
    {
      position -= localFront * velocity;
    }
    if (Input::IsKeyPressed(Key::A))
    {
      position -= localRight * velocity;
    }
    else if (Input::IsKeyPressed(Key::D))
    {
      position += localRight * velocity;
    }
    
    if (canRoll)
    {
      if (Input::IsKeyPressed(Key::Q))
      {
        roll -= deltaTime * rollSpeed;
      }
      else if (Input::IsKeyPressed(Key::E))
      {
        roll += deltaTime * rollSpeed;
      }
      else
      {
        roll = 0.0f;
      }
    }
    
    
    UpdateCameraVectors();
  }
  
  
  
  void EditorCamera::MousePan(const Math::Vector2& mouseDelta, float velocity)
  {
    float xOffset = mouseDelta.x;
    float yOffset=mouseDelta.y;
    Vector3 directionA = Vector3::Cross(localUp, localFront)*xOffset;
    Vector3 directionB = Vector3::Cross(localFront, localRight)*yOffset;
    Vector3 direction = (directionA+directionB);
    
    position += direction*velocity;
    
  }
  void EditorCamera::MouseRotate(const Math::Vector2& mouseDelta, bool constrainPitch)
  {
    Vector2 offset = mouseDelta * mouseSensitivity;
    
    pitch += offset.y;
    yaw += offset.x;
    
    if (constrainPitch)
    {
      if (pitch > 89.0f)
      {
        pitch = 89.0f;
      }
      if (pitch < -89.0f)
      {
        pitch = -89.0f;
      }
    }
    
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
    float velocity = scrollSensitivity * deltaTime;
    Vector3 direction = Vector3::Cross(localUp, localRight)*event.GetOffsetY();
    position += direction*velocity;
    UpdateCameraVectors();
    return false;
  }
  bool EditorCamera::OnWindowResized(Events::WindowResizeEvent& event)
  {
    SetViewportSize((float)event.GetWidth(), (float)event.GetHeight());
    UpdateCameraVectors();
    return false;
  }
  
  
  
  Math::Vector3 EditorCamera::GetLocalUp() const
  {
    return localUp;
  }
  
  Math::Vector3 EditorCamera::GetLocalRight() const
  {
    return localRight;
  }
  
  Math::Vector3 EditorCamera::GetLocalForward() const
  {
    return localFront;
  }
  
  float EditorCamera::GetDistance() const
  {
    return distance;
  }
  void EditorCamera::SetDistance(float value)
  {
    distance = value;
  }
  void EditorCamera::SetViewportSize(float width, float height)
  {
    viewportSize.Set(width, height);
    UpdateProjectionMatrix();
  }
  void EditorCamera::SetViewportSize(const Math::Vector2& value)
  {
    SetViewportSize(value.x, value.y);
  }
  
  void EditorCamera::SetNearClip(float value){nearClip = value;}
  void EditorCamera::SetFarClip(float value){farClip = value;}
  void EditorCamera::SetClipRange(float near, float far){nearClip = near; farClip = far;}
  void EditorCamera::SetFov(float value){fov = value;}
  
  
  
  
  float EditorCamera::GetPitch() const
  {
    return pitch;
  }
  float EditorCamera::GetYaw() const
  {
    return yaw;
  }
  float EditorCamera::GetRoll()const
  {
    return roll;
  }
}