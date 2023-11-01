#include <gum/event/Event.hpp>
#include <utility>
#include <CandyPch.hpp>
#include <gum/base/Node.hpp>
namespace Candy::Gum
{
    
    Event::Event(EventType type) : type(std::move(type))
    {
      currentIter = eventDispatchChain.begin();
    }
  
  
  void Event::SetSource(Node* value)
  {
      CANDY_CORE_ASSERT(value);
      source = value;
      BuildChain();
  }
  void Event::BuildChain()
  {
      CANDY_CORE_ASSERT(source);
      eventDispatchChain.clear();
      eventDispatchChain.push_back(source);
      auto* parent = source->GetParent();
      while (parent)
      {
          eventDispatchChain.push_back(parent);
          parent = parent->GetParent();
      }
      CANDY_CORE_ASSERT(! eventDispatchChain.empty());
      currentIter = std::prev(eventDispatchChain.end());
      
  }
}