#pragma once
#include <candy/base/CandyConcepts.hpp>
#include <vector>
#include <deque>
#include <cstdint>
#include <algorithm>
namespace Candy::Utils
{
  template<Numeric T, T START_ID=0>
  class IDManager
  {
  private:
    T currentMax=START_ID;
    std::deque<T> availableIDs{};
    
  public:
    [[nodiscard]] T GetCurrentMax()const{return currentMax;}
    [[nodiscard]] size_t GetAvailableCount()const{return availableIDs.size();}
    [[nodiscard]] bool HasAvailable()const{return !availableIDs.empty();}
    
    
    
    T Assign()
    {
      if(HasAvailable())
      {
        T id=availableIDs.front();
        availableIDs.pop_front();
        return id;
      }
      else
      {
        return currentMax++;
      }
    }
    
    void Free(T id)
    {
      if(id==currentMax)
      {
        --currentMax;
      }
      else
      {
        availableIDs.push_back(id);
      }
    }
    
    
    void Reset()
    {
      currentMax=START_ID;
      availableIDs.clear();
    }
    
    
    [[nodiscard]] bool IsAssigned(T id)const
    {
      if (id < currentMax && id >= START_ID)
      {
        return std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end();
      }
      return false;
    }
    
    
  };
}