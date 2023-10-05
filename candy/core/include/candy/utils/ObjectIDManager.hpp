#pragma once
#include <candy/base/CandyConcepts.hpp>
#include <vector>
#include <deque>
#include <cstdint>
#include <algorithm>
#include <candy/base/Base.hpp>
#include <candy/base/Assert.hpp>
#include <candy/utils/ObjectIDTypes.hpp>
namespace Candy::Utils
{
  
  
  template<typename T, Numeric INDEX>
  class ObjectIDManagerShared : ObjectIDAccess<INDEX>
  {
    
    static_assert(std::is_base_of<ObjectIdentifiable<INDEX>, T>::value, "T must be derived from ObjectIdentifiable");
  private:
    std::deque<INDEX> availableIDs{};
    std::vector<SharedPtr<T>> objects;
  
  
  public:
    [[nodiscard]] INDEX GetCurrentMax()const{return objects.size();}
    [[nodiscard]] size_t GetAvailableCount()const{return availableIDs.size();}
    [[nodiscard]] bool HasAvailable()const{return !availableIDs.empty();}
    
    auto begin()
    {
      return objects.begin();
    }
    auto end()
    {
      return objects.end();
    }
    auto cbegin()const
    {
      return objects.cbegin();
    }
    auto cend()const
    {
      return objects.cend();
    }
    auto rbegin()
    {
      return objects.rbegin();
    }
    auto rend()
    {
      return objects.rend();
    }
    
    T& GetObject(INDEX id)
    {
      
      CANDY_CORE_ASSERT(HasObject(id));
      return *objects[id];
    }
    
    const T& GetObject(INDEX id)const
    {
      CANDY_CORE_ASSERT(HasObject(id));
      return *objects[id];
    }
    
    INDEX AddObject(const SharedPtr<T>& object)
    {
      if(HasAvailable())
      {
        INDEX id=availableIDs.front();
        availableIDs.pop_front();
        objects[id] = object;
        this->SetID(*objects[id], id);
        return id;
      }
      else
      {
        INDEX id = objects.size();
        objects.push_back(object);
        this->SetID(*objects[objects.size()-1], id);
        return id;
      }
    }
    
    template<class Derived, typename...Args>
    std::enable_if<std::is_base_of<T, Derived>::value, SharedPtr<Derived>>
    AddObject(Args&&... args)
    {
      SharedPtr<Derived> object = CreateSharedPtr<Derived>(std::forward<Args>(args)...);
      
      
      if(HasAvailable())
      {
        INDEX id=availableIDs.front();
        availableIDs.pop_front();
        objects[id] = object;
        this->SetID(objects[id], id);
        return object;
      }
      else
      {
        INDEX id = objects.size();
        objects.push_back(object);
        this->SetID(objects[objects.size()-1], id);
        return object;
      }
      
      
    }
    
    
    
    bool Free(INDEX id)
    {
      if (id < objects.size())
      {
        if(id==objects.size()-1)
        {
          objects.pop_back();
          
        }
        else
        {
          objects[id].reset();
          availableIDs.push_back(id);
        }
        return true;
      }
      else
      {
        return false;
      }
      
      
    }
    
    
    void Reset()
    {
      
      availableIDs.clear();
      objects.clear();
    }
    
    
    [[nodiscard]] bool HasObject(INDEX id)const
    {
      if (id < objects.size() && id >= 0)
      {
        return std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end();
      }
      return false;
    }
    
    
  };
  
  template<typename T, Numeric INDEX>
  class ObjectIDManagerUnique : ObjectIDAccess<INDEX>
  {
    
    static_assert(std::is_base_of<ObjectIdentifiable<INDEX>, T>::value, "T must be derived from ObjectIdentifiable");
  private:
    std::deque<INDEX> availableIDs{};
    std::vector<UniquePtr<T>> objects;
    
  
  public:
    [[nodiscard]] INDEX GetCurrentMax()const{return objects.size();}
    [[nodiscard]] size_t GetAvailableCount()const{return availableIDs.size();}
    [[nodiscard]] bool HasAvailable()const{return !availableIDs.empty();}
    
    T& GetObject(INDEX id)
    {
      CANDY_CORE_ASSERT(HasObject(id));
      return *objects[id];
    }
    
    const T& GetObject(INDEX id)const
    {
      CANDY_CORE_ASSERT(HasObject(id));
      return *objects[id];
    }
    
    INDEX AddObject(UniquePtr<T>&& object)
    {
      if(HasAvailable())
      {
        INDEX id=availableIDs.front();
        availableIDs.pop_front();
        objects[id] = std::move(object);
        this->SetID(*objects[id], id);
        return id;
      }
      else
      {
        INDEX id = objects.size();
        objects.push_back(std::move(object));
        this->SetID(*objects[objects.size()-1], id);
        return id;
      }
    }
    
    template<class Derived, typename...Args>
    std::enable_if<std::is_base_of<T, Derived>::value, Derived*>
    AddObject(Args&&... args)
    {
      UniquePtr<T> object = CreateUniquePtr<Derived>(std::forward<Args>(args)...);
      
      // Cast from T* to Derived*
      Derived* derivedPtr = static_cast<Derived*>(object.get());
      if(HasAvailable())
      {
        INDEX id=availableIDs.front();
        availableIDs.pop_front();
        objects[id] = std::move(object);
        this->SetID(objects[id], id);
        return derivedPtr;
      }
      else
      {
        INDEX id = objects.size();
        objects.push_back(std::move(object));
        this->SetID(objects[objects.size()-1], id);
        return derivedPtr;
      }
      
      
    }
    
    
    
    bool Free(INDEX id)
    {
      if (id < objects.size())
      {
        if(id==objects.size()-1)
        {
          objects.pop_back();
          
        }
        else
        {
          objects[id].reset();
          availableIDs.push_back(id);
        }
        return true;
      }
      else
      {
        return false;
      }
      
      
    }
    
    
    void Reset()
    {
      
      availableIDs.clear();
      objects.clear();
    }
    
    
    [[nodiscard]] bool HasObject(INDEX id)const
    {
      if (id < objects.size() && id >= 0)
      {
        return std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end();
      }
      return false;
    }
    
    
  };
}