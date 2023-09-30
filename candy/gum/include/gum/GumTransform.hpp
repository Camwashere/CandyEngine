#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/base/Base.hpp>
#include "GumObject.hpp"
namespace Candy::Gum
{
  class GumTransform
  {
  public:
    enum class DirtyFlag
    {
      None = BIT(0),
      Transform = BIT(1),
      Order = BIT(2),
    };
  private:
    GumObject object;
    Math::Vector2 localPosition = {0, 0};
    float localRotation = 0.0f;
    Math::Vector2 localScale = {1, 1};
    int zIndex=0;
    DirtyFlag dirtyFlag = DirtyFlag::None;
  
  private:
    void Update();
    void AppendDirtyFlag(DirtyFlag flag);
    
  public:
    explicit GumTransform(const GumObject& object);
    
  
  public:
    [[nodiscard]] GumObject GetGumObject()const;
    
    
    [[nodiscard]] Math::Vector2 GetLocalPosition()const;
    [[nodiscard]] float GetLocalRotation()const;
    [[nodiscard]] Math::Vector2 GetLocalScale()const;
    
   
    
    void SetLocalPosition(const Math::Vector2& value);
    void SetLocalRotation(float value);
    void SetLocalScale(const Math::Vector2& value);
    void SetLocal(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue);
    
    
    
  
  
  
    
  };
}