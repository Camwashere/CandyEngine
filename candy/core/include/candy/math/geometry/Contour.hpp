#pragma once
#include <candy/math/geometry/Line.hpp>
#include <candy/math/curve/BezierCurve.hpp>
#include <candy/math/curve/BezierCurveCubic.hpp>
#include <candy/math/curve/BezierCurveQuadratic.hpp>
namespace Candy::Math
{
  struct Contour
  {
    std::variant<Line, BezierCurveQuadratic, BezierCurveCubic> value;
  };
}