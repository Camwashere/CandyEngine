#include "EditorCamera.hpp"
#include <Candy/Math.hpp>
#include <Candy/Events.hpp>
namespace Candy{
    using namespace Math;
    using namespace Events;
    namespace Graphics
    {
        EditorCamera::EditorCamera(float fovValue, float aspectRatioValue, float nearClipValue, float farClipValue)
        : fov(fovValue), aspectRatio(aspectRatioValue), nearClip(nearClipValue), farClip(farClipValue), distance(10.0f),
        pitch(0.0f), yaw(0.0f), viewportSize(1280, 720), rotationSpeed(0.8f), zoomSpeed(0.25f), panSpeed(0.01f)
        {
            UpdateView();
        }
        
        
        void EditorCamera::UpdateProjection()
        {
            aspectRatio=viewportSize.x/viewportSize.y;
            projectionMatrix = Matrix4::Perspective(Math::ToRadians(fov), aspectRatio, nearClip, farClip);
        }
        
        void EditorCamera::UpdateView()
        {
            position = CalculatePosition();
            Math::Quaternion orientation = GetOrientation();
            viewMatrix = Matrix4::Translation(position)*orientation.ToMatrix();
            viewMatrix = Matrix4::Invert(viewMatrix);
        }
        
        Math::Vector2 EditorCamera::CalculatePanSpeed()const
        {
            float x = std::min(viewportSize.x/1000.0f, 2.4f);
            float xFactor = 0.0366f * (x*x) - 0.1778f * x + 0.3021f;
            
            float y = std::min(viewportSize.y/1000.0f, 2.4f);
            float yFactor = 0.0366f * (y*y) - 0.1778f * y + 0.3021f;
            
            return {xFactor, yFactor};
        }
        float EditorCamera::CalculateZoomSpeed()const
        {
            float dist = distance*0.2f;
            dist = Math::Max(dist, 0.0f);
            float speed = dist*dist;
            speed = Math::Min(speed, 100.0f);
            return speed;
        }
        
        Math::Vector3 EditorCamera::CalculatePosition()const
        {
            return focalPoint - GetLocalForward()*distance;
        }
        
        void EditorCamera::OnUpdate()
        {
            if (Input::IsKeyPressed(Key::LeftAlt))
            {
                const Math::Vector2& mousePos = Input::GetMousePosition();
                Math::Vector2 delta = (mousePos-initialMousePosition)*0.003f;
                initialMousePosition = mousePos;
                
                if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
                    MousePan(delta);
                else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
                    MouseRotate(delta);
                else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
                    MouseZoom(delta.y);
                
            }
            
            UpdateView();
        }
        
        void EditorCamera::OnEvent(Event& event)
        {
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(EditorCamera::OnMouseScroll));
        }
        
        bool EditorCamera::OnMouseScroll(MouseScrollEvent& event)
        {
            float delta = event.GetOffsetY() * 0.1f;
            MouseZoom(delta);
            UpdateView();
            return false;
        }
        void EditorCamera::MousePan(const Math::Vector2& delta)
        {
            Math::Vector2 speed = CalculatePanSpeed();
            focalPoint += GetLocalLeft() * delta.x * speed.x * distance;
            focalPoint += GetLocalUp() * delta.y * speed.y * distance;
        }
        void EditorCamera::MouseRotate(const Math::Vector2& delta)
        {
            float yawSign = GetLocalUp().y < 0 ? -1.0f : 1.0f;
            yaw += yawSign * delta.x * rotationSpeed;
            pitch += delta.y * rotationSpeed;
        }
        void EditorCamera::MouseZoom(float delta)
        {
            distance -= delta * CalculateZoomSpeed();
            if (distance < 1.0f)
            {
                focalPoint += GetLocalForward();
                distance = 1.0f;
            }
        }
        
        Math::Vector3 EditorCamera::GetLocalUp()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::up);
        }
        Math::Vector3 EditorCamera::GetLocalDown()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::down);
        }
        Math::Vector3 EditorCamera::GetLocalRight()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::right);
        }
        Math::Vector3 EditorCamera::GetLocalLeft()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::left);
        }
        Math::Vector3 EditorCamera::GetLocalForward()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::back);
        }
        Math::Vector3 EditorCamera::GetLocalBack()const
        {
            return Quaternion::Rotate(GetOrientation(), Vector3::forward);
        }
        
        Math::Quaternion EditorCamera::GetOrientation()const
        {
            return Math::Quaternion(Vector3(-pitch, -yaw, 0.0f));
        }
        
    }
}