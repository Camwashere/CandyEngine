#include "EditorCamera.hpp"
#include <Candy/Math.hpp>
#include <Candy/App.hpp>
#include <Candy/Events.hpp>
namespace Candy{
    using namespace Math;
    using namespace Events;
    namespace Graphics
    {
        EditorCamera::EditorCamera(const Vector3& pos, const Vector3& upValue, float yawValue, float pitchValue)
                : localFront(Math::Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), scrollSensitivity(SCROLL_SENSITIVITY), zoom(ZOOM),
                position(pos), localUp(upValue), yaw(yawValue), pitch(pitchValue)
        {
            UpdateCameraVectors();
        }
        
        Matrix4 EditorCamera::GetViewMatrix()const
        {
            return Matrix4::LookAt(position, position + localFront, localUp);
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
        }
        
        void EditorCamera::UpdateProjection()
        {
            aspectRatio = viewportWidth / viewportHeight;
            projectionMatrix = Matrix4::Perspective(Math::ToRadians(fov), aspectRatio, nearClip, farClip);
        }
        
        void EditorCamera::OnEvent(Event& event)
        {
            switch (event.GetType())
            {
                case Events::EventType::KEY_PRESSED:
                    ProcessKeyboardEvent();
                    break;
                case Events::EventType::MOUSE_MOVE:
                    ProcessMouseMovement(static_cast<Events::MouseMovedEvent&>(event));
                    break;
                case Events::EventType::MOUSE_SCROLL:
                    ProcessMouseScroll(static_cast<Events::MouseScrollEvent&>(event));
                    break;
                default:
                    break;
            }
        }
        
        void EditorCamera::OnUpdate()
        {
            ProcessKeyboardEvent();
        }
        
        void EditorCamera::ProcessKeyboard(Math::Direction3 direction, float deltaTime)
        {
            float velocity = movementSpeed * deltaTime;
            switch (direction)
            {
                case Math::Direction3::FORWARD:
                    position += localFront*velocity;
                    break;
                case Math::Direction3::BACK:
                    position -= localFront*velocity;
                    break;
                case Math::Direction2::UP:
                    position += localUp*velocity;
                    break;
                case Math::Direction2::DOWN:
                    position-=localUp*velocity;
                    break;
                case Math::Direction3::LEFT:
                    position -= localRight*velocity;
                    break;
                case Math::Direction3::RIGHT:
                    position += localRight*velocity;
                    break;
                default:
                    break;
            }
        }
        
        void EditorCamera::ProcessKeyboardEvent()
        {
            float deltaTime = Application::DeltaTime();
            if (Input::IsKeyPressed(Key::Escape))
            {
                Application::Instance().Terminate();
                return;
            }
            if (Input::IsKeyPressed(Key::W))
            {
                ProcessKeyboard(Math::Direction3::FORWARD, deltaTime);
            }
            if (Input::IsKeyPressed(Key::A))
            {
                ProcessKeyboard(Math::Direction3::LEFT, deltaTime);
            }
            if (Input::IsKeyPressed(Key::Q))
            {
                ProcessKeyboard(Math::Direction3::DOWN, deltaTime);
            }
            if (Input::IsKeyPressed(Key::S))
            {
                ProcessKeyboard(Math::Direction3::BACK, deltaTime);
            }
            if (Input::IsKeyPressed(Key::D))
            {
                ProcessKeyboard(Math::Direction3::RIGHT, deltaTime);
            }
            if (Input::IsKeyPressed(Key::E))
            {
                ProcessKeyboard(Math::Direction3::UP, deltaTime);
            }
            UpdateCameraVectors();
        }
        
        void EditorCamera::ProcessMouseMovement(const Events::MouseMovedEvent& event, bool constrainPitch)
        {
            if (firstMouse)
            {
                lastMousePos.x=event.GetX();
                lastMousePos.y=event.GetY();
                firstMouse=false;
            }
            if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
            {
                float xOffset = event.GetX() - lastMousePos.x;
                float yOffset=lastMousePos.y-event.GetY();
                lastMousePos = Math::Vector2(event.GetX(), event.GetY());
                ProcessMouseMovement(xOffset, yOffset, constrainPitch);
            }
            else if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
            {
                float xOffset = event.GetX() - lastMousePos.x;
                float yOffset=lastMousePos.y-event.GetY();
                lastMousePos = Math::Vector2(event.GetX(), event.GetY());
                float deltaTime = Application::DeltaTime();
                float velocity = movementSpeed * deltaTime;
                Vector3 directionA = Vector3::Cross(localUp, localFront)*xOffset;
                Vector3 directionB = Vector3::Cross(localFront, localRight)*yOffset;
                Vector3 direction = (directionA+directionB);
                
                position += direction*velocity;
                
                UpdateCameraVectors();
            }
            else
            {
                firstMouse=true;
            }
            
        }
        
        void EditorCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
        {
            
            xoffset *= mouseSensitivity;
            yoffset *= mouseSensitivity;
            
            yaw   += xoffset;
            pitch += yoffset;
            
            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }
            
            // update Front, Right and Up Vectors using the updated Euler angles
            UpdateCameraVectors();
        }
        void EditorCamera::ProcessMouseScroll(const Events::MouseScrollEvent& event)
        {
            float deltaTime = Application::DeltaTime();
            float velocity = scrollSensitivity * deltaTime;
            Vector3 direction = Vector3::Cross(localUp, localRight)*event.GetOffsetY();
            position += direction*velocity;
            
            UpdateCameraVectors();
        }
        
        
    }
}