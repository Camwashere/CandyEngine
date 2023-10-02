#pragma once
#include <candy/math/Vector.hpp>

namespace Candy::Math
{
  struct BezierCurveQuadratic
  {
    Vector2 start;
    Vector2 control;
    Vector2 end;
    
    /**
     * @brief Evaluate the point on the curve between the start and end at time t
     * @param t A value between 0 and 1, inclusive. 0 returns the start point, 1 returns the end point.
     * @return The 2D point on the curve at time t */
    [[nodiscard]] Vector2 Evaluate(float t)const;
    
    /**
     * @brief Calculate the length between the start and end points as a straight line
     * @return The direct length between the start and end points */
    [[nodiscard]] float StartToEndLength()const;
    
    /**
     * @brief Calculate the length between the start, control and end points as straight lines
     * @return The direct length of the control path */
    [[nodiscard]] float ControlPathLength()const;
    
    /**
     * @brief Calculate the approximate length of the curve
     * @param curvatureThreshold Threshold value deciding subdivision count. Higher values result in less subdivisions.
     * @param minSubdivisions Minimum number of subdivisions
     * @param maxSubdivisions Maximum number of subdivisions
     * @return The approximate length of the curve */
    [[nodiscard]] float Length(float curvatureThreshold=0.1f, size_t minSubdivisions=2, size_t maxSubdivisions=20)const;
    
    /**
     * @brief Calculate the tangent vector at time t
     * @param t A value between 0 and 1, inclusive. 0 returns the start point, 1 returns the end point.
     * @return The tangent vector at time t */
    [[nodiscard]] Vector2 Tangent(float t)const;
    
    /**
     * @brief Calculate the (approximately) closest point on the curve to the given point
     * @param point The point to find the closest point on the curve to
     * @param iterations The number of iterations to use when approximating the closest point. A higher number will yield a more precise result, yet will take longer
     * @return The closest point on the curve to the given point */
    [[nodiscard]] Vector2 ClosestPoint(const Vector2& point, size_t iterations=8)const;
    
    /**
     * @brief Approximate the number of line segments that make up the curve
     * @param subdivisions How many line segments will be used to approximate the curve. Higher values result in a more precise approximation, yet will take longer
     * @return A vector of line segments that make up the curve. It's size is equal to subdivisions + 1 */
    [[nodiscard]] std::vector<Vector2> ToLineSegments(float curvatureThreshold=0.1f, size_t minSubdivisions=2, size_t maxSubdivisions=20)const;
    
    /**
     * @brief Calculate the determinant of the quadratic bezier curve
     * @return The determinant of the quadratic bezier curve */
    [[nodiscard]] float Determinant()const;
    
    /**
     * @brief Calculate the concavity of the curve
     * @param straightLineThreshold The threshold value for the determinant to be considered a straight line
     * @return The concavity of the curve. (Convex, Concave or Straight) */
    [[nodiscard]] Concavity GetConcavity(float straightLineThreshold=Epsilon<float>())const;
    
    /**
     * @brief Check if the curve is a straight line
     * @param threshold The threshold value for the determinant to be considered a straight line
     * @return True if the curve is a straight line, false otherwise */
    [[nodiscard]] bool IsStraightLine(float threshold=Epsilon<float>())const;
    
    /**
     * @brief Check if the curve is convex
     * @return True if the curve is convex, false otherwise */
    [[nodiscard]] bool IsConvex(float straightLineThreshold=Epsilon<float>())const;
    [[nodiscard]] bool IsConcave(float straightLineThreshold=Epsilon<float>())const;
    
  };
}