#include "OrthographicCameraController.hpp"
#include <Candy/App.hpp>
namespace Candy::Graphics
{
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rot)
        : aspectRatio(aspectRatio), zoomLevel(1.0f), camera(-aspectRatio*zoomLevel, aspectRatio*zoomLevel, -zoomLevel, zoomLevel), rotation(rot), cameraPosition(0.0f), cameraRotation(0.0f), cameraMovementSpeed(5.0f), cameraRotationSpeed(180.0f)
    {
    
    }
    
    void OrthographicCameraController::OnUpdate()
    {
        float ts = Application::DeltaTime();
        if (Input::IsKeyPressed(Candy::Key::A))
        {
            cameraPosition.x -= Math::Cos(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
            cameraPosition.y -= Math::Sin(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
        }
        else if (Input::IsKeyPressed(Candy::Key::D))
        {
            cameraPosition.x += Math::Cos(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
            cameraPosition.y += Math::Sin(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
        }
        
        if (Input::IsKeyPressed(Candy::Key::W))
        {
            cameraPosition.x += -Math::Sin(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
            cameraPosition.y += Math::Cos(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
        }
        else if (Input::IsKeyPressed(Candy::Key::S))
        {
            cameraPosition.x -= -Math::Sin(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
            cameraPosition.y -= Math::Cos(Math::ToRadians(cameraRotation))*cameraMovementSpeed*ts;
        }
        
        if (rotation)
        {
            if (Input::IsKeyPressed(Key::Q))
                cameraRotation += cameraRotationSpeed * ts;
            if (Input::IsKeyPressed(Key::E))
                cameraRotation -= cameraRotationSpeed * ts;
            
            if (cameraRotation > 180.0f)
                cameraRotation -= 360.0f;
            else if (cameraRotation <= -180.0f)
                cameraRotation += 360.0f;
            
            camera.SetRotation(cameraRotation);
        }
        
        camera.SetPosition(cameraPosition);
        
        cameraMovementSpeed = zoomLevel;
        
        
    
    }
    
    void OrthographicCameraController::OnEvent(Events::Event& e)
    {
        
        Events::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Events::MouseScrollEvent>(CANDY_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScroll));
        dispatcher.Dispatch<Events::WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
    }
    
    void OrthographicCameraController::OnResize(float width, float height)
    {
        aspectRatio = width / height;
        camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }
    
    bool OrthographicCameraController::OnMouseScroll(Events::MouseScrollEvent& e)
    {
    
        zoomLevel -= e.GetOffsetY() * 0.25f;
        zoomLevel = std::max(zoomLevel, 0.25f);
        camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
        return false;
    }
    
    bool OrthographicCameraController::OnWindowResized(Events::WindowResizeEvent& e)
    {
        
        OnResize((float)e.GetWidth(), (float)e.GetHeight());
        return false;
    }
        

}