#include <gum/GumTransform.hpp>

namespace Candy::Gum
{
  
  void GumTransform::Update()
  {
  
  }
  
  void GumTransform::AppendDirtyFlag(GumTransform::DirtyFlag flag)
  {
  
  }
  
  GumTransform::GumTransform(const GumObject &object)
  {
  
  }
  
  GumObject GumTransform::GetGumObject() const
  {
    return object;
  }
  
 
  
  Math::Vector2 GumTransform::GetLocalPosition() const
  {
    return localPosition;
  }
  
  float GumTransform::GetLocalRotation() const
  {
    return localRotation;
  }
  
  Math::Vector2 GumTransform::GetLocalScale() const
  {
    return localScale;
  }
  
  
  
  
  void GumTransform::SetLocalPosition(const Math::Vector2 &value)
  {
  
  }
  
  void GumTransform::SetLocalRotation(float value)
  {
  
  }
  
  void GumTransform::SetLocalScale(const Math::Vector2 &value)
  {
  
  }
  
  void GumTransform::SetLocal(const Math::Vector2 &positionValue, float rotationValue, const Math::Vector2 &scaleValue)
  {
  
  }
  
  
}