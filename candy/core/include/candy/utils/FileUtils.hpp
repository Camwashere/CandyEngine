#pragma once
#include "../base/RawBuffer.hpp"

#include <filesystem>

namespace Candy::Utils
{
    class FileUtils
    {
    public:
        static Buffer ReadFileBinary(const std::filesystem::path& filepath);
        static std::string ExtractNameFromFilePath(const std::filesystem::path& path);
    };
  
  
  class FileDialogs
  {
  public:
    static std::string OpenFile(const char* filter);
    static std::string SaveFile(const char* filter);
  };
}