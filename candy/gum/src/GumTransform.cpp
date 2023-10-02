#include <gum/GumTransform.hpp>
#include <gum/GumComponents.hpp>
namespace Candy::Gum
{
  using namespace Math;
  GumTransform::DirtyFlag operator&(GumTransform::DirtyFlag a, GumTransform::DirtyFlag b)
  {
    return static_cast<GumTransform::DirtyFlag>(static_cast<std::underlying_type<GumTransform::DirtyFlag>::type>(a) & static_cast<std::underlying_type<GumTransform::DirtyFlag>::type>(b));
  }
  GumTransform::DirtyFlag operator|(GumTransform::DirtyFlag a, GumTransform::DirtyFlag b)
  {
    return static_cast<GumTransform::DirtyFlag>(static_cast<std::underlying_type<GumTransform::DirtyFlag>::type>(a) | static_cast<std::underlying_type<GumTransform::DirtyFlag>::type>(b));
  }
  
  GumTransform::DirtyFlag& operator|=(GumTransform::DirtyFlag& a, GumTransform::DirtyFlag b)
  {
    return a = a | b;
  }
  
  GumTransform::GumTransform(const GumObject &gumObject) : object(gumObject)
  {
  
  }
  void GumTransform::Update()
  {
    switch(dirtyFlag)
    {
      case DirtyFlag::None:
        return;
      case DirtyFlag::Transform:
        localMatrix = Matrix3::Translate(Matrix3::IDENTITY, localPosition)*Matrix3::Rotate(Matrix3::IDENTITY, localRotation)*Matrix3::Scale(Matrix3::IDENTITY, localScale);
        worldMatrix = HasParentTransform() ? GetParentTransform().GetWorldTransform() * localMatrix : localMatrix;
        break;
      case DirtyFlag::Order:
        worldDepthIndex = HasParentTransform() ? GetParentTransform().GetWorldDepthIndex() + localDepthIndex : localDepthIndex;
        break;
      case DirtyFlag::All:
        localMatrix = Matrix3::Translate(Matrix3::IDENTITY, localPosition)*Matrix3::Rotate(Matrix3::IDENTITY, localRotation)*Matrix3::Scale(Matrix3::IDENTITY, localScale);
        worldMatrix = HasParentTransform() ? GetParentTransform().GetWorldTransform() * localMatrix : localMatrix;
        worldDepthIndex = HasParentTransform() ? GetParentTransform().GetWorldDepthIndex() + localDepthIndex : localDepthIndex;
        break;
      default:
        CANDY_CORE_ERROR("GumTransform::Update() called with no dirty flags");
        break;
    }
    ClearDirtyFlags();
  }
  
  
  
  void GumTransform::ClearDirtyFlags()
  {
    dirtyFlag = DirtyFlag::None;
  }
  void GumTransform::AppendDirtyFlag(GumTransform::DirtyFlag flag)
  {
    dirtyFlag |= flag;
    
    if (HasChildrenTransforms())
    {
      auto& children = GetChildrenObjects().children;
      for (auto& child : children)
      {
        if (child.HasTransform())
        {
          child.GetTransform().AppendDirtyFlag(flag);
        }
      }
    }
  }
  bool GumTransform::HasFlag(DirtyFlag flag)const
  {
    return (dirtyFlag & flag) == flag;
  }
  
  
  GumObject GumTransform::GetGumObject() const
  {
    return object;
  }
  
  Math::Matrix3 GumTransform::GetWorldTransform()
  {
    CANDY_PROFILE_FUNCTION();
    Update();
    return worldMatrix;
  }
  Math::Vector2 GumTransform::GetWorldPosition()
  {
    if (HasParentTransform())
    {
      return GetParentTransform().GetWorldTransform() * localPosition;
    }
    else
    {
      return localPosition;
    }
  }
  float GumTransform::GetWorldRotation()
  {
    if (HasParentTransform())
    {
      return GetParentTransform().GetWorldRotation() + localRotation;
    }
    else
    {
      return localRotation;
    }
  }
  Math::Vector2 GumTransform::GetWorldScale()
  {
    if (HasParentTransform())
    {
      return GetParentTransform().GetWorldScale() * localScale;
    }
    else
    {
      return localScale;
    }
    
  }
  int GumTransform::GetWorldDepthIndex()
  {
    if (HasParentTransform())
    {
      return GetParentTransform().GetWorldDepthIndex() + localDepthIndex;
    }
    else
    {
      return localDepthIndex;
    }
  }
  Math::Matrix3 GumTransform::GetLocalTransform()const
  {
    return localMatrix;
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
  
  int GumTransform::GetLocalDepthIndex()const
  {
    return localDepthIndex;
  }
  
  void GumTransform::ResetDepthIndex()
  {
    localDepthIndex = 0;
    AppendDirtyFlag(DirtyFlag::Order);
  }
  void GumTransform::SetLocalPosition(const Math::Vector2 &value)
  {
    localPosition = value;
    AppendDirtyFlag(DirtyFlag::Transform);
  }
  
  void GumTransform::SetLocalRotation(float value)
  {
    localRotation = value;
    AppendDirtyFlag(DirtyFlag::Transform);
  }
  
  void GumTransform::SetLocalScale(const Math::Vector2 &value)
  {
    localScale = value;
    AppendDirtyFlag(DirtyFlag::Transform);
  }
  
  void GumTransform::SetLocalTransform(const Math::Vector2 &positionValue, float rotationValue, const Math::Vector2 &scaleValue)
  {
    localPosition = positionValue;
    localRotation = rotationValue;
    localScale = scaleValue;
    AppendDirtyFlag(DirtyFlag::Transform);
  }
  void GumTransform::SetLocalDepthIndex(int value)
  {
    localDepthIndex = value;
    AppendDirtyFlag(DirtyFlag::Order);
  }
  void GumTransform::SetLocal(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue, int depthIndexValue)
  {
    localPosition = positionValue;
    localRotation = rotationValue;
    localScale = scaleValue;
    localDepthIndex = depthIndexValue;
    AppendDirtyFlag(DirtyFlag::All);
  }
  bool GumTransform::HasParentObject()const
  {
    return object.HasParent();
  }
  bool GumTransform::HasChildrenObjects()const
  {
    return object.HasChildren();
  }
  
  bool GumTransform::HasParentTransform()const
  {
    return object.HasParent() && object.GetParent().parent.HasTransform();
  }
  bool GumTransform::HasChildrenTransforms()const
  {
    if (HasChildrenObjects())
    {
      const auto& children = GetChildrenObjects().children;
      for (const auto& child : children)
      {
        if (child.HasTransform())
          return true;
      }
    }
    return false;
  }
  
  
  GumChildren& GumTransform::GetChildrenObjects()
  {
    CANDY_CORE_ASSERT(HasChildrenObjects(), "GumTransform does not have children objects");
    return object.GetChildren();
  }
  
  const GumChildren& GumTransform::GetChildrenObjects()const
  {
    CANDY_CORE_ASSERT(HasChildrenObjects(), "GumTransform does not have children objects");
    return object.GetChildren();
  }
  
  GumParent& GumTransform::GetParentObject()
  {
    CANDY_CORE_ASSERT(HasParentObject(), "GumTransform does not have parent object");
    return object.GetParent();
  }
  const GumParent& GumTransform::GetParentObject()const
  {
    CANDY_CORE_ASSERT(HasParentObject(), "GumTransform does not have parent object");
    return object.GetParent();
  }
  GumTransform& GumTransform::GetParentTransform()
  {
    CANDY_CORE_ASSERT(HasParentTransform(), "GumTransform does not have parent transform");
    return object.GetParent().parent.GetTransform();
  }
  const GumTransform& GumTransform::GetParentTransform()const
  {
    CANDY_CORE_ASSERT(HasParentTransform(), "GumTransform does not have parent transform");
    return object.GetParent().parent.GetTransform();
  }
}