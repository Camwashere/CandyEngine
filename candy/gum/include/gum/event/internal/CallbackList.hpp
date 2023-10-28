#pragma once
#include <functional>
#include <list>
#include <unordered_map>
namespace Candy::Gum::Internal
{
  template<typename FUNCTION_PROTOTYPE>
  class CallbackList
  {
  private:
    int handleCounter = 0;
    std::list<std::pair<int, FUNCTION_PROTOTYPE>> callbacks{};
    std::unordered_map<int, typename std::list<std::pair<int, FUNCTION_PROTOTYPE>>::iterator> map{};
    
    
  public:
    
    int AppendCallback(FUNCTION_PROTOTYPE func)
    {
      int handle = ++handleCounter;
      callbacks.push_back(std::make_pair(handle, func));
      map[handle] = std::prev(callbacks.end());
      return handle;
    }
    
    
    int PrependCallback(FUNCTION_PROTOTYPE func)
    {
      int handle = ++handleCounter;
      callbacks.push_front(std::make_pair(handle, func));
      map[handle] = callbacks.begin();
      return handle;
    }
    
    // Insert a callback at a specific position
    int InsertCallback(int position, FUNCTION_PROTOTYPE func)
    {
      int handle = ++handleCounter;
      auto iter = std::next(callbacks.begin(), position);
      map[handle] = callbacks.insert(iter, std::make_pair(handle, func));
      return handle;
    }
    
    // Remove a callback given its handle
    void RemoveCallback(int handle)
    {
      auto iter = map[handle];
      callbacks.erase(iter);
      map.erase(handle);
    }
    
    /// Call a single, specified callback
    void CallSingle(int handle)
    {
      auto iter = map[handle];
      iter->second();
    }
    
    /// Call all callbacks in the order they were inserted
    template<typename... ARGS>
    void Call(ARGS&&... args)
    {
      for(auto& pair : callbacks)
      {
        pair.second(std::forward<ARGS>(args)...);
      }
    }
    
    
    /// Call all callbacks in the reverse order they were inserted
    template<typename... ARGS>
    void CallReverse(ARGS&&... args)
    {
      for(auto iter = callbacks.rbegin(); iter != callbacks.rend(); ++iter)
      {
        iter->second(std::forward<ARGS>(args)...);
      }
    }
    
    
  };
}