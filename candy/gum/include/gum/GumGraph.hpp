#pragma once
#include "GumTypes.hpp"
#include "candy/event/Events.hpp"
#include <unordered_map>
#include <deque>
#include <queue>
namespace Candy::Gum
{
  class GumObject;
  
  class GumGraph
  {
  private:
    GumIDVector<SharedPtr<GumObject>> objects;
    std::queue<GumID> dirtyObjects;
    std::deque<GumID> availableIDs{};
    std::string name;
    
  private:
    [[nodiscard]] bool HasAvailableIDs()const;
    void DetachObjectData(const SharedPtr<GumObject>& object);
    [[nodiscard]] bool IsIDAssigned(GumID id)const;
    
    void Render();
    
  public:
    explicit GumGraph(std::string_view name);
    
  public:
    void Update();
    
    
  public:
    GumID AddObject(const SharedPtr<GumObject>& object);
    
    
    template<typename Derived, typename... Args>
    std::enable_if<std::is_base_of<GumObject, Derived>::value, WeakPtr<Derived>>
    AddObject(Args&&... args)
    {
      SharedPtr<Derived> object = MakeShared<Derived>(this, std::forward<Args>(args)...);
      AddObject(object);
      return std::static_pointer_cast<WeakPtr>(object);
    }
    
    bool RemoveObject(GumID id);
    [[nodiscard]] const GumObject* GetObject(GumID id)const;
    GumObject* GetObject(GumID id);
    
    
    friend class GumObject;
    
  
    
  
    
    
    
  
  
  };
  
 
}