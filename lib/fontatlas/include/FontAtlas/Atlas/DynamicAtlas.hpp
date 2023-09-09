#pragma once

#include <vector>
#include "RectanglePacker.hpp"
#include "AtlasGenerator.hpp"

namespace msdf_atlas {
  
  static int ceilPOT(int x) {
    if (x > 0) {
      int y = 1;
      while (y < x)
        y <<= 1;
      return y;
    }
    return 0;
  }

/**
 * This class can be used to produce a dynamic atlas to which more glyphs are added over time.
 * It takes care of laying out and enlarging the atlas as necessary and delegates the actual work
 * to the specified AtlasGenerator, which may e.g. do the work asynchronously.
 */
  template <class AtlasGenerator>
  class DynamicAtlas {
  
  public:
    enum ChangeFlag {
      NO_CHANGE = 0x00,
      RESIZED = 0x01,
      REARRANGED = 0x02
    };
    typedef int ChangeFlags;
    
    DynamicAtlas() : side(0), padding(0), glyphCount(0), totalArea(0) { }
    /// Initializes generator with dimensions and custom arguments for generator
    template <typename... ARGS>
    explicit DynamicAtlas(int minSide, ARGS... args) : side(ceilPOT(minSide)), padding(0), glyphCount(0), totalArea(0), packer(side+padding, side+padding), generator(side, side, args...) { }
    /// Creates with a configured generator. The generator must not contain any prior glyphs!
    explicit DynamicAtlas(AtlasGenerator &&generator) : side(0), padding(0), glyphCount(0), totalArea(0), generator((AtlasGenerator &&) generator) { }
    /// Adds a batch of glyphs. Adding more than one glyph at a time may improve packing efficiency
    ChangeFlags add(GlyphGeometry *glyphs, int count, bool allowRearrange = false) {
      ChangeFlags changeFlags = 0;
      int start = rectangles.size();
      for (int i = 0; i < count; ++i) {
        if (!glyphs[i].isWhitespace()) {
          int w, h;
          glyphs[i].getBoxSize(w, h);
          Rectangle rect = { 0, 0, w+padding, h+padding };
          rectangles.push_back(rect);
          Remap remapEntry = { };
          remapEntry.index = glyphCount+i;
          remapEntry.width = w;
          remapEntry.height = h;
          remapBuffer.push_back(remapEntry);
          totalArea += (w+padding)*(h+padding);
        }
      }
      if ((int) rectangles.size() > start) {
        int packerStart = start;
        int remaining;
        while ((remaining = packer.pack(rectangles.data()+packerStart, rectangles.size()-packerStart)) > 0) {
          side = (side|!side)<<1;
          while (side*side < totalArea)
            side <<= 1;
          if (allowRearrange) {
            packer = RectanglePacker(side+padding, side+padding);
            packerStart = 0;
          } else {
            packer.expand(side+padding, side+padding);
            packerStart = rectangles.size()-remaining;
          }
          changeFlags |= RESIZED;
        }
        if (packerStart < start) {
          for (int i = packerStart; i < start; ++i) {
            Remap &remap = remapBuffer[i];
            remap.source = remap.target;
            remap.target.x = rectangles[i].x;
            remap.target.y = rectangles[i].y;
          }
          generator.rearrange(side, side, remapBuffer.data(), start);
          changeFlags |= REARRANGED;
        } else if (changeFlags&RESIZED)
          generator.resize(side, side);
        for (int i = start; i < (int) rectangles.size(); ++i) {
          remapBuffer[i].target.x = rectangles[i].x;
          remapBuffer[i].target.y = rectangles[i].y;
          glyphs[remapBuffer[i].index-glyphCount].placeBox(rectangles[i].x, rectangles[i].y);
        }
      }
      generator.generate(glyphs, count);
      glyphCount += count;
      return changeFlags;
    }
    /// Allows access to generator. Do not add glyphs to the generator directly!
    AtlasGenerator & atlasGenerator() {
      return generator;
    }
    const AtlasGenerator & atlasGenerator() const {
      return generator;
    }
  
  private:
    int side;
    int padding;
    int glyphCount;
    int totalArea;
    RectanglePacker packer;
    AtlasGenerator generator;
    std::vector<Rectangle> rectangles;
    std::vector<Remap> remapBuffer;
    
  };
  
}

