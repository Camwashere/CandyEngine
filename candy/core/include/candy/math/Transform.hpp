#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/math/Quaternion.hpp>
namespace Candy::Math
{
  struct Transform
  {
  private:
    Math::Vector3 position = {0.0f, 0.0f, 0.0f};
    Math::Quaternion rotation = {0.0f, 0.0f, 0.0f, 1.0f};
    Math::Vector3 scale = {1.0f, 1.0f, 1.0f};
    
    Math::Matrix4 matrix;
    
    
    
  };
}