#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/base/Base.hpp>
#include "GumObject.hpp"
#include <candy/math/geometry/Bounds2D.hpp>
namespace Candy::Gum
{
  class GumTransform
  {
  public:
    enum class DirtyFlag : uint8_t
    {
      None = BIT(0),
      Transform = BIT(1),
      Order = BIT(2),
      All = Transform | Order
    };
    
  private:
    GumObject object;
    Math::Vector2 localPosition = {0, 0};
    float localRotation = 0.0f;
    Math::Vector2 localScale = {1, 1};
    Math::Matrix3 localMatrix;
    Math::Matrix3 worldMatrix;
    int localDepthIndex=0;
    int worldDepthIndex=0;
    DirtyFlag dirtyFlag = DirtyFlag::None;
  
  public:
    explicit GumTransform(const GumObject& object);
  
  private:
    void Update();
    void ClearDirtyFlags();
    void AppendDirtyFlag(DirtyFlag flag);
    bool HasFlag(DirtyFlag flag)const;
    
  
    
  
  public:
    [[nodiscard]] GumObject GetGumObject()const;
    
    [[nodiscard]] Math::Matrix3 GetWorldTransform();
    [[nodiscard]] Math::Vector2 GetWorldPosition();
    [[nodiscard]] float GetWorldRotation();
    [[nodiscard]] Math::Vector2 GetWorldScale();
    [[nodiscard]] int GetWorldDepthIndex();
    
    
    [[nodiscard]] Math::Matrix3 GetLocalTransform()const;
    [[nodiscard]] Math::Vector2 GetLocalPosition()const;
    [[nodiscard]] float GetLocalRotation()const;
    [[nodiscard]] Math::Vector2 GetLocalScale()const;
    [[nodiscard]] int GetLocalDepthIndex()const;
    
   
    void ResetDepthIndex();
    void SetLocalPosition(const Math::Vector2& value);
    void SetLocalRotation(float value);
    void SetLocalScale(const Math::Vector2& value);
    void SetLocalTransform(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue);
    void SetLocalDepthIndex(int value);
    void SetLocal(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue, int depthIndexValue);
    
    [[nodiscard]] bool HasParentObject()const;
    [[nodiscard]] bool HasChildrenObjects()const;
    [[nodiscard]] bool HasParentTransform()const;
    [[nodiscard]] bool HasChildrenTransforms()const;
    
    
    
    GumChildren& GetChildrenObjects();
    const GumChildren& GetChildrenObjects()const;
    
    
    
    GumParent& GetParentObject();
    const GumParent& GetParentObject()const;
    
    GumTransform& GetParentTransform();
    const GumTransform& GetParentTransform()const;
    
    
    
  
  
  
    
  };
 
  
}