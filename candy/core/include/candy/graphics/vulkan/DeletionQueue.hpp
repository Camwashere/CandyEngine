#pragma once
#include <deque>
#include <functional>
namespace Candy::Graphics
{
  class DeletionQueue
  {
  private:
    std::deque<std::function<void()>> queue;
    
  public:
    void PushFunction(std::function<void()>&& function);
    void Flush();
  };
}