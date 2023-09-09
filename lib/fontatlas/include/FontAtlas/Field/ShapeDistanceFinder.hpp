
#pragma once

#include <vector>
#include "msdfVec2.hpp"
#include "EdgeSelectors.hpp"
#include "ContourCombiners.hpp"

namespace msdfgen {

/// Finds the distance between a point and a Shape. ContourCombiner dictates the distance metric and its data type.
  template <class ContourCombiner>
  class ShapeDistanceFinder {
  
  private:
    const Shape &shape;
    ContourCombiner contourCombiner;
    std::vector<typename ContourCombiner::EdgeSelectorType::EdgeCache> shapeEdgeCache;
  
  public:
    typedef typename ContourCombiner::DistanceType DistanceType;
    
    

    
    
    // Passed shape object must persist until the distance finder is destroyed!
    ShapeDistanceFinder(const Shape &shape) : shape(shape), contourCombiner(shape), shapeEdgeCache(shape.edgeCount()) { }
    
    
    /// Finds the distance from origin. Not thread-safe! Is fastest when subsequent queries are close together.
    DistanceType distance(const msdfVec2 &origin) {
      contourCombiner.reset(origin);
      
      typename ContourCombiner::EdgeSelectorType::EdgeCache *edgeCache = shapeEdgeCache.data();
      
      
      for (std::vector<Contour>::const_iterator contour = shape.contours.begin(); contour != shape.contours.end(); ++contour) {
        if (!contour->edges.empty()) {
          typename ContourCombiner::EdgeSelectorType &edgeSelector = contourCombiner.edgeSelector(int(contour-shape.contours.begin()));
          
          const EdgeSegment *prevEdge = contour->edges.size() >= 2 ? *(contour->edges.end()-2) : *contour->edges.begin();
          const EdgeSegment *curEdge = contour->edges.back();
          for (std::vector<EdgeHolder>::const_iterator edge = contour->edges.begin(); edge != contour->edges.end(); ++edge) {
            const EdgeSegment *nextEdge = *edge;
            edgeSelector.addEdge(*edgeCache++, prevEdge, curEdge, nextEdge);
            prevEdge = curEdge;
            curEdge = nextEdge;
          }
        }
      }
      
      return contourCombiner.distance();
    }
    
    /// Finds the distance between shape and origin. Does not allocate result cache used to optimize performance of multiple queries.
    static typename ShapeDistanceFinder<ContourCombiner>::DistanceType oneShotDistance(const Shape &shape, const msdfVec2 &origin) {
      ContourCombiner contourCombiner(shape);
      contourCombiner.reset(origin);
      
      for (std::vector<Contour>::const_iterator contour = shape.contours.begin(); contour != shape.contours.end(); ++contour) {
        if (!contour->edges.empty()) {
          typename ContourCombiner::EdgeSelectorType &edgeSelector = contourCombiner.edgeSelector(int(contour-shape.contours.begin()));
          
          const EdgeSegment *prevEdge = contour->edges.size() >= 2 ? *(contour->edges.end()-2) : *contour->edges.begin();
          const EdgeSegment *curEdge = contour->edges.back();
          for (std::vector<EdgeHolder>::const_iterator edge = contour->edges.begin(); edge != contour->edges.end(); ++edge) {
            const EdgeSegment *nextEdge = *edge;
            typename ContourCombiner::EdgeSelectorType::EdgeCache dummy;
            edgeSelector.addEdge(dummy, prevEdge, curEdge, nextEdge);
            prevEdge = curEdge;
            curEdge = nextEdge;
          }
        }
      }
      
      return contourCombiner.distance();
    }
  
  
    
  };
  
  typedef ShapeDistanceFinder<SimpleContourCombiner<TrueDistanceSelector> > SimpleTrueShapeDistanceFinder;
  
}

