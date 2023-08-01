#include <candy/app/Project.hpp>
#include <utility>

namespace Candy
{
  Project::Project(ProjectConfig projectConfig) : config(std::move(projectConfig))
  {
  
  }
}