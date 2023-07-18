#include <candy/ecs/SystemScheduler.hpp>

namespace Candy::ECS
{
  SystemScheduler::SystemScheduler()
  {
  
  
  }
  
  SystemScheduler::~SystemScheduler()
  {
    Clear();
  }
  
  void SystemScheduler::AttachSystem(System* system)
  {
    if (availableSystemSlots.empty())
    {
      system->id = systems.size();
      systems.push_back(system);
    }
    else
    {
      system->id = availableSystemSlots.front();
      availableSystemSlots.pop();
      systems[system->id] = system;
      
      
    }
    
  }
  
  void SystemScheduler::Update()
  {
    Update(nullptr);
  }
  
  void SystemScheduler::Update(void* data)
  {
    
    for (std::uint32_t i=0; i<systems.size(); i++)
    {
      System* system = systems[i];
      
      if (system)
      {
        SystemState state = system->Update(data);
        
        switch(state)
        {
          case SystemState::NEEDS_STOP:
            system->Stop();
            RemoveSystem(i);
            break;
          case SystemState::STOPPED:
            RemoveSystem(i);
            break;
          default:
            break;
        }
      }
      
      
    }
    
  }
  void SystemScheduler::Clear()
  {
    for (std::uint32_t i=0; i<systems.size(); i++)
    {
      System* system = systems[i];
      
      if (system)
      {
        system->Stop();
        RemoveSystem(i);
      }
    }
    
    
  }
  
  void SystemScheduler::RemoveSystem(std::uint32_t slot)
  {
    availableSystemSlots.push(slot);
    delete systems[slot];
    systems[slot] = nullptr;
  }
  
  
}