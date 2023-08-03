#pragma once

#include "candy/graphics/shader/ShaderData.hpp"
#include <vector>
#include "CandyPch.hpp"
#include <typeinfo>
#include <typeindex>

namespace Candy::Graphics
{
  struct BufferElement
  {
    std::string name = "Empty";
    ShaderData::Type type = ShaderData::Type::None;
    uint64_t offset = 0;
    
    BufferElement(ShaderData::Type dataType, std::string elementName);
    
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
    
    BufferLayout(std::initializer_list<BufferElement> bufferElements);
  
  public:
    std::vector<BufferElement>::iterator begin() {return elements.begin();}
    
    std::vector<BufferElement>::iterator end() {return elements.end();}
    
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const {return elements.begin();}
    
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const {return elements.end();}
  
  public:
    void AddElement(ShaderData::Type type, const std::string &name);
    
    [[nodiscard]] const BufferElement &GetElement(uint64_t index) const;
    
    [[nodiscard]] uint32_t GetStride() const;
    
    [[nodiscard]] size_t GetElementCount() const;
    
    //[[nodiscard]] VkVertexInputBindingDescription GetBindingDescription()const;
    [[nodiscard]] const std::vector<BufferElement> &GetElements() const;
    
    //[[nodiscard]] std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions()const;
    
    template<typename T>
    struct is_vector : std::false_type
    {
    };
    
    template<typename T, typename A>
    struct is_vector<std::vector<T, A>> : std::true_type
    {
    };

// Helper struct to check if T is a vector and get its value_type, falling back to T itself for non-vectors
    template<typename T, typename = void>
    struct container_value_type
    {
      using type = T;
    };
    
    template<typename T>
    struct container_value_type<T, std::enable_if_t<is_vector<std::decay_t<T>>::value>>
    {
      using type = typename std::decay_t<T>::value_type;
    };
    
    template<typename T> using container_value_type_t = typename container_value_type<T>::type;
    
    template<typename T, typename... Args>
    static constexpr bool AreTypesValidForFlatten(const std::vector<BufferElement>& bufferElements, Args &&... args)
    {
      std::vector<ShaderData::Type> types{};
      auto args_pack = std::make_tuple(std::forward<Args>(args)...);
      std::apply([&](auto &&... values)
                 {
                 ((types.push_back(ShaderData::TypeFrom<std::remove_cv_t<std::remove_reference_t<container_value_type_t<decltype(values)>>>>())), ...);
                 }, args_pack);
      
      for (int i=0; i<types.size(); i++)
      {
        if (types[i] != bufferElements[i].type)
        {
          return false;
        }
        if (ShaderData::TypeFrom<T>() != ShaderData::ToBaseType(bufferElements[i].type))
        {
          return false;
        }
      }
      
      return true;
      
    }
    
    template<typename... Args>
    static constexpr std::vector<ShaderData::Type> GetFlattenTypes(Args &&... args)
    {
      std::vector<ShaderData::Type> types{};
      auto args_pack = std::make_tuple(std::forward<Args>(args)...);
      std::apply([&](auto &&... values)
                 {
                 ((types.push_back(ShaderData::TypeFrom<std::remove_cv_t<std::remove_reference_t<container_value_type_t<decltype(values)>>>>())), ...);
                 }, args_pack);
      
      return types;
      
      
    }
    
    template<typename T, typename... Args>
    static constexpr std::vector<T> Flatten(const std::vector<BufferElement>& bufferElements, Args &&... args)
    {
      if (AreTypesValidForFlatten<T>(bufferElements, std::forward<Args>(args)...))
      {
        std::vector<T> result{};
        return result;
        
      }
      else
      {
        CANDY_CORE_ERROR("Flatten types are not valid");
        return {};
      }
      
    }
    
    
    [[nodiscard]] uint64_t CalculateSize(uint64_t countPerElement) const
    {
      
      uint64_t size = 0;
      for (auto &&element: elements)
      {
        size += element.Size();
      }
      return size*countPerElement;
    }
    
    [[nodiscard]] uint64_t CalculateTotalComponentCount(uint64_t countPerElement) const
    {
      uint64_t count = 0;
      for (auto &&element: elements)
      {
        count += element.GetComponentCount();
      }
      return count*countPerElement;
    }
    
    
  };
}