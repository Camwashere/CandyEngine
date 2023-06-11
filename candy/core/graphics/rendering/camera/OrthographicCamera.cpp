#include "OrthographicCamera.hpp"

namespace Candy::Graphics
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
            : projectionMatrix(Math::Matrix4::Orthographic(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f)
    {
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
    
    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        projectionMatrix = Math::Matrix4::Orthographic(left, right, bottom, top, -1.0f, 1.0f);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
    
    void OrthographicCamera::RecalculateViewMatrix()
    {
        Math::Matrix4 transform = Math::Matrix4::Translation(position) *
                              Math::Matrix4::Rotated(Math::Matrix4::Eye(), Math::ToRadians(rotation), Math::Vector3::forward);
        
        viewMatrix = Math::Matrix4::Invert(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
}