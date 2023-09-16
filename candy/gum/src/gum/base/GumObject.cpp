#include <gum/base/GumObject.hpp>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  Utils::IDManager<uint32_t> GumObject::idManager;
  
  GumObject::GumObject() : id(idManager.Assign()), position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f), parent(nullptr), depth(0)
  {
  }
  GumObject::GumObject(GumObject* parentObj) : id(idManager.Assign()), parent(parentObj), position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f), depth(parent->depth+1)
  {
    parentObj->children.push_back(this);
  }
  
  GumObject::~GumObject()
  {
    idManager.Free(id);
  }
  
  bool GumObject::operator==(const GumObject& other)const
  {
    return id==other.id;
  }
  bool GumObject::operator!=(const GumObject& other)const
  {
    return !(*this==other);
  }
  void GumObject::OnEvent(Events::Event& event)
  {
    if (propagateEvents)
    {
      for (auto child : children)
      {
        child->OnEvent(event);
      }
    }
  }
  void GumObject::SetPosition(const Math::Vector2 &pos)
  {
    position = pos;
  }
  
  void GumObject::SetPosition(float x, float y)
  {
    position.Set(x, y);
  }
  
  void GumObject::SetPosX(float x)
  {
    position.x = x;
  }
  
  void GumObject::SetPosY(float y)
  {
    position.y = y;
  }
  
  void GumObject::SetScale(const Math::Vector2 &value)
  {
    scale = value;
  }
  
  void GumObject::SetScale(float x, float y)
  {
    scale.Set(x, y);
  }
  
  void GumObject::SetWidth(float width)
  {
    scale.width = width;
  }
  
  void GumObject::SetHeight(float height)
  {
    scale.height = height;
  }
  
  void GumObject::SetRotation(float value)
  {
    rotation = value;
  }
  void GumObject::SetShape(GumShape value)
  {
    shape = value;
  }
  void GumObject::BlockEvents()
  {
    propagateEvents = false;
  }
  void GumObject::Hide()
  {
    isVisible=false;
  }
  void GumObject::Show()
  {
    isVisible=true;
  }
  uint32_t GumObject::GetID() const
  {
    return id;
  }
  
  float GumObject::GetPosX() const
  {
    return position.x;
  }
  
  float GumObject::GetPosY() const
  {
    return position.y;
  }
  
  float GumObject::GetWidth() const
  {
    return scale.width;
  }
  
  float GumObject::GetHeight() const
  {
    return scale.height;
  }
  bool GumObject::HasShape()const
  {
    return shape!=0;
  }
  Math::Vector2 GumObject::GetPosition() const
  {
    return position;
  }
  
  Math::Vector2 GumObject::GetScale() const
  {
    return scale;
  }
  
  float GumObject::GetRotation() const
  {
    return rotation;
  }
  
  bool GumObject::IsRoot()const
  {
    return parent==nullptr;
  }
  GumShape GumObject::GetShape()const
  {
    return shape;
  }
  bool GumObject::IsVisible()const
  {
    return isVisible;
  }
  bool GumObject::HasChildren()const
  {
    return children.size()>0;
  }
  GumObject& GumObject::GetParent()
  {
    CANDY_CORE_ASSERT(parent!=nullptr, "GumObject::GetParent() - Parent is nullptr!");
    return *parent;
  }
  const GumObject& GumObject::GetParent()const
  {
    CANDY_CORE_ASSERT(parent!=nullptr, "GumObject::GetParent() - Parent is nullptr!");
    return *parent;
  }
  GumObject& GumObject::GetChild(uint32_t index)
  {
    CANDY_CORE_ASSERT(index<children.size(), "GumObject::GetChild() - Index out of range!");
    return *children[index];
  }
  const GumObject& GumObject::GetChild(uint32_t index)const
  {
    CANDY_CORE_ASSERT(index<children.size(), "GumObject::GetChild() - Index out of range!");
    return *children[index];
  }
  std::vector<GumObject*>& GumObject::GetChildren()
  {
    return children;
  }
  const std::vector<GumObject*>& GumObject::GetChildren()const
  {
    return children;
  }
}