#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/math/Quaternion.hpp>
namespace Candy::ECS
{
  class TransformComponent
  {
  private:
    //Entity* owner = nullptr;
    TransformComponent* parent = nullptr;
    
    Math::Vector3 position = {0.0f, 0.0f, 0.0f};
    Math::Quaternion rotation = {0.0f, 0.0f, 0.0f, 1.0f};
    //Math::Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Math::Vector3 scale = {1.0f, 1.0f, 1.0f};
    
    Math::Matrix4 localTransform = Math::Matrix4::IDENTITY;
    Math::Matrix4 worldTransform = Math::Matrix4::IDENTITY;
    
    
    
    
    std::vector<TransformComponent*> children;
    
    
    
    void UpdateLocalTransform();
    void UpdateWorldTransform();
  
  
  public:
    [[nodiscard]] const Math::Matrix4& GetWorldTransform()const;
    [[nodiscard]] const Math::Matrix4& GetLocalTransform()const;
    
    [[nodiscard]] const Math::Vector3& GetPosition()const;
    
    //[[nodiscard]] const Math::Vector3& GetRotation()const;
    
    [[nodiscard]] const Math::Quaternion& GetRotation()const;
    
    [[nodiscard]] const Math::Vector3& GetScale()const;
    
    void SetPosition(const Math::Vector3& value);
    
    void SetPosition2D(const Math::Vector2& value);
    //void SetRotation(const Math::Vector3& value);
    void SetRotation(const Math::Quaternion& value);
    void SetRotation2D(float value);
    void SetScale2D(const Math::Vector2& value);
    void SetScale(const Math::Vector3& value);
    void Set2D(const Math::Vector2& positionValue, float rotationValue, const Math::Vector2& scaleValue);
    void Set(const Math::Vector3& positionValue, const Math::Quaternion& rotationValue, const Math::Vector3& scaleValue);
    void ApplyDeltaRotation(const Math::Vector3& rot);
    
    [[nodiscard]] bool HasParent()const;
    
    [[nodiscard]] bool HasChildren()const;
    
    bool RemoveChild(const TransformComponent* child);
    bool AddChild(TransformComponent* child);
    
    [[nodiscard]] const std::vector<TransformComponent*>& GetChildren()const;
    
    void SetParent(TransformComponent* parentValue);
    
    TransformComponent* GetParent();
    
    
    
    /*Entity* GetOwner()
    {
      return owner;
    }*/
    
    /*[[nodiscard]] Math::Matrix4 GetMatrix()const
    {
      Math::Quaternion rot = Math::Quaternion::Euler(rotation);
      Math::Matrix4 matrix = Math::Matrix4::Translate(Math::Matrix4::IDENTITY, position) * Math::Matrix4::Rotate(Math::Matrix4::IDENTITY, rot) * Math::Matrix4::Scale(Math::Matrix4::IDENTITY, scale);
      return matrix;
    }*/
    
    
    
    
  };
}