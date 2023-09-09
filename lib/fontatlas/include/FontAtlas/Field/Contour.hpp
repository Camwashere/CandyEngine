
#pragma once

#include <vector>
#include "EdgeHolder.hpp"

namespace msdfgen {

/// A single closed contour of a shape.
  class Contour {
  
  public:
    /// The sequence of edges that make up the contour.
    std::vector<EdgeHolder> edges;
    
    /// Adds an edge to the contour.
    void AddEdge(const EdgeHolder &edge);

    void AddEdge(EdgeHolder &&edge);

    /// Creates a new edge in the contour and returns its reference.
    EdgeHolder & AddEdge();
    /// Adjusts the bounding box to fit the contour.
    void Bound(float &l, float &b, float &r, float &t) const;
    /// Adjusts the bounding box to fit the contour border's mitered corners.
    void BoundMiters(float &l, float &b, float &r, float &t, float border, float miterLimit, int polarity) const;
    /// Computes the winding of the contour. Returns 1 if positive, -1 if negative.
    [[nodiscard]] int Winding() const;
    /// Reverses the sequence of edges on the contour.
    void Reverse();
    
  };
  
}
