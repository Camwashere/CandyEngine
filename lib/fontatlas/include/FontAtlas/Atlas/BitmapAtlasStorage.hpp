#pragma once
#include <cstring>
#include "AtlasStorage.hpp"

namespace msdf_atlas {

/// An implementation of AtlasStorage represented by a bitmap in memory (msdfgen::Bitmap)
  template <typename T, int N>
  class BitmapAtlasStorage {
  
  public:
    BitmapAtlasStorage()= default;
    BitmapAtlasStorage(int width, int height) : bitmap(width, height) {
      memset((T *) bitmap, 0, sizeof(T)*N*width*height);
    }
    explicit BitmapAtlasStorage(const msdfgen::BitmapConstRef<T, N> &bitmap) : bitmap(bitmap) { }
    explicit BitmapAtlasStorage(msdfgen::Bitmap<T, N> &&bitmap) : bitmap((msdfgen::Bitmap<T, N> &&) bitmap) { }
    BitmapAtlasStorage(const BitmapAtlasStorage<T, N> &orig, int width, int height) : bitmap(width, height) {
      memset((T *) bitmap, 0, sizeof(T)*N*width*height);
      blit(bitmap, orig.bitmap, 0, 0, 0, 0, std::min(width, orig.bitmap.width()), std::min(height, orig.bitmap.height()));
    }
    BitmapAtlasStorage(const BitmapAtlasStorage<T, N> &orig, int width, int height, const Remap *remapping, int count) : bitmap(width, height) {
      memset((T *) bitmap, 0, sizeof(T)*N*width*height);
      for (int i = 0; i < count; ++i) {
        const Remap &remap = remapping[i];
        blit(bitmap, orig.bitmap, remap.target.x, remap.target.y, remap.source.x, remap.source.y, remap.width, remap.height);
      }
    }
    operator msdfgen::BitmapConstRef<T, N>() const
    {
      return bitmap;
    }
    operator msdfgen::BitmapRef<T, N>()
    {
      return bitmap;
    }
    operator msdfgen::Bitmap<T, N>() &&
    {
      return (msdfgen::Bitmap<T, N> &&) bitmap;
    }
    template <typename S>
    void put(int x, int y, const msdfgen::BitmapConstRef<S, N> &subBitmap) {
      blit(bitmap, subBitmap, x, y, 0, 0, subBitmap.width, subBitmap.height);
    }
    void get(int x, int y, const msdfgen::BitmapRef<T, N> &subBitmap) const {
      blit(subBitmap, bitmap, 0, 0, x, y, subBitmap.width, subBitmap.height);
    }
  
  private:
    msdfgen::Bitmap<T, N> bitmap;
    
  };
  
}


