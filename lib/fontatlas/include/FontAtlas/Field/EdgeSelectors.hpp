
#pragma once

#include "msdfVec2.hpp"
#include "SignedDistance.hpp"
#include "EdgeSegments.hpp"

namespace msdfgen {
  
  struct MultiDistance {
    float r, g, b;
  };
  struct MultiAndTrueDistance : MultiDistance {
    float a;
  };

/// Selects the nearest edge by its true distance.
  class TrueDistanceSelector {
  
  public:
    typedef float DistanceType;
    
    struct EdgeCache {
      msdfVec2 point;
      float absDistance;
      
      EdgeCache();
    };
    
    void reset(const msdfVec2 &p);
    void addEdge(EdgeCache &cache, const EdgeSegment *prevEdge, const EdgeSegment *edge, const EdgeSegment *nextEdge);
    void merge(const TrueDistanceSelector &other);
    DistanceType distance() const;
  
  private:
    msdfVec2 p;
    SignedDistance minDistance;
    
  };
  
  class PseudoDistanceSelectorBase {
  
  public:
    struct EdgeCache {
      msdfVec2 point;
      float absDistance;
      float aDomainDistance, bDomainDistance;
      float aPseudoDistance, bPseudoDistance;
      
      EdgeCache();
    };
    
    static bool getPseudoDistance(float &distance, const msdfVec2 &ep, const msdfVec2 &edgeDir);
    
    PseudoDistanceSelectorBase();
    void reset(float delta);
    bool isEdgeRelevant(const EdgeCache &cache, const EdgeSegment *edge, const msdfVec2 &p) const;
    void addEdgeTrueDistance(const EdgeSegment *edge, const SignedDistance &distance, float param);
    void addEdgePseudoDistance(float distance);
    void merge(const PseudoDistanceSelectorBase &other);
    float computeDistance(const msdfVec2 &p) const;
    SignedDistance trueDistance() const;
  
  private:
    SignedDistance minTrueDistance;
    float minNegativePseudoDistance;
    float minPositivePseudoDistance;
    const EdgeSegment *nearEdge;
    float nearEdgeParam;
    
  };

/// Selects the nearest edge by its pseudo-distance.
  class PseudoDistanceSelector : public PseudoDistanceSelectorBase {
  
  public:
    typedef float DistanceType;
    
    void reset(const msdfVec2 &p);
    void addEdge(EdgeCache &cache, const EdgeSegment *prevEdge, const EdgeSegment *edge, const EdgeSegment *nextEdge);
    DistanceType distance() const;
  
  private:
    msdfVec2 p;
    
  };

/// Selects the nearest edge for each of the three channels by its pseudo-distance.
  class MultiDistanceSelector {
  
  public:
    typedef MultiDistance DistanceType;
    typedef PseudoDistanceSelectorBase::EdgeCache EdgeCache;
    
    void reset(const msdfVec2 &p);
    void addEdge(EdgeCache &cache, const EdgeSegment *prevEdge, const EdgeSegment *edge, const EdgeSegment *nextEdge);
    void merge(const MultiDistanceSelector &other);
    DistanceType distance() const;
    SignedDistance trueDistance() const;
  
  private:
    msdfVec2 p;
    PseudoDistanceSelectorBase r, g, b;
    
  };

/// Selects the nearest edge for each of the three color channels by its pseudo-distance and by true distance for the alpha channel.
  class MultiAndTrueDistanceSelector : public MultiDistanceSelector {
  
  public:
    typedef MultiAndTrueDistance DistanceType;
    
    DistanceType distance() const;
    
  };
  
}
