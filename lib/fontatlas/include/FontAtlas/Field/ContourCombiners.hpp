
#pragma once
#include "msdfVec2.hpp"
#include "Shape.hpp"
#include "EdgeSelectors.hpp"

namespace msdfgen {

/// Simply selects the nearest contour.
  template <class EdgeSelector>
  class SimpleContourCombiner {
  
  public:
    typedef EdgeSelector EdgeSelectorType;
    typedef typename EdgeSelector::DistanceType DistanceType;
    
    explicit SimpleContourCombiner(const Shape &shape);
    void reset(const msdfVec2 &p);
    EdgeSelector & edgeSelector(int i);
    DistanceType distance() const;
  
  private:
    EdgeSelector shapeEdgeSelector;
    
  };

/// Selects the nearest contour that actually forms a border between filled and unfilled area.
  template <class EdgeSelector>
  class OverlappingContourCombiner {
  
  public:
    typedef EdgeSelector EdgeSelectorType;
    typedef typename EdgeSelector::DistanceType DistanceType;
    
    explicit OverlappingContourCombiner(const Shape &shape);
    void reset(const msdfVec2 &p);
    EdgeSelector & edgeSelector(int i);
    DistanceType distance() const;
  
  private:
    msdfVec2 p;
    std::vector<int> windings;
    std::vector<EdgeSelector> edgeSelectors;
    
  };
  
}
