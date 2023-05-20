#pragma once

#include "../../../include/Candy/Math.hpp"
#include "../color/ColorAll.hpp"
namespace Candy::Graphics {
    struct Material
    {
        float metallic;
        float specular;
        float roughness;
        
        Material() : metallic(0.5f), specular(0.5f), roughness(32.f){}
    };
    
    struct Light{
        Color color;
        Math::Vector3 position;
        float ambientStrength;
        
        Light() : color(Color::white), position(), ambientStrength(0.1f){}
    };
}

