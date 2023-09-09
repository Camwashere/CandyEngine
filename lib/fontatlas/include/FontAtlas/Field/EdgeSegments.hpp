
#pragma once

#include "msdfVec2.hpp"
#include "SignedDistance.hpp"
#include "EdgeColor.hpp"

namespace msdfgen {

// Parameters for iterative search of closest point on a cubic Bezier curve. Increase for higher precision.
#define MSDFGEN_CUBIC_SEARCH_STARTS 4
#define MSDFGEN_CUBIC_SEARCH_STEPS 4

/// An abstract edge segment.
  class EdgeSegment {
  
  public:
    EdgeColor color;
    
    EdgeSegment(EdgeColor edgeColor = WHITE) : color(edgeColor) { }
    virtual ~EdgeSegment() { }
    /// Creates a copy of the edge segment.
    virtual EdgeSegment * clone() const = 0;
    /// Returns the numeric code of the edge segment's type.
    virtual int type() const = 0;
    /// Returns the array of control points.
    virtual const msdfVec2 * controlPoints() const = 0;
    /// Returns the point on the edge specified by the parameter (between 0 and 1).
    virtual msdfVec2 point(float param) const = 0;
    /// Returns the direction the edge has at the point specified by the parameter.
    virtual msdfVec2 direction(float param) const = 0;
    /// Returns the change of direction (second derivative) at the point specified by the parameter.
    virtual msdfVec2 directionChange(float param) const = 0;
    /// Returns the minimum signed distance between origin and the edge.
    virtual SignedDistance signedDistance(msdfVec2 origin, float &param) const = 0;
    /// Converts a previously retrieved signed distance from origin to pseudo-distance.
    virtual void distanceToPseudoDistance(SignedDistance &distance, msdfVec2 origin, float param) const;
    /// Outputs a list of (at most three) intersections (their X coordinates) with an infinite horizontal scanline at y and returns how many there are.
    virtual int scanlineIntersections(float x[3], int dy[3], float y) const = 0;
    /// Adjusts the bounding box to fit the edge segment.
    virtual void bound(float &l, float &b, float &r, float &t) const = 0;
    
    /// Reverses the edge (swaps its start point and end point).
    virtual void reverse() = 0;
    /// Moves the start point of the edge segment.
    virtual void moveStartPoint(msdfVec2 to) = 0;
    /// Moves the end point of the edge segment.
    virtual void moveEndPoint(msdfVec2 to) = 0;
    /// Splits the edge segments into thirds which together represent the original edge.
    virtual void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const = 0;
    
  };

/// A line segment.
  class LinearSegment : public EdgeSegment {
  
  public:
    enum EdgeType {
      EDGE_TYPE = 1
    };
    
    msdfVec2 p[2];
    
    LinearSegment(msdfVec2 p0, msdfVec2 p1, EdgeColor edgeColor = WHITE);
    LinearSegment * clone() const;
    int type() const;
    const msdfVec2 * controlPoints() const;
    msdfVec2 point(float param) const;
    msdfVec2 direction(float param) const;
    msdfVec2 directionChange(float param) const;
    float length() const;
    SignedDistance signedDistance(msdfVec2 origin, float &param) const;
    int scanlineIntersections(float x[3], int dy[3], float y) const;
    void bound(float &l, float &b, float &r, float &t) const;
    
    void reverse();
    void moveStartPoint(msdfVec2 to);
    void moveEndPoint(msdfVec2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;
    
  };

/// A quadratic Bezier curve.
  class QuadraticSegment : public EdgeSegment {
  
  public:
    enum EdgeType {
      EDGE_TYPE = 2
    };
    
    msdfVec2 p[3];
    
    QuadraticSegment(msdfVec2 p0, msdfVec2 p1, msdfVec2 p2, EdgeColor edgeColor = WHITE);
    QuadraticSegment * clone() const;
    int type() const;
    const msdfVec2 * controlPoints() const;
    msdfVec2 point(float param) const;
    msdfVec2 direction(float param) const;
    msdfVec2 directionChange(float param) const;
    float length() const;
    SignedDistance signedDistance(msdfVec2 origin, float &param) const;
    int scanlineIntersections(float x[3], int dy[3], float y) const;
    void bound(float &l, float &b, float &r, float &t) const;
    
    void reverse();
    void moveStartPoint(msdfVec2 to);
    void moveEndPoint(msdfVec2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;
    
    EdgeSegment * convertToCubic() const;
    
  };

/// A cubic Bezier curve.
  class CubicSegment : public EdgeSegment {
  
  public:
    enum EdgeType {
      EDGE_TYPE = 3
    };
    
    msdfVec2 p[4];
    
    CubicSegment(msdfVec2 p0, msdfVec2 p1, msdfVec2 p2, msdfVec2 p3, EdgeColor edgeColor = WHITE);
    CubicSegment * clone() const;
    int type() const;
    const msdfVec2 * controlPoints() const;
    msdfVec2 point(float param) const;
    msdfVec2 direction(float param) const;
    msdfVec2 directionChange(float param) const;
    SignedDistance signedDistance(msdfVec2 origin, float &param) const;
    int scanlineIntersections(float x[3], int dy[3], float y) const;
    void bound(float &l, float &b, float &r, float &t) const;
    
    void reverse();
    void moveStartPoint(msdfVec2 to);
    void moveEndPoint(msdfVec2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;
    
    void deconverge(int param, float amount);
    
  };
  
}
