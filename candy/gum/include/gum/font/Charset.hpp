#pragma once
#include <candy/base/PrimitiveTypes.hpp>
#include <set>
namespace Candy::Gum
{
  class Charset
  {
  private:
    std::set<unicode_t> codepoints;
    
  public:
    /// The set of the 95 printable ASCII characters
    static const Charset ASCII;
    
    /// Adds a codepoint
    void Add(unicode_t codePoint);
    /// Removes a codepoint
    void Remove(unicode_t codePoint);
    
    [[nodiscard]] size_t Size() const;
    [[nodiscard]] bool Empty() const;
    [[nodiscard]] std::set<unicode_t>::const_iterator begin() const;
    [[nodiscard]] std::set<unicode_t>::const_iterator end() const;
    
    /// Load character set from a text file with the correct syntax
    bool Load(const char *filename, bool disableCharLiterals = false);
  
  
    
  };
}