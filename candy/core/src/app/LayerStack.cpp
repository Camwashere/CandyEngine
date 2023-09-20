#include <candy/app/LayerStack.hpp>
#include <algorithm>
#include "CandyPch.hpp"
namespace Candy{
  /*LayerStack::~LayerStack()
  {
    for (Layer* layer : layers)
    {
      //layer->OnDetach();
      delete layer;
    }
  }*/
  
  void LayerStack::PushLayer(Layer* layer)
  {
    CANDY_PROFILE_FUNCTION();
    layers.emplace(layers.begin() + layerInsertIndex, layer);
    layerInsertIndex++;
  }
  
  void LayerStack::PushOverlay(Layer* overlay)
  {
    CANDY_PROFILE_FUNCTION();
    layers.emplace_back(overlay);
  }
  
  void LayerStack::PopLayer(Layer* layer)
  {
    CANDY_PROFILE_FUNCTION();
    auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
    if (it != layers.begin() + layerInsertIndex)
    {
      layer->OnDetach();
      layers.erase(it);
      layerInsertIndex--;
    }
  }
  
  void LayerStack::PopOverlay(Layer* overlay)
  {
    CANDY_PROFILE_FUNCTION();
    auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
    if (it != layers.end())
    {
      overlay->OnDetach();
      layers.erase(it);
    }
  }
}