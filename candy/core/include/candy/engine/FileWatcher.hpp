#pragma once
#include <filesystem>

namespace Candy
{
  class FileWatcher
  {
  private:
   
    std::filesystem::path directory;
    
  public:
    explicit FileWatcher(std::filesystem::path  dir);
    
  public:
    void StartWatching();
    void StopWatching();
    void PollEvents();
  };
}