#pragma once
#include <vector>
namespace Candy::Collections
{
  class GenericBuffer
  {
  private:
    std::vector<char> buffer;
    
  public:
    template<typename T>
    void Add(const T& value)
    {
      const char* start = reinterpret_cast<const char*>(std::addressof(value));
      buffer.insert(buffer.end(), start, start + sizeof(T));
    }
    
    const char* Data()const
    {
      return buffer.data();
    }
    char* Data()
    {
      return buffer.data();
    }
    
    size_t Size()const
    {
      return buffer.size();
    }
  };
}