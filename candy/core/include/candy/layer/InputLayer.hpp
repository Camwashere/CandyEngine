#pragma once
#include <candy/app/Layer.hpp>
namespace Candy
{
  class InputLayer : public Layer
  {
  public:
    void OnAttach()override;
    void OnDetach()override;
    void OnEvent(Events::Event& event) {}
    void OnUpdate() {}
    void OnRenderUI() {}
  };
}