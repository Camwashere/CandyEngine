
#pragma once

#include "msdfVec2.hpp"

namespace msdfgen {

/// A transformation from shape coordinates to pixel coordinates.
  class Projection {
  
  public:
    Projection();
    Projection(const msdfVec2 &scale, const msdfVec2 &translate);
    /// Converts the shape coordinate to pixel coordinate.
    msdfVec2 project(const msdfVec2 &coord) const;
    /// Converts the pixel coordinate to shape coordinate.
    msdfVec2 unproject(const msdfVec2 &coord) const;
    /// Converts the vector to pixel coordinate space.
    msdfVec2 projectVector(const msdfVec2 &vector) const;
    /// Converts the vector from pixel coordinate space.
    msdfVec2 unprojectVector(const msdfVec2 &vector) const;
    /// Converts the X-coordinate from shape to pixel coordinate space.
    float projectX(float x) const;
    /// Converts the Y-coordinate from shape to pixel coordinate space.
    float projectY(float y) const;
    /// Converts the X-coordinate from pixel to shape coordinate space.
    float unprojectX(float x) const;
    /// Converts the Y-coordinate from pixel to shape coordinate space.
    float unprojectY(float y) const;
  
  private:
    msdfVec2 scale;
    msdfVec2 translate;
    
  };
  
}
