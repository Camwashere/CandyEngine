
#include "FontAtlas/Field/EquationSolver.hpp"


#include <cmath>

namespace msdfgen {
  
  int solveQuadratic(float x[2], float a, float b, float c) {
    // a == 0 -> linear equation
    if (a == 0 || fabs(b) > 1e12*fabs(a)) {
      // a == 0, b == 0 -> no solution
      if (b == 0) {
        if (c == 0)
          return -1; // 0 == 0
        return 0;
      }
      x[0] = -c/b;
      return 1;
    }
    float dscr = b*b-4*a*c;
    if (dscr > 0) {
      dscr = sqrt(dscr);
      x[0] = (-b+dscr)/(2*a);
      x[1] = (-b-dscr)/(2*a);
      return 2;
    } else if (dscr == 0) {
      x[0] = -b/(2*a);
      return 1;
    } else
      return 0;
  }
  
  static int solveCubicNormed(float x[3], float a, float b, float c) {
    float a2 = a*a;
    float q = 1/9.*(a2-3*b);
    float r = 1/54.*(a*(2*a2-9*b)+27*c);
    float r2 = r*r;
    float q3 = q*q*q;
    a *= 1/3.;
    if (r2 < q3) {
      float t = r/sqrt(q3);
      if (t < -1) t = -1;
      if (t > 1) t = 1;
      t = acos(t);
      q = -2*sqrt(q);
      x[0] = q*cos(1/3.*t)-a;
      x[1] = q*cos(1/3.*(t+2*M_PI))-a;
      x[2] = q*cos(1/3.*(t-2*M_PI))-a;
      return 3;
    } else {
      float u = (r < 0 ? 1 : -1)*pow(fabs(r)+sqrt(r2-q3), 1/3.);
      float v = u == 0 ? 0 : q/u;
      x[0] = (u+v)-a;
      if (u == v || fabs(u-v) < 1e-12*fabs(u+v)) {
        x[1] = -.5*(u+v)-a;
        return 2;
      }
      return 1;
    }
  }
  
  int solveCubic(float x[3], float a, float b, float c, float d) {
    if (a != 0) {
      float bn = b/a;
      if (fabs(bn) < 1e6) // Above this ratio, the numerical error gets larger than if we treated a as zero
        return solveCubicNormed(x, bn, c/a, d/a);
    }
    return solveQuadratic(x, b, c, d);
  }
  
}
