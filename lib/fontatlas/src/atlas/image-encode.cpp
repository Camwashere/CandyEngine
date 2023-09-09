
#include "FontAtlas/Atlas/image-encode.hpp"

#include "FontAtlas/Field/PixelConversion.hpp"

#include <png.h>

namespace msdf_atlas {
  
  class PngGuard {
    png_structp png;
    png_infop info;
  
  public:
    inline PngGuard(png_structp png, png_infop info) : png(png), info(info) { }
    inline ~PngGuard() {
      png_destroy_write_struct(&png, &info);
    }
    
  };
  
  static void pngIgnoreError(png_structp, png_const_charp) { }
  
  static void pngWrite(png_structp png, png_bytep data, png_size_t length) {
    std::vector<byte> &output = *reinterpret_cast<std::vector<byte> *>(png_get_io_ptr(png));
    output.insert(output.end(), data, data+length);
  }
  
  static void pngFlush(png_structp) { }
  
  static bool pngEncode(std::vector<byte> &output, const byte *pixels, int width, int height, int channels, int colorType) {
    if (!(pixels && width && height))
      return false;
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, &pngIgnoreError, &pngIgnoreError);
    if (!png)
      return false;
    png_infop info = png_create_info_struct(png);
    PngGuard guard(png, info);
    if (!info)
      return false;
    std::vector<const byte *> rows(height);
    for (int y = 0; y < height; ++y)
      rows[y] = pixels+channels*width*(height-y-1);
    if (setjmp(png_jmpbuf(png)))
      return false;
    png_set_write_fn(png, &output, &pngWrite, &pngFlush);
    png_set_IHDR(png, info, width, height, 8, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_compression_level(png, 9);
    png_set_rows(png, info, const_cast<png_bytepp>(&rows[0]));
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, nullptr);
    return true;
  }
  
  static bool pngEncode(std::vector<byte> &output, const float *pixels, int width, int height, int channels, int colorType) {
    if (!(pixels && width && height))
      return false;
    int subpixels = channels*width*height;
    std::vector<byte> bytePixels(subpixels);
    for (int i = 0; i < subpixels; ++i)
      bytePixels[i] = msdfgen::pixelFloatToByte(pixels[i]);
    return pngEncode(output, bytePixels.data(), width, height, channels, colorType);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<msdfgen::byte, 1> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 1, PNG_COLOR_TYPE_GRAY);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<msdfgen::byte, 3> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 3, PNG_COLOR_TYPE_RGB);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<msdfgen::byte, 4> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 4, PNG_COLOR_TYPE_RGB_ALPHA);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<float, 1> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 1, PNG_COLOR_TYPE_GRAY);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<float, 3> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 3, PNG_COLOR_TYPE_RGB);
  }
  
  bool encodePng(std::vector<byte> &output, const msdfgen::BitmapConstRef<float, 4> &bitmap) {
    return pngEncode(output, bitmap.pixels, bitmap.width, bitmap.height, 4, PNG_COLOR_TYPE_RGB_ALPHA);
  }
  
}


