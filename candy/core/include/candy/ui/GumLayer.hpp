#pragma once
#include <candy/app/Layer.hpp>

namespace Candy::Gum
{
  class Context;
}
namespace Candy
{
  class GumLayer : public Layer
  {
  private:
    Gum::Context* context;
    bool blockEvents=false;
  
  public:
    GumLayer(Gum::Context* gumContext);
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Events::Event& e)override;
    
    void BlockEvents(bool block);
    void Begin();
    void End();
    
    
    
    
  };
}