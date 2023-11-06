#pragma once
#include <candy/math/Vector.hpp>
#include <numbers>
#include <cmath>
namespace Candy::Math
{
  template<size_t N>
  struct BezierCurve
  {
    std::array<Vector2, N+1> controlPoints;
    
    [[nodiscard]] constexpr Vector2 Evaluate(float t) const {
      return EvaluateImpl(std::make_index_sequence<N>{}, t);
    }
    
    
  
  private:
    // Helper function
    template<size_t I>
    [[nodiscard]] constexpr Vector2 calculatePoint(float t, float u) const {
      return (std::tgamma(N + 1) / (std::tgamma(I + 1) * std::tgamma(N - I + 1))) * std::pow(u, N-I) * std::pow(t, I) * controlPoints[I];
    }
    template<size_t... Is>
    constexpr Vector2 EvaluateImpl(std::index_sequence<Is...>, float t) const {
      float u = 1 - t;
      return (calculatePoint<Is>(t, u) + ...);
    }
  };
}