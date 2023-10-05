#include "gum/GumTransform.hpp"

namespace Candy::Gum
{
  using namespace Math;
  GumTransform::GumTransform()
  {
    CalculateLocalMatrix();
    worldMatrix = localMatrix;
    //CalculateWorldMatrix();
  }
  
  void GumTransform::CalculateLocalMatrix()
  {
    localMatrix = Matrix3::Translate(Matrix3::IDENTITY, localPosition)*Matrix3::Rotate(Matrix3::IDENTITY, localRotation)*Matrix3::Scale(Matrix3::IDENTITY, localScale);
  }
  
  void GumTransform::CalculateWorldMatrix(const Matrix3& parentWorldMatrix)
  {
    worldMatrix = parentWorldMatrix * localMatrix;
  }
  

}