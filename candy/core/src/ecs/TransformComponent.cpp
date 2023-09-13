#include <candy/ecs/TransformComponent.hpp>
#include <candy/math/Quaternion.hpp>
#include <algorithm>
namespace Candy::ECS
{
  
  void TransformComponent::UpdateLocalTransform()
  {
    
    //Math::Quaternion rot = Math::Quaternion::Euler(rotation.ToRadians());
    rotation = rotation.Normalized();
    localTransform = Math::Matrix4::Translate(Math::Matrix4::IDENTITY, position) * Math::Matrix4::Rotate(Math::Matrix4::IDENTITY, rotation) * Math::Matrix4::Scale(Math::Matrix4::IDENTITY, scale);
    //localTransform = Math::Matrix4::Translate(Math::Matrix4::IDENTITY, position) * Math::Quaternion::ToMatrix(rotation) * Math::Matrix4::Scale(Math::Matrix4::IDENTITY, scale);
    if (parent)
    {
      parent->UpdateWorldTransform();
    }
    UpdateWorldTransform();
    for (TransformComponent* child : children)
    {
      child->UpdateWorldTransform();
    }
    
  }
  
  void TransformComponent::UpdateWorldTransform()
  {
    if (parent)
    {
      
      worldTransform = parent->GetWorldTransform() * localTransform;
    }
    else
    {
      worldTransform = localTransform;
    }
  }
  const Math::Matrix4& TransformComponent::GetWorldTransform()const
  {
    return worldTransform;
  }
  [[nodiscard]] const Math::Matrix4& TransformComponent::GetLocalTransform()const
  {
    return localTransform;
  }
  
  [[nodiscard]] const Math::Vector3& TransformComponent::GetPosition()const
  {
    return position;
  }
  
  [[nodiscard]] const Math::Quaternion& TransformComponent::GetRotation()const
  {
    return rotation;
  }
  
  [[nodiscard]] const Math::Vector3& TransformComponent::GetScale()const
  {
    return scale;
  }
  
  void TransformComponent::SetPosition(const Math::Vector3& value)
  {
    position = value;
    UpdateLocalTransform();
  }
  
  void TransformComponent::SetPosition2D(const Math::Vector2& value)
  {
    position.Set(value.x, value.y, position.z);
    UpdateLocalTransform();
  }
  void TransformComponent::SetRotation(const Math::Quaternion& value)
  {
    rotation = value;
    UpdateLocalTransform();
  }
  void TransformComponent::SetRotation2D(float value)
  {
    rotation.z = value;
    UpdateLocalTransform();
  }
  void TransformComponent::SetScale2D(const Math::Vector2& value)
  {
    scale.Set(value.x, value.y, scale.z);
    UpdateLocalTransform();
  }
  void TransformComponent::SetScale(const Math::Vector3& value)
  {
    scale = value;
    UpdateLocalTransform();
  }
  void TransformComponent::Set2D(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue)
  {
    position.Set(positionValue.x, positionValue.y, position.z);
    rotation.z = rotationValue;
    scale.Set(scaleValue.x, scaleValue.y, scale.z);
    UpdateLocalTransform();
  }
  void TransformComponent::Set(const Math::Vector3& positionValue, const Math::Quaternion& rotationValue, const Math::Vector3& scaleValue)
  {
    position = positionValue;
    rotation = rotationValue;
    scale = scaleValue;
    UpdateLocalTransform();
  }
  
  void TransformComponent::ApplyDeltaRotation(const Math::Vector3& rot)
  {
    rotation += rot;
    UpdateLocalTransform();
  }
  
  bool TransformComponent::HasParent()const
  {
    return parent != nullptr;
  }
  
  bool TransformComponent::HasChildren()const
  {
    return !children.empty();
  }
  
  bool TransformComponent::RemoveChild(const TransformComponent* child)
  {
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end())
    {
      children.erase(it);
      return true;
    }
    return false;
  }
  bool TransformComponent::AddChild(TransformComponent* child)
  {
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end())
    {
      children.push_back(child);
      return true;
    }
    return false;
  }
  
  const std::vector<TransformComponent*>& TransformComponent::GetChildren()const
  {
    return children;
  }
  
  void TransformComponent::SetParent(TransformComponent* parentValue)
  {
    if (parent)
    {
      parent->RemoveChild(this);
    }
    parent = parentValue;
    parent->AddChild(this);
  }
  
  TransformComponent* TransformComponent::GetParent()
  {
    return parent;
  }
}