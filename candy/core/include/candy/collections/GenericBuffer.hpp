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
    
    void AddBuffer(const GenericBuffer& value)
    {
      buffer.insert(buffer.end(), value.buffer.begin(), value.buffer.end());
    }
    
    void Add(const char* data, size_t size)
    {
      CANDY_CORE_ASSERT(size > 0);
      buffer.insert(buffer.end(), data, data + size);
    }
    [[nodiscard]] const char* Data()const
    {
      return buffer.data();
    }
    char* Data()
    {
      return buffer.data();
    }
    
    [[nodiscard]] size_t Size()const
    {
      return buffer.size();
    }
  };
  
 
}