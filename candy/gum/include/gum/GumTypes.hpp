#pragma once
#include <cstdint>
#include <limits>
#include <vector>
#include <candy/base/Base.hpp>
#include <candy/base/Assert.hpp>
namespace Candy::Gum
{
  template<typename T>
  class GumIDVector;
  
  class GumID
  {
  public:
    static constexpr uint32_t NULL_ID = std::numeric_limits<uint32_t>::max();
  private:
    uint32_t id=NULL_ID;
    
  
    
  public:
    GumID(uint32_t gumID=NULL_ID) : id(gumID){} //NOLINT(google-explicit-constructor)
    GumID(GumID const &other) = default;
    
    explicit operator bool()const{return id!=NULL_ID;}
    explicit operator uint32_t()const{return id;}
    
    bool operator==(const GumID& other)const{return id==other.id;}
    bool operator==(uint8_t other) const {return id == other;}
    bool operator==(uint16_t other) const {return id == other;}
    bool operator==(uint32_t other)const{return id==other;}
    bool operator==(uint64_t other) const {return id == static_cast<uint32_t>(other);}
    
    bool operator!=(const GumID& other) const {return id != other.id;}
    bool operator!=(uint8_t other) const {return id != other;}
    bool operator!=(uint16_t other) const {return id != other;}
    bool operator!=(uint32_t other) const {return id != other;}
    bool operator!=(uint64_t other) const {return id != static_cast<uint32_t>(other);}
    
    bool operator<(const GumID& other) const {return id<other.id;}
    bool operator<(uint8_t other) const {return id<other;}
    bool operator<(uint16_t other) const {return id<other;}
    bool operator<(uint32_t other) const {return id<other;}
    bool operator<(uint64_t other) const {return id<static_cast<uint32_t>(other);}
    
    bool operator<=(const GumID& other) const {return id<=other.id;}
    bool operator<=(uint8_t other) const {return id<=other;}
    bool operator<=(uint16_t other) const {return id<=other;}
    bool operator<=(uint32_t other) const {return id<=other;}
    bool operator<=(uint64_t other) const {return id<=static_cast<uint32_t>(other);}
    
    bool operator>(const GumID& other) const {return id>other.id;}
    bool operator>(uint8_t other) const {return id>other;}
    bool operator>(uint16_t other) const {return id>other;}
    bool operator>(uint32_t other) const {return id>other;}
    bool operator>(uint64_t other) const {return id>static_cast<uint32_t>(other);}
    
    bool operator>=(const GumID& other) const {return id>=other.id;}
    bool operator>=(uint8_t other) const {return id>=other;}
    bool operator>=(uint16_t other) const {return id>=other;}
    bool operator>=(uint32_t other) const {return id>=other;}
    bool operator>=(uint64_t other) const {return id>=static_cast<uint32_t>(other);}
    
    GumID operator+(const GumID& other) const {return GumID{id+other.id};}
    GumID operator+(uint8_t other) const {return GumID{id+other};}
    GumID operator+(uint16_t other) const {return GumID{id+other};}
    GumID operator+(uint32_t other) const {return GumID{id+other};}
    GumID operator+(uint64_t other) const {return GumID{static_cast<uint32_t>(id+other)};}
    
    GumID operator-(const GumID& other) const {return GumID{id-other.id};}
    GumID operator-(uint8_t other) const {return GumID{id-other};}
    GumID operator-(uint16_t other) const {return GumID{id-other};}
    GumID operator-(uint32_t other) const {return GumID{id-other};}
    GumID operator-(uint64_t other) const {return GumID{static_cast<uint32_t>(id-other)};}
    
    GumID operator*(const GumID& other) const {return GumID{id*other.id};}
    GumID operator*(uint8_t other) const {return GumID{id*other};}
    GumID operator*(uint16_t other) const {return GumID{id*other};}
    GumID operator*(uint32_t other) const {return GumID{id*other};}
    GumID operator*(uint64_t other) const {return GumID{static_cast<uint32_t>(id*other)};}
    
    
    GumID operator/(const GumID& other) const {return GumID{id/other.id};}
    GumID operator/(uint8_t other) const {return GumID{id/other};}
    GumID operator/(uint16_t other) const {return GumID{id/other};}
    GumID operator/(uint32_t other) const {return GumID{id/other};}
    GumID operator/(uint64_t other) const {return GumID{static_cast<uint32_t>(id/other)};}
    
    GumID operator%(const GumID& other) const {return GumID{id%other.id};}
    GumID operator%(uint8_t other) const {return GumID{id%other};}
    GumID operator%(uint16_t other) const {return GumID{id%other};}
    GumID operator%(uint32_t other) const {return GumID{id%other};}
    GumID operator%(uint64_t other) const {return GumID{static_cast<uint32_t>(id%other)};}
    
    
    
    
    
    [[nodiscard]] bool IsNull()const{return id==NULL_ID;}
    [[nodiscard]] bool IsValid()const{return id!=NULL_ID;}
    
    template<typename T>
    friend class GumIDVector;
  };
  
  template<typename T>
  class GumIDVector
  {
  private:
    std::vector<T> data;
    
  public:
    T& operator[](GumID id)
    {
      CANDY_CORE_ASSERT(id.id < data.size(), "GumIDVector::operator[] index out of bounds");
      return data[id.id];
    }
    
    const T& operator[](GumID id)const
    {
      CANDY_CORE_ASSERT(id.id < data.size(), "GumIDVector::operator[] index out of bounds");
      return data[id.id];
    }
    
    auto begin()
    {
      return data.begin();
    }
    auto begin()const
    {
      return data.begin();
    }
    auto end()
    {
      return data.end();
    }
    auto end()const
    {
      return data.end();
    }
    
    
    void PushBack(const T& value)
    {
      data.push_back(value);
    }
    
    void PushBack(T&& value)
    {
      data.push_back(std::move(value));
    }
    
    void PopBack()
    {
      data.pop_back();
    }
    
    void Reserve(size_t size)
    {
      data.reserve(size);
    }
    void Resize(size_t size)
    {
      data.resize(size);
    }
    
    void Clear()
    {
      data.clear();
    }
    
    
    [[nodiscard]] size_t Size()const{return data.size();}
    [[nodiscard]] bool Empty()const{return data.empty();}
    [[nodiscard]] GumID FirstID()const{return GumID{0};}
    [[nodiscard]] GumID LastID()const{return GumID(data.size()-1);}
    
    const T& Front()const
    {
      return data.front();
    }
    T& Front()
    {
      return data.front();
    }
    
    const T& Back()const
    {
      return data.back();
    }
    
    T& Back()
    {
      return data.back();
    }
    
    const T& Last() const
    {
      return data.back();
    }
    
    T& Last()
    {
      return data.back();
    }
    
    
  };
}

namespace std
{
  template<typename T>
  struct hash;
  
  template<>
  struct hash<Candy::Gum::GumID>
  {
    std::size_t operator()(const Candy::Gum::GumID& id) const
    {
      return (std::uint32_t) id;
    }
  };
  
}

template<>
struct fmt::formatter<Candy::Gum::GumID>
{
  constexpr auto parse(format_parse_context& ctx)
  {
    return ctx.begin();
  }
  
  template<typename FormatContext>
  auto format(const Candy::Gum::GumID& id, FormatContext& ctx)
  {
    return format_to(ctx.out(), "{}", (uint32_t) id);
  }
};