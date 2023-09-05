#include <candy/graphics/font/Charset.hpp>

namespace Candy::Graphics
{
  static Charset CreateAsciiCharset() {
    Charset ascii;
    for (unicode_t cp = 0x20; cp < 0x7f; ++cp)
      ascii.Add(cp);
    return ascii;
  }
  
  const Charset Charset::ASCII = CreateAsciiCharset();
  
  void Charset::Add(unicode_t cp) {
    codepoints.insert(cp);
  }
  
  void Charset::Remove(unicode_t cp) {
    codepoints.erase(cp);
  }
  
  size_t Charset::Size() const {
    return codepoints.size();
  }
  
  bool Charset::Empty() const {
    return codepoints.empty();
  }
  
  std::set<unicode_t>::const_iterator Charset::begin() const {
    return codepoints.begin();
  }
  
  std::set<unicode_t>::const_iterator Charset::end() const {
    return codepoints.end();
  }
}