#pragma once
#include <Candy/Math.hpp>

namespace Candy::Events
{
    class Event;
    class MouseScrollEvent;
}

namespace Candy::Graphics
{
    class EditorCamera
    {
    private:
        float fov, aspectRatio, nearClip, farClip;
        
        Math::Matrix4 projectionMatrix;
        Math::Matrix4 viewMatrix;
        Math::Vector3 position;
        Math::Vector3 focalPoint;
        
        Math::Vector2 initialMousePosition;
        
        float distance;
        float pitch, yaw;
        
        Math::Vector2 viewportSize;
        
        float rotationSpeed;
        float zoomSpeed;
        float panSpeed;
        
    private:
        void UpdateProjection();
        void UpdateView();
        
        bool OnMouseScroll(Events::MouseScrollEvent& event);
        
        void MousePan(const Math::Vector2& delta);
        void MouseRotate(const Math::Vector2& delta);
        void MouseZoom(float delta);
        
        Math::Vector3 CalculatePosition()const;
        
        
        Math::Vector2 CalculatePanSpeed()const;
        float CalculateZoomSpeed()const;
        
        
    public:
        EditorCamera(float fov=45.0f, float aspectRatio=1.778f, float nearClip=0.1f, float farClip=1000.0f);
        
    public:
        void OnUpdate();
        void OnEvent(Events::Event& event);
        
    public:
        inline float GetDistance()const{return distance;}
        inline void SetDistance(float value){distance=value;}
        inline void SetViewportSize(float width, float height){viewportSize.Set(width, height);}
        inline void SetViewportSize(const Math::Vector2& size){viewportSize=size; UpdateProjection();}
        
        const Math::Matrix4& GetViewMatrix()const{return viewMatrix;}
        const Math::Matrix4& GetProjectionMatrix()const{return projectionMatrix;}
        Math::Matrix4 GetViewProjectionMatrix()const{return projectionMatrix*viewMatrix;}
        
        Math::Vector3 GetLocalUp()const;
        Math::Vector3 GetLocalRight()const;
        Math::Vector3 GetLocalForward()const;
        Math::Vector3 GetLocalDown()const;
        Math::Vector3 GetLocalLeft()const;
        Math::Vector3 GetLocalBack()const;
        Math::Vector3 GetLocalDirection(Math::Direction3 direction)const;
        
        const Math::Vector3& GetPosition()const{return position;}
        Math::Quaternion GetOrientation()const;
        
        float GetPitch()const{return pitch;}
        float GetYaw()const{return yaw;}
        
        
        
    };
}