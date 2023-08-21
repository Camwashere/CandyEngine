#pragma once

#include "candy/graphics/shader/ShaderData.hpp"
#include <vector>
#include "CandyPch.hpp"
#include <typeinfo>
#include <typeindex>
#include <variant>
#include <candy/base/CandyConcepts.hpp>
#include <candy/math/Vector.hpp>

namespace Candy::Graphics
{
  struct BufferElement
  {
    std::string name = "Empty";
    ShaderData::Type type = ShaderData::Type::None;
    uint32_t location=0;
    uint32_t offset = 0;
    BufferElement(const BufferElement& other)=default;
    BufferElement(std::string elementName, ShaderData::Type dataType, uint32_t location);
    
    [[nodiscard]] uint64_t Size() const;
    
    [[nodiscard]] uint64_t GetComponentCount() const;
    
    [[nodiscard]] VkFormat GetFormat() const;
    
    [[nodiscard]] uint64_t CalculateSize(uint64_t count) const;
    
  };
  
  class BufferLayout
  {
  private:
    uint32_t binding = 0;
    uint32_t stride = 0;
    std::vector<BufferElement> elements{};
  
  private:
    void CalculateOffsetsAndStride();
  
  public:
    BufferLayout() = default;
    BufferLayout(const BufferLayout& other)=default;
    BufferLayout(std::initializer_list<BufferElement> bufferElements);
  
  public:
    std::vector<BufferElement>::iterator begin() {return elements.begin();}
    
    std::vector<BufferElement>::iterator end() {return elements.end();}
    
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const {return elements.begin();}
    
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const {return elements.end();}
  
  public:
    void Recalculate();
    void AddElement(std::string elementName, ShaderData::Type dataType, uint32_t location);
    uint32_t GetBinding()const;
    
    [[nodiscard]] const BufferElement &GetElement(uint64_t index) const;
    
    [[nodiscard]] uint32_t GetStride() const;
    
    [[nodiscard]]
    
    [[nodiscard]] size_t GetElementCount() const;
    
    [[nodiscard]] const std::vector<BufferElement> &GetElements() const;
    
    
    template<typename T>
    static constexpr size_t GetFlattenSizes(const std::vector<Math::VectorVariantList<T>>& vectorList)
    {
      size_t totalSize = 0;
      
      
      for (const auto& list : vectorList)
      {
        auto FindSize = std::visit([](const auto& elementList) { return elementList.size(); }, list);
        totalSize += FindSize;
      }
     
      size_t perElementSize = totalSize / vectorList.size();
      return perElementSize;
    }
    
    template<typename T, typename...VECTOR_LIST>
    requires(IsVectorContainer<VECTOR_LIST>&& ...)
    static constexpr std::vector<T> Flatten(const BufferLayout &layout, const VECTOR_LIST&... vector)
    {
      std::vector<T> result{};
      std::vector<Math::VectorVariantList<T>> vectorList{(vector)...};
      size_t countPerElement = GetFlattenSizes<T>(vectorList);
      size_t totalComponentCount = layout.CalculateTotalComponentCount(countPerElement);
      size_t incrementSize = countPerElement;
      size_t localIncSize = totalComponentCount / incrementSize;
      result.resize(totalComponentCount);
      for (size_t i=0, a=0; i<totalComponentCount; i+=localIncSize, a++)
      {
        size_t currentIncOffset=i;
        for (size_t b=0; b<vectorList.size(); b++)
        {
          std::visit([&result, a, &currentIncOffset](const auto& elementList)
          {
            auto element = elementList[a];
            for (size_t e=0; e<element.Size(); e++)
            {
              result[currentIncOffset] = element[e];
              currentIncOffset++;
            }
            
          }, vectorList[b]);
        }
      }
      return result;
    }
    
    
    [[nodiscard]] uint64_t CalculateSize(uint64_t countPerElement) const
    {
      
      uint64_t size = 0;
      for (auto&& element : elements)
      {
        size += element.Size();
      }
      //CANDY_CORE_INFO("SIZE: {}", size*countPerElement);
      return size*countPerElement;
    }
    
    [[nodiscard]] uint64_t CalculateTotalComponentCount(uint64_t countPerElement) const
    {
      uint64_t count = 0;
      for (auto&& element : elements)
      {
        count += element.GetComponentCount();
      }
      return count*countPerElement;
    }
    
    
  };
}