#include "SceneCamera.hpp"

namespace Candy::Graphics
{
    SceneCamera::SceneCamera()
    {
        RecalculateProjection();
    }
    
    void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip)
    {
        projectionType=ProjectionType::PERSPECTIVE;
        perspectiveFov=verticalFov;
        perspectiveNear = nearClip;
        perspectiveFar = farClip;
        RecalculateProjection();
    }
    
    void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
    {
        projectionType=ProjectionType::ORTHOGRAPHIC;
        orthographicSize=size;
        orthographicNear=nearClip;
        orthographicFar=farClip;
        RecalculateProjection();
    }
    
    void SceneCamera::SetViewportSize(uint32 width, uint32 height)
    {
        CANDY_CORE_ASSERT(width>0 && height>0);
        aspectRatio=(float)width/(float)height;
        RecalculateProjection();
    }
    
    void SceneCamera::RecalculateProjection()
    {
        if (projectionType == ProjectionType::PERSPECTIVE)
        {
            projectionMatrix = Math::Matrix4::Perspective(perspectiveFov, aspectRatio, perspectiveNear, perspectiveFar);
        }
        else
        {
            float orthoLeft = -orthographicSize * aspectRatio * 0.5f;
            float orthoRight = orthographicSize * aspectRatio * 0.5f;
            float orthoBottom = -orthographicSize * 0.5f;
            float orthoTop = orthographicSize * 0.5f;
            projectionMatrix = Math::Matrix4::Orthographic(orthoLeft, orthoRight, orthoBottom, orthoTop, orthographicNear, orthographicFar);
        }
    }
}