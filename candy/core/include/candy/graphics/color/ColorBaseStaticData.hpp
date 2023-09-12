#pragma once
#include "ColorBase.hpp"

namespace Candy
{
  
  
  template<typename T, uint8_t CHANNELS, typename Enable = void>
  struct ColorBaseStaticData;
  
  
  // VECTOR 2
  
  // Signed
  template<typename T>
  struct ColorBaseStaticData<T, 4, typename std::enable_if<std::is_floating_point<T>::value>::type>
  {
    
    static inline const ColorBase<T, 4> red = {1, 0, 0, 1};
    static inline const ColorBase<T, 4> green = {0, 1, 0, 1};
    static inline const ColorBase<T, 4> blue = {0, 0, 1, 1};
    static inline const ColorBase<T, 4> black = {0.0f, 0.0f, 0.0f, 1.0f};
    static inline const ColorBase<T, 4> white = {1, 1, 1, 1};
    static inline const ColorBase<T, 4> grey = {0.5f, 0.5f, 0.5f, 1};
    static inline const ColorBase<T, 4> clear = {0, 0, 0, 0};
    
    static inline const ColorBase<T, 4> teal = {0, 1, 1, 1};
    static inline const ColorBase<T, 4> magenta = {1, 0, 1, 1};
    static inline const ColorBase<T, 4> yellow = {1.0f, 0.92f, 0.016, 1};
    static inline const ColorBase<T, 4> orange = {1.0f, 0.647f, 0.0f, 1};
    static inline const ColorBase<T, 4> purple = {0.627f, 0.125f, 0.941f, 1};
    static inline const ColorBase<T, 4> brown = {0.588f, 0.294f, 0.0f, 1};
    static inline const ColorBase<T, 4> coral = {1.0f, 0.5f, 0.31f, 1};
    
  };
}