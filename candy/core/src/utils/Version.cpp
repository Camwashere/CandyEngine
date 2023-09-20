#include <candy/utils/Version.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>
#include <c4/format.hpp>
namespace Candy
{
  size_t to_chars(c4::substr buf, const Candy::Version& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{}]", v.GetMajor(), v.GetMinor(), v.GetPatch());
  }
  
  bool from_chars(c4::csubstr buf, Candy::Version* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    uint32_t major, minor, patch;
    size_t ret = c4::unformat(buf, "[{},{}]", major, minor, patch);
    v->Set(major, minor, patch);
    return ret != c4::csubstr::npos;
  }
}
namespace Candy
{
  Version::Version() : major(0), minor(0), patch(0)
  {
  
  }
  
  Version::Version(uint32_t majorV, uint32_t minorV, uint32_t patchV) : major(majorV), minor(minorV), patch(patchV)
  {
    
  }
  void Version::SetMajor(uint32_t value){major=value;}
  void Version::SetMinor(uint32_t value){minor=value;}
  void Version::SetPatch(uint32_t value){patch=value;}
  void Version::Set(uint32_t majorV, uint32_t minorV, uint32_t patchV){major = majorV; minor = minorV; patch = patchV;}
  void Version::IncrementMajor(uint32_t amount){major+=amount;}
  void Version::IncrementMinor(uint32_t amount){minor+=amount;}
  void Version::IncrementPatch(uint32_t amount){patch+=amount;}
  void Version::DecrementMajor(uint32_t amount){major-=amount;}
  void Version::DecrementMinor(uint32_t amount){minor-=amount;}
  void Version::DecrementPatch(uint32_t amount){patch-=amount;}
  uint32_t Version::GetMajor()const{return major;}
  uint32_t Version::GetMinor()const{return minor;}
  uint32_t Version::GetPatch()const{return patch;}
  
  bool Version::operator==(const Version& other)const
  {
    return major==other.major&&minor==other.minor&&patch==other.patch;
  }
  bool Version::operator!=(const Version& other)const
  {
    return (!(*this==other));
  }
  bool Version::operator<(const Version& other)const
  {
    if (major < other.major)
    {
      return true;
    }
    else if (major == other.major)
    {
      if (minor < other.minor)
      {
        return true;
      }
      else if (minor == other.minor)
      {
        return patch < other.patch;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  bool Version::operator>(const Version& other)const
  {
    if (major > other.major)
    {
      return true;
    }
    else if (major == other.major)
    {
      if (minor > other.minor)
      {
        return true;
      }
      else if (minor == other.minor)
      {
        return patch > other.patch;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  bool Version::operator<=(const Version& other)const
  {
    if ((*this)==other)
    {
      return true;
    }
    return ((*this)<other);
    
  }
  bool Version::operator>=(const Version& other)const
  {
    if ((*this)==other)
    {
      return true;
    }
    return ((*this)>other);
  }
  
  Version::operator std::string()const
  {
    return std::to_string(major)+"."+std::to_string(minor)+"."+std::to_string(patch);
  }
}