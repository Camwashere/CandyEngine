#pragma once
#include <candy/app/Layer.hpp>

namespace Candy
{
  class GumLayer : public Layer
  {
  private:
    
    bool blockEvents=false;
  
  public:
    GumLayer();
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Events::Event& e)override;
    
    void BlockEvents(bool block);
    void Begin();
    void End();
    
    
    
    
  };
}