#pragma once
#include <string>
#include <candy/base/UUID.hpp>
#include <candy/math/geometry/Bounds2D.hpp>
#include "GumTransform.hpp"
#include "GumObject.hpp"

namespace Candy::Gum
{
  struct GumTag
  {
    std::string tag;
  };
  
  struct GumID
  {
    UUID id;
  };
  
  struct GumParent
  {
    GumObject parent;
    
    explicit GumParent(const GumObject& parentObject) : parent(parentObject){}
  };
  
  struct GumChildren
  {
    std::vector<GumObject> children;
    
    [[nodiscard]] bool Empty()const{return children.empty();}
    [[nodiscard]] size_t Size()const{return children.size();}
  };
  
  
  
  template<typename... Component>
  struct GumComponentGroup
  {
  };
  
  using AllGumComponents = GumComponentGroup<GumTag, GumID, GumParent, GumChildren, GumTransform>;
}