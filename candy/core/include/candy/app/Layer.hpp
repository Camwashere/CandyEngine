#pragma once
#include <candy/event/Event.hpp>
#include <utility>

namespace Candy
{
  class Layer
  {
  protected:
    bool isVisible;
    std::string name;
  
  public:
    explicit Layer(std::string  layerName="Layer", bool visible=true) : name(std::move(layerName)), isVisible(visible){}
    virtual ~Layer()=default;
    
    [[nodiscard]] inline bool IsVisible()const{return isVisible;}
    inline void SetVisible(bool visible) { isVisible = visible; }
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent(Events::Event& event){}
    virtual void OnUpdate(){}
    virtual void OnRenderGum(){}
    virtual void OnRenderUI(){}
    
    [[nodiscard]] const std::string& GetName()const{return name;}
    
  };
}