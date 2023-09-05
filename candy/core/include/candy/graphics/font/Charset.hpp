#pragma once
#include <candy/base/PrimitiveTypes.hpp>
#include <set>
namespace Candy::Graphics
{
  
  class Charset
  {
  private:
    std::set<unicode_t> codepoints;
    
  public:
    static const Charset ASCII;
    void Add(unicode_t codepoint);
    void Remove(unicode_t codepoint);
    
    [[nodiscard]] size_t Size()const;
    [[nodiscard]] bool Empty()const;
    
    [[nodiscard]] std::set<unicode_t>::const_iterator begin() const;
    [[nodiscard]] std::set<unicode_t>::const_iterator end() const;
  };
}