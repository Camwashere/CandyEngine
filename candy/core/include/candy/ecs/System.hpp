#pragma once
#include <cstdint>
namespace Candy::ECS
{
  enum class SystemState : std::uint8_t
  {
    NONE=0,
    RUNNING,
    PAUSED,
    NEEDS_STOP,
    STOPPED
  };
  enum class SystemError : std::uint8_t
  {
    NONE=0,
    SUCCESS,
    FAILURE,
  };
  class System
  {
  private:
    SystemState state=SystemState::NONE;
    SystemError error=SystemError::NONE;
    std::uint32_t id=0;
  
  private:
    virtual void OnStart(){}
    virtual void OnUpdate(void* data){}
    virtual void OnStop(){}
  
  protected:
    void Succeed() noexcept;
    void Fail() noexcept;
    void Pause() noexcept;
    void Unpause() noexcept;
  
  public:
    virtual ~System()noexcept=default;
    
    void Abort(bool immediately=false);
    [[nodiscard]] bool IsAlive()const noexcept;
    [[nodiscard]] bool IsFinished()const noexcept;
    [[nodiscard]] bool IsPaused()const noexcept;
    [[nodiscard]] bool IsRejected()const noexcept;
    
    void Start();
    SystemState Update(void* data);
    void Stop();
  
  private:
    friend class SystemScheduler;
    
    
    
    
  };
}