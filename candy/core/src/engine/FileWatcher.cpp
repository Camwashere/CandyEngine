#include <candy/engine/FileWatcher.hpp>
#include <utility>

#include <CandyPch.hpp>
namespace Candy
{
  
  FileWatcher::FileWatcher(std::filesystem::path  dir) : directory(std::move(dir))
  {
  
  }
  void FileWatcher::StartWatching()
  {
  
  }
  void FileWatcher::StopWatching()
  {
  
  }
  void FileWatcher::PollEvents()
  {
  
  }
}