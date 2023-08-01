#include <candy/utils/Version.hpp>

namespace Candy
{
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