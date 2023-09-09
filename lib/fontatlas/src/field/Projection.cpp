
#include "FontAtlas/Field/Projection.hpp"

namespace msdfgen {
  
  Projection::Projection() : scale(1), translate(0) { }
  
  Projection::Projection(const msdfVec2 &scale, const msdfVec2 &translate) : scale(scale), translate(translate) { }
  
  Point2 Projection::project(const Point2 &coord) const {
    return scale*(coord+translate);
  }
  
  Point2 Projection::unproject(const Point2 &coord) const {
    return coord/scale-translate;
  }
  
  msdfVec2 Projection::projectVector(const msdfVec2 &vector) const {
    return scale*vector;
  }
  
  msdfVec2 Projection::unprojectVector(const msdfVec2 &vector) const {
    return vector/scale;
  }
  
  float Projection::projectX(float x) const {
    return scale.x*(x+translate.x);
  }
  
  float Projection::projectY(float y) const {
    return scale.y*(y+translate.y);
  }
  
  float Projection::unprojectX(float x) const {
    return x/scale.x-translate.x;
  }
  
  float Projection::unprojectY(float y) const {
    return y/scale.y-translate.y;
  }
  
}
