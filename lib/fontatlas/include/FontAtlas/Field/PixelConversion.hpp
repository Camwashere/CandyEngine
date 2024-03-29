
#pragma once

#include "Arithmetics.hpp"

namespace msdfgen {
  
  typedef unsigned char byte;
  
  inline byte pixelFloatToByte(float x) {
    return byte(clamp(256.f*x, 255.f));
  }
  
  inline float pixelByteToFloat(byte x) {
    return 1.f/255.f*float(x);
  }
  
}
