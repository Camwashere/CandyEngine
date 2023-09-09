
#pragma once

#include "BitmapRef.hpp"

namespace msdfgen {

/// A 2D image bitmap with N channels of type T. Pixel memory is managed by the class.
  template <typename T, int N = 1>
  class Bitmap {
  
  private:
    T *pixels;
    int w, h;
  
  public:
    Bitmap()  : pixels(nullptr), w(0), h(0) { }
    Bitmap(int width, int height) : w(width), h(height) {
      pixels = new T[N*w*h];
    }
    Bitmap(const BitmapConstRef<T, N> &orig) : w(orig.width), h(orig.height) {
      pixels = new T[N*w*h];
      memcpy(pixels, orig.pixels, sizeof(T)*N*w*h);
    }
    Bitmap(const Bitmap<T, N> &orig) : pixels(orig.pixels), w(orig.w), h(orig.h) {
      orig.pixels = NULL;
      orig.w = 0, orig.h = 0;
    }
    Bitmap(Bitmap<T, N> &&orig) noexcept  : pixels(orig.pixels), w(orig.w), h(orig.h) {
      orig.pixels = NULL;
      orig.w = 0, orig.h = 0;
    }

    ~Bitmap()
    {
      delete[] pixels;
    }
    
  public:
    Bitmap<T, N>& operator=(const BitmapConstRef<T, N> &orig)
    {
      if (pixels != orig.pixels)
      {
        delete [] pixels;
        w = orig.width, h = orig.height;
        pixels = new T[N*w*h];
        memcpy(pixels, orig.pixels, sizeof(T)*N*w*h);
      }
      return *this;
    }
    
    
    Bitmap<T, N> & operator=(const Bitmap<T, N> &orig)
    {
      if (this != &orig)
      {
        delete [] pixels;
        w = orig.w, h = orig.h;
        pixels = new T[N*w*h];
        memcpy(pixels, orig.pixels, sizeof(T)*N*w*h);
      }
      return *this;
    }
    
    
    
    Bitmap<T, N> & operator=(Bitmap<T, N> &&orig) noexcept
    {
      if (this != &orig)
      {
        delete [] pixels;
        pixels = orig.pixels;
        w = orig.w, h = orig.h;
        orig.pixels = NULL;
      }
      return *this;
    }
    
    
    
    [[nodiscard]] int Width() const {
      return w;
    }
    
    
    [[nodiscard]] int Height() const {
      return h;
    }
    
    
    T * operator()(int x, int y) {
      return pixels+N*(w*y+x);
    }
    
    
    const T * operator()(int x, int y) const {
      return pixels+N*(w*y+x);
    }
    
    
    explicit operator T *() {
      return pixels;
    }
    
    
    explicit operator const T *() const {
      return pixels;
    }
    
    
    operator BitmapRef<T, N>() {
      return BitmapRef<T, N>(pixels, w, h);
    }
    
    
    operator BitmapConstRef<T, N>() const {
      return BitmapConstRef<T, N>(pixels, w, h);
    }
  
  
    
  };
  
  
  
  
  
  
}


