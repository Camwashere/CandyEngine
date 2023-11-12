#pragma once
#include "../base/RawBuffer.hpp"
#include <filesystem>
#include <vector>
namespace Candy::Utils
{
  class FileUtils
  {
  public:
    static Buffer ReadFileBinary(const std::filesystem::path& filepath);
    static std::string ExtractNameFromFilePath(const std::filesystem::path& path);
  };
  
  
  class FileDialogFilter
  {
  private:
    std::string name;
    std::string types;
    
  public:
    FileDialogFilter();
    explicit FileDialogFilter(std::string name);
    explicit FileDialogFilter(std::string  name, const std::vector<std::string>& extensions);
    void AddExtension(const std::string& extension);
    void AddExtensions(const std::vector<std::string>& extensions);
    [[nodiscard]] const std::string& GetTypes()const;
    [[nodiscard]] const std::string& GetName()const;
    
  public:
    static const FileDialogFilter Images;
    static const FileDialogFilter Scenes;
    static const FileDialogFilter Shaders;
  };
  
  
  class FileDialog
  {
  private:
    std::filesystem::path startPath;
    std::filesystem::path currentPath;
    std::vector<FileDialogFilter> filters;
    
  private:
    [[nodiscard]] std::string GetFilterString()const;
    
  public:
    FileDialog();
    explicit FileDialog(const std::filesystem::path& startPath);
    explicit FileDialog(const std::vector<FileDialogFilter>& filters);
    FileDialog(const std::filesystem::path& startPath, const std::vector<FileDialogFilter>& filters);
    
    void AddFilter(const FileDialogFilter& filter);
    
    std::filesystem::path OpenFile();
    std::filesystem::path SaveFile();
  };
}