#pragma once
#include "candy/math/Matrix.hpp"
#include "candy/base/Base.hpp"

namespace Candy::Gum
{
  struct GumTransform
  {
    
    Math::Vector2 localPosition = {0, 0};
    float localRotation = 0.0f;
    Math::Vector2 localScale = {1, 1};
    Math::Matrix3 localMatrix;
    Math::Matrix3 worldMatrix;
    
  

    GumTransform();
    
    void CalculateLocalMatrix();
    void CalculateWorldMatrix(const Math::Matrix3& parentWorldMatrix);
    
  };
 
  
}