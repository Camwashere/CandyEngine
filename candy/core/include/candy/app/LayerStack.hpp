#pragma once
#include "Layer.hpp"
#include <vector>
namespace Candy
{
  class LayerStack
  {
  private:
    std::vector<Layer*> layers;
    unsigned int layerInsertIndex=0;
  
  public:
    LayerStack()=default;
    ~LayerStack()=default;
    
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);
    
    std::vector<Layer*>::iterator begin() { return layers.begin(); }
    std::vector<Layer*>::iterator end() { return layers.end(); }
    std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
    std::vector<Layer*>::reverse_iterator rend() { return layers.rend(); }
    
    [[nodiscard]] std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
    [[nodiscard]] std::vector<Layer*>::const_iterator end()	const { return layers.end(); }
    [[nodiscard]] std::vector<Layer*>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
    [[nodiscard]] std::vector<Layer*>::const_reverse_iterator rend() const { return layers.rend(); }
  };
}