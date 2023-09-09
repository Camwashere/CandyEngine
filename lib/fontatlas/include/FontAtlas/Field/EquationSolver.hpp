
#pragma once

namespace msdfgen {

// ax^2 + bx + c = 0
  int solveQuadratic(float x[2], float a, float b, float c);

// ax^3 + bx^2 + cx + d = 0
  int solveCubic(float x[3], float a, float b, float c, float d);
  
}
