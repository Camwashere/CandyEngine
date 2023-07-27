#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <ranges>

namespace Candy::Graphics
{
  void DeletionQueue::PushFunction(std::function<void()>&& function)
  {
    queue.push_back(std::move(function));
  }
  void DeletionQueue::Flush()
  {
    for (auto & f : std::ranges::reverse_view(queue))
    {
      f();
    }
    queue.clear();
  }

}