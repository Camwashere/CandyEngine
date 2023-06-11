#pragma once
#include <Candy/Math.hpp>

namespace Candy::Graphics
{
    class OrthographicCamera
    {
    private:
        Math::Matrix4 projectionMatrix;
        Math::Matrix4 viewMatrix;
        Math::Matrix4 viewProjectionMatrix;
        Math::Vector3 position;
        
        float rotation;
        
    private:
        void RecalculateViewMatrix();
        
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        
    public:
        void SetProjection(float left, float right, float bottom, float top);
        void SetPosition(const Math::Vector3& pos){position = pos; RecalculateViewMatrix();}
        const Math::Vector3& GetPosition()const{return position;}
        void SetRotation(float value){rotation = value; RecalculateViewMatrix();}
        float GetRotation()const{return rotation;}
        
        const Math::Matrix4& GetProjectionMatrix()const{return projectionMatrix;}
        const Math::Matrix4& GetViewMatrix()const{return viewMatrix;}
        const Math::Matrix4& GetViewProjectionMatrix()const{return viewProjectionMatrix;}
        
    };
}