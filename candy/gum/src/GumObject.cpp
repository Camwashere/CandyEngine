#include <gum/GumObject.hpp>
#include <gum/GumComponents.hpp>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  
  GumObject::GumObject()=default;
  GumObject::GumObject(entt::entity objectHandle, GumGraph* gumGraph) : handle(objectHandle), graph(gumGraph)
  {
  
  }
  GumObject::GumObject(const GumObject &other)=default;
  
  
  GumObject::operator bool()const
  {
    return handle!=entt::null;
  }
  GumObject::operator std::uint32_t()const
  {
    return (std::uint32_t)handle;
  }
  GumObject::operator entt::entity()const
  {
    return handle;
  }
  
  bool GumObject::operator==(const GumObject& other)const
  {
    return handle==other.handle && graph == other.graph;
  }
  bool GumObject::operator!=(const GumObject& other)const
  {
    return !(*this==other);
  }
  
  UUID GumObject::GetUUID()
  {
    CANDY_CORE_ASSERT(HasComponent<GumID>(), "GumObject does not have ID component");
    return GetComponent<GumID>().id;
  }
  std::string GumObject::GetTag()
  {
    CANDY_CORE_ASSERT(HasComponent<GumTag>(), "GumObject does not have tag component");
    return GetComponent<GumTag>().tag;
  }
  GumParent& GumObject::GetParent()
  {
    CANDY_CORE_ASSERT(HasParent(), "GumObject does not have parent");
    return GetComponent<GumParent>();
  }
  const GumParent& GumObject::GetParent()const
  {
    CANDY_CORE_ASSERT(HasParent(), "GumObject does not have parent");
    return GetComponent<GumParent>();
  }
  GumObject GumObject::GetParentObject()
  {
    CANDY_CORE_ASSERT(HasParent(), "GumObject does not have parent");
    return GumObject(GetParent().parent, graph);
  }
  
  GumObject GumObject::GetParentObject()const
  {
    CANDY_CORE_ASSERT(HasParent(), "GumObject does not have parent");
    return GumObject(GetParent().parent, graph);
  }
  bool GumObject::HasParent()const
  {
    return HasComponent<GumParent>();
  }
  bool GumObject::HasChildren()const
  {
    return HasComponent<GumChildren>();
  }
  bool GumObject::IsParent()const
  {
    return HasChildren();
  }
  bool GumObject::IsChild()const
  {
    return HasParent();
  }
  bool GumObject::IsRoot()const
  {
    return !HasParent();
  }
  
  bool GumObject::HasTransform()const
  {
    return HasComponent<GumTransform>();
  }
  
  bool GumObject::HasGraph()const
  {
    return graph!=nullptr;
  }
  bool GumObject::RemoveChild(const GumObject& child)
  {
    CANDY_PROFILE_FUNCTION();
    if (!HasChildren())
      return false;
    auto& children = GetChildren();
    auto it = std::find(children.children.begin(), children.children.end(), child);
    if (it==children.children.end())
      return false;
    children.children.erase(it);
    return true;
  }
  bool GumObject::AddChild(const GumObject& child)
  {
    CANDY_PROFILE_FUNCTION();
    if (!HasChildren())
      AddComponent<GumChildren>();
    auto& children = GetChildren();
    auto it = std::find(children.children.begin(), children.children.end(), child);
    if (it!=children.children.end())
      return false;
    
    
    children.children.push_back(child);
    return true;
  }
  
  void GumObject::SetParent(GumObject parent)
  {
    CANDY_PROFILE_FUNCTION();
    if (! HasParent())
    {
      AddComponent<GumParent>(parent);
      parent.AddChild(*this);
    }
    else
    {
      GumObject oldParent{GetParent().parent, graph};
      oldParent.RemoveChild(*this);
      GetParent().parent = parent;
      parent.AddChild(*this);
      
    }
  }
  
  GumChildren& GumObject::GetChildren()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasChildren(), "GumObject does not have children");
    return GetComponent<GumChildren>();
  }
  
  const GumChildren& GumObject::GetChildren()const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasChildren(), "GumObject does not have children");
    return GetComponent<GumChildren>();
  }
  
  GumTransform& GumObject::GetTransform()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasTransform(), "GumObject does not have transform");
    return GetComponent<GumTransform>();
  }
  const GumTransform& GumObject::GetTransform()const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasTransform(), "GumObject does not have transform");
    return GetComponent<GumTransform>();
  }
  void GumObject::SetName(const std::string& tag){GetComponent<GumTag>().tag=tag;}
  GumGraph* GumObject::GetGraph(){return graph;}
}