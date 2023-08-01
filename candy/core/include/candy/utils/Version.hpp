#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <spdlog/fmt/bundled/format.h>
namespace Candy
{
  
  class Version
  {
  private:
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
    
  public:
    Version(uint32_t major, uint32_t minor=0, uint32_t patch=0);
    
    void SetMajor(uint32_t value);
    void SetMinor(uint32_t value);
    void SetPatch(uint32_t value);
    void Set(uint32_t major, uint32_t minor=0, uint32_t patch=0);
    void IncrementMajor(uint32_t amount=1);
    void IncrementMinor(uint32_t amount=1);
    void IncrementPatch(uint32_t amount=1);
    void DecrementMajor(uint32_t amount=1);
    void DecrementMinor(uint32_t amount=1);
    void DecrementPatch(uint32_t amount=1);
    
    [[nodiscard]] uint32_t GetMajor()const;
    [[nodiscard]] uint32_t GetMinor()const;
    [[nodiscard]] uint32_t GetPatch()const;
    
    [[nodiscard]] bool operator==(const Version& other)const;
    [[nodiscard]] bool operator!=(const Version& other)const;
    [[nodiscard]] bool operator<(const Version& other)const;
    [[nodiscard]] bool operator>(const Version& other)const;
    [[nodiscard]] bool operator<=(const Version& other)const;
    [[nodiscard]] bool operator>=(const Version& other)const;
    
    [[nodiscard]] explicit operator std::string()const;
    
  };
}
template<>
struct fmt::formatter<Candy::Version>
{
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Version& input, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(),"{}.{}.{}", input.GetMajor(), input.GetMinor(), input.GetPatch());
  }
};
