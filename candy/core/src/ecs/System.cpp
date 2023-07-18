#include <candy/ecs/System.hpp>
#include <CandyPch.hpp>
namespace Candy::ECS
{
  
  void System::Succeed() noexcept
  {
    state = SystemState::STOPPED;
  }
  
  void System::Fail() noexcept
  {
    state = SystemState::NEEDS_STOP;
    error = SystemError::FAILURE;
  }
  
  void System::Pause() noexcept
  {
    state = SystemState::PAUSED;
  }
  
  void System::Unpause() noexcept
  {
    state = SystemState::RUNNING;
  }
  
  void System::Abort(const bool immediately)
  {
    if (immediately)
    {
      state = SystemState::STOPPED;
    }
    else
    {
      state = SystemState::NEEDS_STOP;
    }
    error = SystemError::FAILURE;
  }
  
  bool System::IsAlive() const noexcept
  {
    switch(state)
    {
      case SystemState::STOPPED:
        return false;
      default:
        return true;
    }
  }
  
  bool System::IsFinished() const noexcept
  {
    return state == SystemState::STOPPED;
  }
  
  bool System::IsPaused() const noexcept
  {
    return state == SystemState::PAUSED;
  }
  
  bool System::IsRejected() const noexcept
  {
    return error == SystemError::FAILURE;
  }
  
  void System::Start()
  {
    CANDY_CORE_ASSERT(state == SystemState::NONE, "System is already started");
    state = SystemState::RUNNING;
    OnStart();
  }
  
  SystemState System::Update(void* data)
  {
    switch(state)
    {
      case SystemState::NONE:
        Start();
        break;
      case SystemState::RUNNING:
      case SystemState::NEEDS_STOP:
        OnUpdate(data);
        break;
      default:
        break;
    }
    return state;
  }
  
  void System::Stop()
  {
    CANDY_CORE_ASSERT(state != SystemState::STOPPED, "System is already stopped");
    state = SystemState::STOPPED;
    OnStop();
  }
}