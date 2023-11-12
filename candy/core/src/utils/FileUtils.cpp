#include <candy/utils/FileUtils.hpp>
#include <candy/app/Application.hpp>
#include <fstream>
#include <utility>
#include <nativefiledialog/src/include/nfd.h>


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
  FileDialogFilter::FileDialogFilter()
  {
  
  }
  FileDialogFilter::FileDialogFilter(std::string name) : name(std::move(name))
  {
  
  }
  FileDialogFilter::FileDialogFilter(std::string  name, const std::vector<std::string>& extensions) : name(std::move(name))
  {
    AddExtensions(extensions);
  }
  void FileDialogFilter::AddExtension(const std::string& extension)
  {
    if (!extension.empty())
    {
      std::string ext = extension;
      // Remove '.' from start of extension if exists
      if (ext[0] == '.')
      {
        ext.erase(0, 1);
      }
      // Append to the types string separated by comma
      if (!types.empty())
      {
        types += ",";
      }
      types += ext;
    }
  }
  void FileDialogFilter::AddExtensions(const std::vector<std::string>& extensions)
  {
    for (const auto& ext : extensions)
    {
      // Call AddExtension method for each extension
      AddExtension(ext);
    }
  }
  const std::string& FileDialogFilter::GetTypes()const
  {
      return types;
  }
  const std::string& FileDialogFilter::GetName()const
  {
      return name;
  }
  const FileDialogFilter FileDialogFilter::Images("Images", {"png", "jpg", "jpeg", "bmp", "tga"});
  const FileDialogFilter FileDialogFilter::Scenes("Candy Scenes", {"scene"});
  const FileDialogFilter FileDialogFilter::Shaders("Shaders", {"vert", "frag", "comp", "glsl", "hlsl", "spv"});
  
  FileDialog::FileDialog()=default;
  FileDialog::FileDialog(const std::filesystem::path& startPath) : startPath(startPath), currentPath(startPath)
  {
  
  }
  FileDialog::FileDialog(const std::vector<FileDialogFilter>& filters) : filters(filters)
  {
  
  }
  FileDialog::FileDialog(const std::filesystem::path& startPath, const std::vector<FileDialogFilter>& filters) : startPath(startPath), currentPath(startPath), filters(filters)
  {
  
  }
  void FileDialog::AddFilter(const FileDialogFilter& filter)
  {
    filters.push_back(filter);
  }
  std::string FileDialog::GetFilterString()const
  {
    std::string filterString;
    for (const auto& filter : filters)
    {
      if (!filterString.empty())
      {
        filterString += ";";
      }
      filterString += filter.GetTypes();
    }
    return filterString;
  }
  std::filesystem::path FileDialog::OpenFile()
  {
    nfdchar_t *outPath = nullptr;
    std::string filterString = GetFilterString();
    const char* filter = filterString.empty() ? nullptr : filterString.c_str();
    nfdresult_t result = NFD_OpenDialog(filter, startPath.string().c_str(), &outPath);
   
    if (result == NFD_OKAY)
    {
      std::filesystem::path filePath(outPath);
      free(outPath); // don't forget to free the path string
      return filePath;
    }
    else if (result == NFD_CANCEL) return {};
    else
    {
      CANDY_CORE_ERROR("Error '{}'", NFD_GetError());
      return {};
    }
  }
  std::filesystem::path FileDialog::SaveFile()
  {
    nfdchar_t *outPath = nullptr;
    std::string filterString = GetFilterString();
    const char* filter = filterString.empty() ? nullptr : filterString.c_str();
    nfdresult_t result = NFD_SaveDialog(filter, startPath.string().c_str(), &outPath);
    
    if (result == NFD_OKAY)
    {
      std::string filePath(outPath);
      free(outPath); // don't forget to free the path string
      return filePath;
    }
    else if (result == NFD_CANCEL) return {};
    else
    {
      CANDY_CORE_ERROR("Error '{}'", NFD_GetError());
      return {};
    }
  }
  
}

