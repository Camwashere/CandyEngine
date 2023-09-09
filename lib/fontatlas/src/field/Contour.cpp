
#include <cmath>

#include "FontAtlas/Field/Contour.hpp"

#include "FontAtlas/Field/Arithmetics.hpp"

namespace msdfgen {
  
  static float shoelace(const msdfVec2 &a, const msdfVec2 &b) {
    return (b.x-a.x)*(a.y+b.y);
  }
  
  void Contour::AddEdge(const EdgeHolder &edge) {
    edges.push_back(edge);
  }


  void Contour::AddEdge(EdgeHolder &&edge) {
    edges.push_back((EdgeHolder &&) edge);
}

  
  EdgeHolder & Contour::AddEdge() {
    edges.resize(edges.size()+1);
    return edges.back();
  }
  
  static void boundPoint(float &l, float &b, float &r, float &t, msdfVec2 p) {
    if (p.x < l) l = p.x;
    if (p.y < b) b = p.y;
    if (p.x > r) r = p.x;
    if (p.y > t) t = p.y;
  }
  
  void Contour::Bound(float &l, float &b, float &r, float &t) const {
    for (std::vector<EdgeHolder>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge)
      (*edge)->bound(l, b, r, t);
  }
  
  void Contour::BoundMiters(float &l, float &b, float &r, float &t, float border, float miterLimit, int polarity) const {
    if (edges.empty())
      return;
    msdfVec2 prevDir = edges.back()->direction(1).normalize(true);
    for (std::vector<EdgeHolder>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge) {
      msdfVec2 dir = -(*edge)->direction(0).normalize(true);
      if (polarity*crossProduct(prevDir, dir) >= 0) {
        float miterLength = miterLimit;
        float q = .5f*(1.0f-dotProduct(prevDir, dir));
        if (q > 0)
          miterLength = min(1.0f/std::sqrt(q), miterLimit);
        msdfVec2 miter = (*edge)->point(0)+border*miterLength*(prevDir+dir).normalize(true);
        boundPoint(l, b, r, t, miter);
      }
      prevDir = (*edge)->direction(1).normalize(true);
    }
  }
  
  int Contour::Winding() const {
    if (edges.empty())
      return 0;
    float total = 0;
    if (edges.size() == 1) {
      msdfVec2 a = edges[0]->point(0), b = edges[0]->point(1/3.), c = edges[0]->point(2/3.);
      total += shoelace(a, b);
      total += shoelace(b, c);
      total += shoelace(c, a);
    } else if (edges.size() == 2) {
      msdfVec2 a = edges[0]->point(0), b = edges[0]->point(.5), c = edges[1]->point(0), d = edges[1]->point(.5);
      total += shoelace(a, b);
      total += shoelace(b, c);
      total += shoelace(c, d);
      total += shoelace(d, a);
    } else {
      msdfVec2 prev = edges.back()->point(0);
      for (std::vector<EdgeHolder>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        msdfVec2 cur = (*edge)->point(0);
        total += shoelace(prev, cur);
        prev = cur;
      }
    }
    return sign(total);
  }
  
  void Contour::Reverse() {
    for (int i = (int) edges.size()/2; i > 0; --i)
      EdgeHolder::swap(edges[i-1], edges[edges.size()-i]);
    for (std::vector<EdgeHolder>::iterator edge = edges.begin(); edge != edges.end(); ++edge)
      (*edge)->reverse();
  }
  
}
