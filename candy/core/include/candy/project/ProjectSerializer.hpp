#pragma once
#include "candy/base/Base.hpp"
#include "Project.hpp"
namespace Candy
{
  class ProjectSerializer
  {
  private:
    SharedPtr<Project> project;
  
  public:
    explicit ProjectSerializer(SharedPtr<Project> projectValue);
    bool Serialize(const std::filesystem::path& filepath);
    bool Deserialize(const std::filesystem::path& filepath);
  };
}