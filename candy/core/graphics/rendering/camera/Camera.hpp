#pragma once

#include "../../../../include/Candy/Math.hpp"
#include "../../../../include/Candy/Events.hpp"

namespace Candy::Graphics {
    
    class Camera
    {
    protected:
        Math::Matrix4 projectionMatrix;
        
    public:
        Camera()=default;
        Camera(const Math::Matrix4& projection) : projectionMatrix(projection){}
        virtual ~Camera()=default;
        
        const Math::Matrix4& GetProjectionMatrix()const{return projectionMatrix;}
    };
        
        /*class Camera {
        
        private:
            static constexpr float YAW         = -90.0f;
            static constexpr float PITCH       =  0.0f;
            static constexpr float SPEED       =  0.006f;
            static constexpr float SENSITIVITY =  0.1f;
            static constexpr float SCROLL_SENSITIVITY=0.1f;
            const float ZOOM        =  45.0f;
        public:
            // camera Attributes
            Math::Vector3 position;
            Math::Vector3 front;
            Math::Vector3 up;
            Math::Vector3 right;
            Math::Vector3 worldUp;
            
            Math::Vector2 lastMousePos;
            bool firstMouse;
            // euler Angles
            float yaw;
            float pitch;
            // camera options
            float MovementSpeed;
            float MouseSensitivity;
            float scrollSensitivity;
            float zoom;
        
        private:
            // calculates the front vector from the Camera's (updated) Euler Angles
            void UpdateCameraVectors();
            void ProcessMouseMovement(const Events::MouseMovedEvent& event, bool constainPitch = true);
            
            void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
            void ProcessMouseScroll(const Events::MouseScrollEvent& event);
            
            void ProcessKeyboard(Math::Direction3 direction, float deltaTime);
            void ProcessKeyboardEvent();
        public:
            // constructor with vectors
            Camera(Math::Vector3 pos, Math::Vector3 upValue = Math::Vector3(0.0f, 1.0f, 0.0f), float yawValue = YAW, float pitchValue = PITCH);
            
            
            // returns the view matrix calculated using Euler Angles and the LookAt Matrix
            Math::Matrix4 GetViewMatrix()const;
            
            void OnEvent(Events::Event& event);
            
            void OnUpdate();
            
            
            
            
        };*/
}

