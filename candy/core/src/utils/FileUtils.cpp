#include <candy/utils/FileUtils.hpp>

#include <fstream>
namespace Candy::Utils{
    Buffer FileUtils::ReadFileBinary(const std::filesystem::path& filepath)
    {
        std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
        
        if (!stream)
        {
            // Failed to open the file
            return {};
        }
        
        
        std::streampos end = stream.tellg();
        stream.seekg(0, std::ios::beg);
        uint64_t size = end - stream.tellg();
        
        if (size == 0)
        {
            // File is empty
            return {};
        }
        
        Buffer buffer(size);
        stream.read(buffer.As<char>(), size);
        stream.close();
        return buffer;
    }
  
  std::string FileUtils::ExtractNameFromFilePath(const std::filesystem::path& path)
  {
    // Extract name from filepath
    auto lastSlash = path.string().find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = path.string().rfind('.');
    auto count = lastDot == std::string::npos ? path.string().size() - lastSlash : lastDot - lastSlash;
    return path.string().substr(lastSlash, count);
  }
}