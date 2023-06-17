#pragma once
#include <Candy/Math.hpp>
#include "Camera.hpp"
namespace Candy::Events
{
    class Event;
    class MouseScrollEvent;
}

namespace Candy::Graphics
{
    class EditorCamera : public Camera
    {
    private:
        static constexpr float YAW=-90.0f;
        static constexpr float PITCH       =  0.0f;
        static constexpr float SPEED       =  0.006f;
        static constexpr float SENSITIVITY =  0.1f;
        static constexpr float SCROLL_SENSITIVITY=0.1f;
        static constexpr float ZOOM        =  45.0f;
    private:
        // Camera Attributes
        Math::Vector3 position;
        Math::Vector3 localFront;
        Math::Vector3 localUp;
        Math::Vector3 localRight;
        
        // Euler Angles
        float yaw, pitch;
        
        // Camera Options
        float movementSpeed;
        float mouseSensitivity;
        float scrollSensitivity;
        float zoom;
        
        // Projection Attributes
        float fov, aspectRatio, nearClip, farClip;
        float viewportWidth, viewportHeight;
        
        // Mouse attributes
        bool firstMouse=true;
        Math::Vector2 lastMousePos;
    private:
        void UpdateCameraVectors();
        void UpdateProjection();
        void ProcessMouseMovement(const Events::MouseMovedEvent& event, bool constrainPitch=true);
        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch=true);
        void ProcessMouseScroll(const Events::MouseScrollEvent& event);
        void ProcessKeyboard(Math::Direction3 direction, float deltaTime);
        void ProcessKeyboardEvent();
        
    public:
        EditorCamera(const Math::Vector3& pos, const Math::Vector3& upValue=Math::Vector3::up, float yawValue=YAW, float pitchValue=PITCH);
        
        void SetViewportSize(float width, float height) {viewportWidth=width;viewportHeight = height; UpdateProjection();}
        Math::Matrix4 GetViewMatrix()const;
        Math::Matrix4 GetViewProjectionMatrix()const{return projectionMatrix*GetViewMatrix();}
        
        void OnEvent(Events::Event& event);
        
        void OnUpdate();
        
    };
}