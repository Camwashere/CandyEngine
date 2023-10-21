#pragma once
#include <candy/app/Layer.hpp>

namespace Candy::Gum
{
  class GumContext;
}
namespace Candy
{
  class GumLayer : public Layer
  {
  private:
    Gum::GumContext* context;
    bool blockEvents=false;
  
  public:
    GumLayer(Gum::GumContext* gumContext);
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Events::Event& e)override;
    
    void BlockEvents(bool block);
    void Begin();
    void End();
    
    
    
    
  };
}