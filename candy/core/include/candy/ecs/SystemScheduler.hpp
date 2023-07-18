#pragma once
#include <stack>
#include <queue>
#include "System.hpp"
namespace Candy::ECS
{
  class SystemScheduler
  {
  private:
    std::vector<System*> systems;
    std::queue<std::uint32_t> availableSystemSlots;
  
  private:
    void RemoveSystem(std::uint32_t slot);
  
  
  public:
    SystemScheduler();
    ~SystemScheduler();
  
  public:
    void AttachSystem(System* system);
    
    void Update();
    void Update(void* data);
    
    void Clear();
  };
}