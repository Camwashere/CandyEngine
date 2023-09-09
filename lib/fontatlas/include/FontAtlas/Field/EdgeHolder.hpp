
#pragma once
#include "msdfVec2.hpp"
#include "EdgeSegments.hpp"

namespace msdfgen {

/// Container for a single edge of dynamic type.
  class EdgeHolder {
  
  public:
    /// Swaps the edges held by a and b.
    static void swap(EdgeHolder &a, EdgeHolder &b);
    
    EdgeHolder();
    EdgeHolder(EdgeSegment *segment);
    EdgeHolder(msdfVec2 p0, msdfVec2 p1, EdgeColor edgeColor = WHITE);
    EdgeHolder(msdfVec2 p0, msdfVec2 p1, msdfVec2 p2, EdgeColor edgeColor = WHITE);
    EdgeHolder(msdfVec2 p0, msdfVec2 p1, msdfVec2 p2, msdfVec2 p3, EdgeColor edgeColor = WHITE);
    EdgeHolder(const EdgeHolder &orig);

    EdgeHolder(EdgeHolder &&orig);

    ~EdgeHolder();
    EdgeHolder & operator=(const EdgeHolder &orig);
    EdgeHolder & operator=(EdgeHolder &&orig);

    EdgeSegment & operator*();
    const EdgeSegment & operator*() const;
    EdgeSegment * operator->();
    const EdgeSegment * operator->() const;
    operator EdgeSegment *();
    operator const EdgeSegment *() const;
  
  private:
    EdgeSegment *edgeSegment;
    
  };
  
}
