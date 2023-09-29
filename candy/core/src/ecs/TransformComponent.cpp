#include <candy/ecs/TransformComponent.hpp>
#include <candy/math/Quaternion.hpp>
#include <algorithm>
#include <candy/ecs/BaseComponents.hpp>

namespace Candy::ECS
{
  
  
  using namespace Math;
  TransformComponent::TransformComponent(const Entity& e) : entity(e)
  {
    MarkDirty();
  }
  
  void TransformComponent::Update()
  {
    localMatrix = Matrix4::Translate(Matrix4::IDENTITY, localPosition)*Matrix4::Rotate(Matrix4::IDENTITY, localRotation)*Matrix4::Scale(Matrix4::IDENTITY, localScale);
    if (HasParent())
    {
      worldMatrix = GetParent()->GetWorldTransform() * localMatrix;
    }
    else
    {
      worldMatrix = localMatrix;
    }
    dirty = false;
  }
  
  void TransformComponent::MarkDirty()
  {
    dirty = true;
    if (HasChildren())
    {
      auto children = GetChildren();
      for (auto child : children)
      {
        child->MarkDirty();
      }
    }
  }
  
  Entity TransformComponent::GetEntity()const
  {
    return entity;
  }
  Matrix4 TransformComponent::GetWorldTransform()
  {
    CANDY_PROFILE_FUNCTION();
    if (dirty)
    {
      Update();
    }
    return worldMatrix;
    
    /*if (HasParent())
    {
      return GetParent()->GetWorldTransform()*GetLocalTransform();
    }
    else
    {
      return GetLocalTransform();
    }*/
  }
  
  Matrix4 TransformComponent::GetLocalTransform()
  {
    CANDY_PROFILE_FUNCTION();
    if (dirty)
    {
      Update();
    }
    return localMatrix;
    //return Matrix4::Translate(Matrix4::IDENTITY, localPosition)*Matrix4::Rotate(Matrix4::IDENTITY, localRotation)*Matrix4::Scale(Matrix4::IDENTITY, localScale);
  }
  
  Math::Vector3 TransformComponent::GetLocalPosition() const
  {
    return localPosition;
  }
  
  Math::Quaternion TransformComponent::GetLocalRotation() const
  {
    return localRotation;
  }
  
  Math::Vector3 TransformComponent::GetLocalScale() const
  {
    return localScale;
  }
  
  void TransformComponent::SetLocalPosition(const Math::Vector3 &value)
  {
    localPosition = value;
    MarkDirty();
  }
  
  
  void TransformComponent::SetLocalRotation(const Math::Quaternion &value)
  {
    localRotation = value.Normalized();
    MarkDirty();
    
  }
  
  
  void TransformComponent::SetLocalScale(const Math::Vector3 &value)
  {
    localScale = value;
    MarkDirty();
    
  }
  
  void TransformComponent::SetLocal(const Math::Vector3 &positionValue, const Math::Quaternion &rotationValue, const Math::Vector3 &scaleValue)
  {
    localPosition = positionValue;
    localRotation = rotationValue.Normalized();
    localScale = scaleValue;
    MarkDirty();
    
  }
  
  Math::Vector3 TransformComponent::GetWorldPosition()
  {
    CANDY_PROFILE_FUNCTION();
    if (HasParent())
    {
      return GetParent()->GetWorldTransform() * localPosition;
    }
    else
    {
      return localPosition;
    }
  }
  Math::Quaternion TransformComponent::GetWorldRotation()
  {
    CANDY_PROFILE_FUNCTION();
    if (HasParent())
    {
      return GetParent()->GetWorldRotation() * localRotation;
    }
    else
    {
      return localRotation;
    }
  }
  Math::Vector3 TransformComponent::GetWorldScale()
  {
    CANDY_PROFILE_FUNCTION();
    if (HasParent())
    {
      return GetParent()->GetWorldScale() * localScale;
      //return parent->GetWorldScale() * localScale;
    }
    else
    {
      return localScale;
    }
  }
  bool TransformComponent::HasParent()const
  {
    return entity.HasParent();
  }
  
  bool TransformComponent::HasChildren()const
  {
    return entity.HasChildren();
  }
  
  
  
  std::vector<TransformComponent*> TransformComponent::GetChildren()
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<TransformComponent*> children;
    auto& entityChildren = entity.GetChildren();
    children.resize(entityChildren.Size());
    
    for (int i=0; i<entityChildren.Size(); i++)
    {
      children[i] = &entityChildren.children[i].GetComponent<TransformComponent>();
    }
    
    return children;
  }
  
  
  
  TransformComponent* TransformComponent::GetParent()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasParent());
    return &entity.GetParentEntity().GetComponent<TransformComponent>();
  }
  
  const TransformComponent* TransformComponent::GetParent()const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasParent());
    return &entity.GetParentEntity().GetComponent<TransformComponent>();
  }
}