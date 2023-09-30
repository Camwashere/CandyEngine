#pragma once
#include <candy/event/Events.hpp>
#include "GumGraph.hpp"
namespace Candy::Gum
{
  class GumContext
  {
  private:
    bool blockEvents=false;
    GumGraph graph;
  
  
  public:
    GumContext();
    ~GumContext();
    
  public:
    void OnEvent(Events::Event& event);
  };
  
}