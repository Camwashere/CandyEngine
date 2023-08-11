#pragma once
#include "GumObject.hpp"
#include <unordered_map>
namespace Candy::Gum
{
  
  class GumTree
  {
  private:
    std::unordered_map<uint32_t, GumObject*> objectMap;
    GumObject* root;
    
  public:
    GumTree();
    ~GumTree();
    
  public:
    GumObject& GetRoot();
    
  
  };
}