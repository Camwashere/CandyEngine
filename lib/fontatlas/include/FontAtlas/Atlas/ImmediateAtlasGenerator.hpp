#pragma once

#include <vector>
#include "GlyphBox.hpp"
#include "Workload.hpp"
#include "AtlasGenerator.hpp"
#include <algorithm>
namespace msdf_atlas {

/**
 * An implementation of AtlasGenerator that uses the specified generator function
 * and AtlasStorage class and generates glyph bitmaps immediately
 * (does not return until all submitted work is finished),
 * but may use multiple threads (setThreadCount).
 */
  template <typename T, int N, GeneratorFunction<T, N> GEN_FN, class AtlasStorage>
  class ImmediateAtlasGenerator {
  
  private:
    AtlasStorage storage;
    std::vector<GlyphBox> layout;
    std::vector<T> glyphBuffer;
    std::vector<byte> errorCorrectionBuffer;
    GeneratorAttributes attributes;
    int threadCount;
  
  public:
    ImmediateAtlasGenerator() : threadCount(1) { }
    ImmediateAtlasGenerator(int width, int height) : storage(width, height), threadCount(1) { }
    template <typename... ARGS>
    ImmediateAtlasGenerator(int width, int height, ARGS... storageArgs) : storage(width, height, storageArgs...), threadCount(1) { }
    void generate(const GlyphGeometry *glyphs, int count) {
      int maxBoxArea = 0;
      for (int i = 0; i < count; ++i) {
        GlyphBox box = glyphs[i];
        maxBoxArea = std::max(maxBoxArea, box.rect.w*box.rect.h);
        layout.push_back((GlyphBox &&) box);
      }
      int threadBufferSize = N*maxBoxArea;
      if (threadCount*threadBufferSize > (int) glyphBuffer.size())
        glyphBuffer.resize(threadCount*threadBufferSize);
      if (threadCount*maxBoxArea > (int) errorCorrectionBuffer.size())
        errorCorrectionBuffer.resize(threadCount*maxBoxArea);
      std::vector<GeneratorAttributes> threadAttributes(threadCount);
      for (int i = 0; i < threadCount; ++i) {
        threadAttributes[i] = attributes;
        threadAttributes[i].config.errorCorrection.buffer = errorCorrectionBuffer.data()+i*maxBoxArea;
      }
      
      Workload([this, glyphs, &threadAttributes, threadBufferSize](int i, int threadNo) -> bool {
      const GlyphGeometry &glyph = glyphs[i];
      if (!glyph.isWhitespace()) {
        int l, b, w, h;
        glyph.getBoxRect(l, b, w, h);
        msdfgen::BitmapRef<T, N> glyphBitmap(glyphBuffer.data()+threadNo*threadBufferSize, w, h);
        GEN_FN(glyphBitmap, glyph, threadAttributes[threadNo]);
        storage.put(l, b, msdfgen::BitmapConstRef<T, N>(glyphBitmap));
      }
      return true;
      }, count).finish(threadCount);
    }
    void rearrange(int width, int height, const Remap *remapping, int count) {
      for (int i = 0; i < count; ++i) {
        layout[remapping[i].index].rect.x = remapping[i].target.x;
        layout[remapping[i].index].rect.y = remapping[i].target.y;
      }
      AtlasStorage newStorage((AtlasStorage &&) storage, width, height, remapping, count);
      storage = (AtlasStorage &&) newStorage;
    }
    void resize(int width, int height) {
      AtlasStorage newStorage((AtlasStorage &&) storage, width, height);
      storage = (AtlasStorage &&) newStorage;
    }
    /// Sets attributes for the generator function
    void setAttributes(const GeneratorAttributes &attr) {
      this->attributes = attr;
    }
    /// Sets the number of threads to be run by generate
    void setThreadCount(int count) {
      this->threadCount = count;
    }
    /// Allows access to the underlying AtlasStorage
    const AtlasStorage & atlasStorage() const {
      return storage;
    }
    /// Returns the layout of the contained glyphs as a list of GlyphBoxes
    [[nodiscard]] const std::vector<GlyphBox> & getLayout() const {
      return layout;
    }
  
  
    
  };
  
}

