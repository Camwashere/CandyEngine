#include <candy/ecs/TransformComponent.hpp>
#include <candy/math/Quaternion.hpp>
#include <algorithm>
#include <candy/ecs/BaseComponents.hpp>

namespace Candy::ECS
{
  
  
  using namespace Math;
  TransformComponent::TransformComponent(const Entity& e) : entity(e)
  {
  
  }
  
  
  /*void TransformComponent::UpdateRelationships()
  {
    if (entity.HasParent())
    {
      parent = &entity.GetParentEntity().GetComponent<TransformComponent>();
      parent->AddChild(this);
    }
    else
    {
      parent = nullptr;
    }
    
    
  }*/
  Entity TransformComponent::GetEntity()const
  {
    return entity;
  }
  Matrix4 TransformComponent::GetWorldTransform() const
  {
    if (HasParent())
    {
      return GetParent()->GetWorldTransform()*GetLocalTransform();
    }
    else
    {
      return GetLocalTransform();
    }
  }
  
  Matrix4 TransformComponent::GetLocalTransform() const
  {
    return Matrix4::Translate(Matrix4::IDENTITY, localPosition)*Matrix4::Rotate(Matrix4::IDENTITY, localRotation)*Matrix4::Scale(Matrix4::IDENTITY, localScale);
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
    
  }
  
  
  void TransformComponent::SetLocalRotation(const Math::Quaternion &value)
  {
    localRotation = value.Normalized();
    
  }
  
  
  void TransformComponent::SetLocalScale(const Math::Vector3 &value)
  {
    localScale = value;
    
  }
  
  void TransformComponent::SetLocal(const Math::Vector3 &positionValue, const Math::Quaternion &rotationValue, const Math::Vector3 &scaleValue)
  {
    localPosition = positionValue;
    localRotation = rotationValue.Normalized();
    localScale = scaleValue;
    
  }
  
  Math::Vector3 TransformComponent::GetWorldPosition() const
  {
    if (HasParent())
    {
      return GetParent()->GetWorldTransform() * localPosition;
    }
    else
    {
      return localPosition;
    }
  }
  Math::Quaternion TransformComponent::GetWorldRotation()const
  {
    if (HasParent())
    {
      return GetParent()->GetWorldRotation() * localRotation;
    }
    else
    {
      return localRotation;
    }
  }
  Math::Vector3 TransformComponent::GetWorldScale()const
  {
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
    CANDY_CORE_ASSERT(HasParent());
    return &entity.GetParentEntity().GetComponent<TransformComponent>();
  }
  
  const TransformComponent* TransformComponent::GetParent()const
  {
    CANDY_CORE_ASSERT(HasParent());
    return &entity.GetParentEntity().GetComponent<TransformComponent>();
  }
}