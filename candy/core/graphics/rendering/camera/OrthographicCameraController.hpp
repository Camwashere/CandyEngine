#pragma once
#include "OrthographicCamera.hpp"
#include <Candy/Events.hpp>
namespace Candy::Graphics
{
    class OrthographicCameraController
    {
    private:
        float aspectRatio;
        float zoomLevel;
        OrthographicCamera camera;
        bool rotation;
        
        Math::Vector3 cameraPosition;
        float cameraRotation;
        float cameraMovementSpeed;
        float cameraRotationSpeed;
        
    private:
        bool OnMouseScroll(Events::MouseScrollEvent& event);
        bool OnWindowResized(Events::WindowResizeEvent& event);
        
    public:
        explicit OrthographicCameraController(float aspectRatio, bool rotation=false);
        
    public:
        void OnUpdate();
        void OnEvent(Events::Event& event);
        
        void OnResize(float width, float height);
        
        OrthographicCamera& GetCamera(){return camera;}
        const OrthographicCamera& GetCamera()const{return camera;}
        
        float GetZoomLevel()const{return zoomLevel;}
        void SetZoomLevel(float value){zoomLevel=value;}
        
        
    };
}