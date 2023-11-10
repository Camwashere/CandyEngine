#include <candy/utils/FileUtils.hpp>
#include <candy/app/Application.hpp>
#include <fstream>
#include <GLFW/glfw3.h>

#ifdef CANDY_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#elifdef CANDY_PLATFORM_LINUX
  #include <nfd.h>
#endif

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
  
  std::string FileDialogs::OpenFile(const char* filter)
  {
    #ifdef CANDY_PLATFORM_WINDOWS
    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    CHAR currentDir[256] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetMainWindowReference().handle);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    if (GetCurrentDirectoryA(256, currentDir))
      ofn.lpstrInitialDir = currentDir;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    
    if (GetOpenFileNameA(&ofn) == TRUE)
      return ofn.lpstrFile;
    
    return std::string();
    #elifdef CANDY_PLATFORM_LINUX
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(filter, NULL, &outPath);

    if (result == NFD_OKAY)
    {
      std::string filePath(outPath);
      free(outPath); // don't forget to free the path string
      return filePath;
    }
    else if (result == NFD_CANCEL) return std::string();
    else
    {
      std::cout << "Error: " << NFD_GetError() << std::endl;
      return std::string();
    }
    #endif
    
  }
  
  std::string FileDialogs::SaveFile(const char* filter)
  {
    #ifdef CANDY_PLATFORM_WINDOWS
    
    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    CHAR currentDir[256] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetMainWindowReference().handle);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    if (GetCurrentDirectoryA(256, currentDir))
      ofn.lpstrInitialDir = currentDir;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    
    // Sets the default extension by extracting it from the filter
    ofn.lpstrDefExt = strchr(filter, '\0') + 1;
    
    if (GetSaveFileNameA(&ofn) == TRUE)
      return ofn.lpstrFile;
    
    return std::string();
    
    #elifdef CANDY_PLATFORM_LINUX
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog(filter, NULL, &outPath);

    if (result == NFD_OKAY)
    {
      std::string filePath(outPath);
      free(outPath); // don't forget to free the path string
      return filePath;
    }
    else if (result == NFD_CANCEL) return std::string();
    else
    {
      std::cout << "Error: " << NFD_GetError() << std::endl;
      return std::string();
    }
    #endif
    
  }
}

