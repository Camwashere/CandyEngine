#pragma once

#include "../../../../include/Candy/Math.hpp"
#include "../../../../include/Candy/Events.hpp"

namespace Candy::Graphics {
    
    class Camera
    {
    protected:
        Math::Matrix4 projectionMatrix=Math::Matrix4::Eye();
        
    public:
        Camera()=default;
        explicit Camera(const Math::Matrix4& projection) : projectionMatrix(projection){}
        virtual ~Camera()=default;
        
        [[nodiscard]] const Math::Matrix4& GetProjectionMatrix()const{return projectionMatrix;}
    };

}

