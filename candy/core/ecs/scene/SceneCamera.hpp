#pragma once

#include "../../graphics/rendering/camera/Camera.hpp"
#include <Candy/Math.hpp>
namespace Candy::Graphics
{
    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType{PERSPECTIVE=0, ORTHOGRAPHIC=1};
        
    private:
        ProjectionType projectionType=ProjectionType::ORTHOGRAPHIC;
        float perspectiveFov=Math::ToRadians(45.0f);
        float perspectiveNear = 0.01f;
        float perspectiveFar=1000.0f;
        
        float orthographicSize=10.0f;
        float orthographicNear=-1.0f;
        float orthographicFar=1.0f;
        
        float aspectRatio=0.0f;
        
    private:
        void RecalculateProjection();
        
    public:
        SceneCamera();
        virtual ~SceneCamera()=default;
        
    public:
        void SetPerspective(float verticalFov, float nearClip, float farClip);
        void SetOrthographic(float size, float nearClip, float farClip);
        
        void SetViewportSize(uint32 width, uint32 height);
        
        float GetPerspectiveVerticalFov()const{return perspectiveFov;}
        void SetPerspectiveVerticalFov(float verticalFov){perspectiveFov=verticalFov; RecalculateProjection();}
        
        float GetPerspectiveNearClip() const { return perspectiveNear; }
        void SetPerspectiveNearClip(float nearClip) { perspectiveNear = nearClip; RecalculateProjection(); }
        float GetPerspectiveFarClip() const { return perspectiveFar; }
        void SetPerspectiveFarClip(float farClip) { perspectiveFar = farClip; RecalculateProjection(); }
        
        float GetOrthographicSize() const { return orthographicSize; }
        void SetOrthographicSize(float size) { orthographicSize = size; RecalculateProjection(); }
        float GetOrthographicNearClip() const { return orthographicNear; }
        void SetOrthographicNearClip(float nearClip) { orthographicNear = nearClip; RecalculateProjection(); }
        float GetOrthographicFarClip() const { return orthographicFar; }
        void SetOrthographicFarClip(float farClip) { orthographicFar = farClip; RecalculateProjection(); }
        
        ProjectionType GetProjectionType() const { return projectionType; }
        void SetProjectionType(ProjectionType type) { projectionType = type; RecalculateProjection(); }
    };
}