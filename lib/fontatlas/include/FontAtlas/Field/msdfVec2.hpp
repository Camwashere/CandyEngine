
#pragma once

namespace msdfgen {

/**
* A 2-dimensional euclidean vector with float precision.
* Implementation based on the msdfVec2 template from Artery Engine.
* @author Viktor Chlumsky
*/
  struct msdfVec2 {
    
    float x, y;
    
    msdfVec2(float val = 0);
    msdfVec2(float x, float y);
    /// Sets the vector to zero.
    void reset();
    /// Sets individual elements of the vector.
    void set(float x, float y);
    /// Returns the vector's length.
    float length() const;
    /// Returns the angle of the vector in radians (atan2).
    float direction() const;
    /// Returns the normalized vector - one that has the same direction but unit length.
    msdfVec2 normalize(bool allowZero = false) const;
    /// Returns a vector with the same length that is orthogonal to this one.
    msdfVec2 getOrthogonal(bool polarity = true) const;
    /// Returns a vector with unit length that is orthogonal to this one.
    msdfVec2 getOrthonormal(bool polarity = true, bool allowZero = false) const;
    /// Returns a vector projected along this one.
    msdfVec2 project(const msdfVec2 &vector, bool positive = false) const;
    operator const void *() const;
    bool operator!() const;
    bool operator==(const msdfVec2 &other) const;
    bool operator!=(const msdfVec2 &other) const;
    msdfVec2 operator+() const;
    msdfVec2 operator-() const;
    msdfVec2 operator+(const msdfVec2 &other) const;
    msdfVec2 operator-(const msdfVec2 &other) const;
    msdfVec2 operator*(const msdfVec2 &other) const;
    msdfVec2 operator/(const msdfVec2 &other) const;
    msdfVec2 operator*(float value) const;
    msdfVec2 operator/(float value) const;
    msdfVec2 & operator+=(const msdfVec2 &other);
    msdfVec2 & operator-=(const msdfVec2 &other);
    msdfVec2 & operator*=(const msdfVec2 &other);
    msdfVec2 & operator/=(const msdfVec2 &other);
    msdfVec2 & operator*=(float value);
    msdfVec2 & operator/=(float value);
    /// Dot product of two vectors.
    friend float dotProduct(const msdfVec2 &a, const msdfVec2 &b);
    /// A special version of the cross product for 2D vectors (returns scalar value).
    friend float crossProduct(const msdfVec2 &a, const msdfVec2 &b);
    friend msdfVec2 operator*(float value, const msdfVec2 &vector);
    friend msdfVec2 operator/(float value, const msdfVec2 &vector);
    
  };

/// A vector may also represent a point, which shall be differentiated semantically using the alias Point2.
  typedef msdfVec2 Point2;
  
}
