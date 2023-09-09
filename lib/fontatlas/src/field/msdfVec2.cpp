
#include "FontAtlas/Field/msdfVec2.hpp"

#include <cstddef>
#include <cmath>

namespace msdfgen {
  
  msdfVec2::msdfVec2(float val) : x(val), y(val) { }
  
  msdfVec2::msdfVec2(float x, float y) : x(x), y(y) { }
  
  void msdfVec2::reset() {
    x = 0, y = 0;
  }
  
  void msdfVec2::set(float x, float y) {
    msdfVec2::x = x, msdfVec2::y = y;
  }
  
  float msdfVec2::length() const {
    return sqrt(x*x+y*y);
  }
  
  float msdfVec2::direction() const {
    return atan2(y, x);
  }
  
  msdfVec2 msdfVec2::normalize(bool allowZero) const {
    float len = length();
    if (len == 0)
      return msdfVec2(0, !allowZero);
    return msdfVec2(x/len, y/len);
  }
  
  msdfVec2 msdfVec2::getOrthogonal(bool polarity) const {
    return polarity ? msdfVec2(-y, x) : msdfVec2(y, -x);
  }
  
  msdfVec2 msdfVec2::getOrthonormal(bool polarity, bool allowZero) const {
    float len = length();
    if (len == 0)
      return polarity ? msdfVec2(0, !allowZero) : msdfVec2(0, -!allowZero);
    return polarity ? msdfVec2(-y/len, x/len) : msdfVec2(y/len, -x/len);
  }
  
  msdfVec2 msdfVec2::project(const msdfVec2 &vector, bool positive) const {
    msdfVec2 n = normalize(true);
    float t = dotProduct(vector, n);
    if (positive && t <= 0)
      return msdfVec2();
    return t*n;
  }
  
  msdfVec2::operator const void*() const {
    return x || y ? this : NULL;
  }
  
  bool msdfVec2::operator!() const {
    return !x && !y;
  }
  
  bool msdfVec2::operator==(const msdfVec2 &other) const {
    return x == other.x && y == other.y;
  }
  
  bool msdfVec2::operator!=(const msdfVec2 &other) const {
    return x != other.x || y != other.y;
  }
  
  msdfVec2 msdfVec2::operator+() const {
    return *this;
  }
  
  msdfVec2 msdfVec2::operator-() const {
    return msdfVec2(-x, -y);
  }
  
  msdfVec2 msdfVec2::operator+(const msdfVec2 &other) const {
    return msdfVec2(x+other.x, y+other.y);
  }
  
  msdfVec2 msdfVec2::operator-(const msdfVec2 &other) const {
    return msdfVec2(x-other.x, y-other.y);
  }
  
  msdfVec2 msdfVec2::operator*(const msdfVec2 &other) const {
    return msdfVec2(x*other.x, y*other.y);
  }
  
  msdfVec2 msdfVec2::operator/(const msdfVec2 &other) const {
    return msdfVec2(x/other.x, y/other.y);
  }
  
  msdfVec2 msdfVec2::operator*(float value) const {
    return msdfVec2(x*value, y*value);
  }
  
  msdfVec2 msdfVec2::operator/(float value) const {
    return msdfVec2(x/value, y/value);
  }
  
  msdfVec2 & msdfVec2::operator+=(const msdfVec2 &other) {
    x += other.x, y += other.y;
    return *this;
  }
  
  msdfVec2 & msdfVec2::operator-=(const msdfVec2 &other) {
    x -= other.x, y -= other.y;
    return *this;
  }
  
  msdfVec2 & msdfVec2::operator*=(const msdfVec2 &other) {
    x *= other.x, y *= other.y;
    return *this;
  }
  
  msdfVec2 & msdfVec2::operator/=(const msdfVec2 &other) {
    x /= other.x, y /= other.y;
    return *this;
  }
  
  msdfVec2 & msdfVec2::operator*=(float value) {
    x *= value, y *= value;
    return *this;
  }
  
  msdfVec2 & msdfVec2::operator/=(float value) {
    x /= value, y /= value;
    return *this;
  }
  
  float dotProduct(const msdfVec2 &a, const msdfVec2 &b) {
    return a.x*b.x+a.y*b.y;
  }
  
  float crossProduct(const msdfVec2 &a, const msdfVec2 &b) {
    return a.x*b.y-a.y*b.x;
  }
  
  msdfVec2 operator*(float value, const msdfVec2 &vector) {
    return msdfVec2(value*vector.x, value*vector.y);
  }
  
  msdfVec2 operator/(float value, const msdfVec2 &vector) {
    return msdfVec2(value/vector.x, value/vector.y);
  }
  
}
