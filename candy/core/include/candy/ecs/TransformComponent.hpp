#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/math/Quaternion.hpp>
#include <candy/base/UUID.hpp>
#include "Entity.hpp"
namespace Candy::ECS
{
  
  class TransformComponent
  {
  private:
    Entity entity;
    //TransformComponent* parent=nullptr;
    
   
    
    Math::Vector3 localPosition = {0.0f, 0.0f, 0.0f};
    Math::Quaternion localRotation = {0.0f, 0.0f, 0.0f, 1.0f};
    Math::Vector3 localScale = {1.0f, 1.0f, 1.0f};
    
    
    //std::vector<TransformComponent*> children;
    
  private:
    //void UpdateRelationships();
    
    
    
  public:
    explicit TransformComponent(const Entity& entity);
  
  
  public:
    [[nodiscard]] Entity GetEntity()const;
    [[nodiscard]] Math::Matrix4 GetWorldTransform()const;
    [[nodiscard]] Math::Matrix4 GetLocalTransform()const;
    
    [[nodiscard]] Math::Vector3 GetLocalPosition()const;
    [[nodiscard]] Math::Quaternion GetLocalRotation()const;
    [[nodiscard]] Math::Vector3 GetLocalScale()const;
    
    [[nodiscard]] Math::Vector3 GetWorldPosition()const;
    [[nodiscard]] Math::Quaternion GetWorldRotation()const;
    [[nodiscard]] Math::Vector3 GetWorldScale()const;
    
    void SetLocalPosition(const Math::Vector3& value);
    void SetLocalRotation(const Math::Quaternion& value);
    void SetLocalScale(const Math::Vector3& value);
    void SetLocal(const Math::Vector3& positionValue, const Math::Quaternion& rotationValue, const Math::Vector3& scaleValue);
    
    
    [[nodiscard]] bool HasParent()const;
    [[nodiscard]] bool HasChildren()const;
    [[nodiscard]] std::vector<TransformComponent*> GetChildren();
    
    
    
    TransformComponent* GetParent();
    const TransformComponent* GetParent()const;
    
  private:
    friend class SceneSerializer;
    
  };
}