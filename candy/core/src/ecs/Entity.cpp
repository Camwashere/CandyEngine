#include <candy/ecs/Entity.hpp>
#include <candy/ecs/BaseComponents.hpp>
namespace Candy::ECS
{
  
  Entity::Entity()=default;
  Entity::Entity(entt::entity entityID, Scene* parentScene) : handle(entityID), scene(parentScene){}
  Entity::Entity(const Entity &other)=default;
  
  
  Entity::operator bool()const{return handle!=entt::null;}
  Entity::operator std::uint32_t()const{return (std::uint32_t)handle;}
  Entity::operator entt::entity()const{return handle;}
  
  bool Entity::operator==(const Entity& other)const
  {
    return handle==other.handle && scene==other.scene;
  }
  bool Entity::operator!=(const Entity& other)const
  {
    return !(*this==other);
  }
  
  UUID Entity::GetUUID()
  {
    CANDY_CORE_ASSERT(HasComponent<IDComponent>(), "Entity does not have ID component");
    return GetComponent<IDComponent>().id;
  }
  std::string Entity::GetTag()
  {
    CANDY_CORE_ASSERT(HasComponent<TagComponent>(), "Entity does not have tag component");
    return GetComponent<TagComponent>().tag;
  }
  ParentComponent& Entity::GetParent()
  {
    CANDY_CORE_ASSERT(HasParent(), "Entity does not have parent");
    return GetComponent<ParentComponent>();
  }
  const ParentComponent& Entity::GetParent()const
  {
    CANDY_CORE_ASSERT(HasParent(), "Entity does not have parent");
    return GetComponent<ParentComponent>();
  }
  Entity Entity::GetParentEntity()
  {
    CANDY_CORE_ASSERT(HasParent(), "Entity does not have parent");
    return Entity(GetParent().parent, scene);
  }
  
  Entity Entity::GetParentEntity()const
  {
    CANDY_CORE_ASSERT(HasParent(), "Entity does not have parent");
    return Entity(GetParent().parent, scene);
  }
  bool Entity::HasParent()const
  {
    return HasComponent<ParentComponent>();
  }
  bool Entity::HasChildren()const
  {
    return HasComponent<ChildrenComponent>();
  }
  bool Entity::IsParent()const
  {
    return HasChildren();
  }
  bool Entity::IsChild()const
  {
    return HasParent();
  }
  bool Entity::IsRoot()const
  {
    return !HasParent();
  }
  
  bool Entity::HasScene()const
  {
    return scene!=nullptr;
  }
  bool Entity::RemoveChild(const Entity& child)
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
  bool Entity::AddChild(const Entity& child)
  {
    CANDY_PROFILE_FUNCTION();
    if (!HasChildren())
      AddComponent<ChildrenComponent>();
    auto& children = GetChildren();
    auto it = std::find(children.children.begin(), children.children.end(), child);
    if (it!=children.children.end())
      return false;
    
    
    children.children.push_back(child);
    return true;
  }
  
  void Entity::SetParent(Entity parent)
  {
    CANDY_PROFILE_FUNCTION();
    if (! HasParent())
    {
      AddComponent<ParentComponent>(parent);
      parent.AddChild(*this);
    }
    else
    {
      Entity oldParent{GetParent().parent, scene};
      oldParent.RemoveChild(*this);
      GetParent().parent = parent;
      parent.AddChild(*this);
      
    }
  }
  
  ChildrenComponent& Entity::GetChildren()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasChildren(), "Entity does not have children");
    return GetComponent<ChildrenComponent>();
  }
  
  const ChildrenComponent& Entity::GetChildren()const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(HasChildren(), "Entity does not have children");
    return GetComponent<ChildrenComponent>();
  }
  bool Entity::Is2D()const
  {
    CANDY_PROFILE_FUNCTION();
    return HasComponent<SpriteRendererComponent>() || HasComponent<CircleRendererComponent>() || HasComponent<LineRendererComponent>() || HasComponent<TextRendererComponent>();
  }
  TransformComponent& Entity::GetTransform(){return GetComponent<TransformComponent>();}
  void Entity::SetName(const std::string& tag){GetComponent<TagComponent>().tag=tag;}
  Scene* Entity::GetScene(){return scene;}
}