#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/utils/IDManager.hpp>
#include <candy/event/Events.hpp>
#include "GumShape.hpp"

namespace Candy::Gum
{
class GumObject : public Events::IEventListener
  {
  private:
    const uint32_t id;
    
  protected:
  GumObject* parent;
  Math::Vector2 position;
  Math::Vector2 scale;
  float rotation;
  Math::Matrix4 localTransform;
  Math::Matrix4 worldTransform;
  uint32_t depth;
  GumShape shape;
  std::vector<GumObject*> children;
  bool propagateEvents=true;
  bool isVisible=true;
  
  private:
    static Utils::IDManager<uint32_t> idManager;
    
  public:
    GumObject();
    explicit GumObject(GumObject* parent);
    ~GumObject();
    
  
  bool operator==(const GumObject& other)const;
  bool operator!=(const GumObject& other)const;
  
  public:
    virtual void OnEvent(Events::Event& event)override;
  public:
    void SetPosition(const Math::Vector2& position);
    void SetPosition(float x, float y);
    void SetPosX(float x);
    void SetPosY(float y);
    void SetScale(const Math::Vector2& scale);
    void SetScale(float x, float y);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetRotation(float value);
    void SetShape(GumShape value);
    void BlockEvents();
    void Hide();
    void Show();
    
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] float GetPosX()const;
    [[nodiscard]] float GetPosY()const;
    [[nodiscard]] float GetWidth()const;
    [[nodiscard]] float GetHeight()const;
    [[nodiscard]] bool HasShape()const;
    [[nodiscard]] Math::Vector2 GetPosition()const;
    [[nodiscard]] Math::Vector2 GetScale()const;
    [[nodiscard]] float GetRotation()const;
    [[nodiscard]] bool IsRoot()const;
    [[nodiscard]] GumShape GetShape()const;
    [[nodiscard]] bool IsVisible()const;
    [[nodiscard]] bool HasChildren()const;
    GumObject& GetParent();
    [[nodiscard]] const GumObject& GetParent()const;
    GumObject& GetChild(uint32_t index);
    [[nodiscard]] const GumObject& GetChild(uint32_t index)const;
    std::vector<GumObject*>& GetChildren();
    [[nodiscard]] const std::vector<GumObject*>& GetChildren()const;
  };
}