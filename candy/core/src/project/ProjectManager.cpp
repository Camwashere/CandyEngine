#include <candy/project/ProjectManager.hpp>
#include "rapidyaml/src/ryml_std.hpp"
#include "rapidyaml/src/ryml.hpp"
#include <CandyPch.hpp>
#include <CandyEngine.hpp>
#include <candy/project/Project.hpp>
#include <optional>
namespace Candy
{
  struct ProjectManagerData
  {
    SharedPtr<Project> activeProject;
    
  };
  
  struct ProjectDirectoryValidationData
  {
    bool rootValid = false;
    bool subDirectoriesExist=false;
    
    int candyFilePathCount=0;
    std::optional<std::filesystem::path> candyFilePath;
    
    [[nodiscard]] bool IsValid()const
    {
      return rootValid && subDirectoriesExist && candyFilePathCount == 1 && candyFilePath.has_value();
    }
  };
  
  static ProjectManagerData data;
  
  static bool IsValidProjectFileType(const std::filesystem::path& projectFile)
  {
    if (std::filesystem::exists(projectFile) && std::filesystem::is_regular_file(projectFile))
    {
      return projectFile.extension() == CandyEngine::PROJECT_FILE_EXTENSION;
    }
    return false;
    
  }
  
  static ProjectDirectoryValidationData ValidateProjectDirectory(const std::filesystem::path& projectDirectory)
  {
    ProjectDirectoryValidationData validationData{};
    
    if (std::filesystem::exists(projectDirectory) && std::filesystem::is_directory(projectDirectory))
    {
      validationData.rootValid = true;
      CANDY_CORE_INFO("Valid project root directory");
      validationData.subDirectoriesExist = std::filesystem::exists(projectDirectory / "assets") &&
                                           std::filesystem::exists(projectDirectory / "cache") &&
                                           std::filesystem::exists(projectDirectory / "packages") &&
                                           std::filesystem::exists(projectDirectory / "library") &&
                                           std::filesystem::exists(projectDirectory / "logs") &&
                                           std::filesystem::exists(projectDirectory / "config") &&
                                           std::filesystem::exists(projectDirectory / "meta");
      
      CANDY_CORE_INFO("Valid project sub directories");
      
      try
      {
        
        for (auto& p : std::filesystem::directory_iterator(projectDirectory))
        {
          if (p.path().extension() == CandyEngine::PROJECT_FILE_EXTENSION)
          {
            validationData.candyFilePathCount++;
            validationData.candyFilePath = p.path();
          }
          
        }
        return validationData;
      }
      catch (std::filesystem::filesystem_error& e)
      {
        CANDY_CORE_ASSERT_MSG(false, "Failed to extract project file from directory {0}. Error: {1}", projectDirectory.string(), e.what());
        return {};
      }
    }
    
    return {};
  }
  
  
  
  static std::filesystem::path ExtractProjectFileFromDirectory(const std::filesystem::path& projectDirectory)
  {
    if (std::filesystem::exists(projectDirectory) && std::filesystem::is_directory(projectDirectory))
    {
      std::filesystem::path projectFilePath;
      try
      {
        for (auto& p : std::filesystem::directory_iterator(projectDirectory))
        {
          if (p.path().extension() == CandyEngine::PROJECT_FILE_EXTENSION)
          {
            return projectFilePath;
          }
          
        }
      }
      catch (std::filesystem::filesystem_error& e)
      {
        CANDY_CORE_ASSERT_MSG(false, "Failed to extract project file from directory {0}. Error: {1}", projectDirectory.string(), e.what());
        return {};
      }
      
    }
    return {};
   
  }
  
  static bool CreateEmptyFileAt(const std::filesystem::path& filepath)
  {
    // Create an ofstream object, this will create the file if it doesn't exist
    std::ofstream file(filepath);
    
    // Check if the file has been created
    if (!file)
    {
      return false; // File not created, return false
    }
    // Close the file
    file.close();
    return true;
  }
  
  bool ProjectManager::Init()
  {
    return LoadProject(CandyEngine::GetProjectsDirectory() / "ExampleProject");
  }
  bool ProjectManager::NewProject(const std::string& projectName)
  {
    std::filesystem::path projectsDirectory = CandyEngine::GetProjectsDirectory();
    return NewProject(projectName, projectsDirectory);
  }
  bool ProjectManager::NewProject(const std::string& projectName, const std::filesystem::path& containingFolder)
  {
    //std::filesystem::path projectsDirectory = CandyEngine::GetProjectsDirectory();
    std::filesystem::path projectDirectory = containingFolder / projectName;
    if (std::filesystem::exists(projectDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new project. Project already exists {0}", projectDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(projectDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new project directory {0}", projectDirectory.string());
      return false;
    }
    
    std::filesystem::path projectFile = projectDirectory;
    projectFile /= projectName;
    projectFile += CandyEngine::PROJECT_FILE_EXTENSION;
    if (! CreateEmptyFileAt(projectFile))
    {
      CANDY_CORE_ERROR("Failed to create new project. Failed to create project file {0}", projectFile.string());
      return false;
    }
    SharedPtr<Project> project = CreateSharedPtr<Project>(projectFile);
    
    /*if (! CreateProjectDirectories(*project))
    {
      CANDY_CORE_ERROR("Failed to create new project. Failed to create project directories");
      return false;
    }*/
    
    std::filesystem::path scenesPath = project->GetAssetsDirectory() / "scenes";
    if (!std::filesystem::create_directory(scenesPath))
    {
      CANDY_CORE_ERROR("Failed to create new project. Failed to create scenes directory {0}", scenesPath.string());
      return false;
    }
    
    /*project->metaData.startScenePath = scenesPath / "EmptyScene.scene";
    if (! CreateEmptyFileAt(project->metaData.startScenePath))
    {
      CANDY_CORE_ERROR("Failed to create empty scene file at {0}", project->metaData.startScenePath.string());
      return false;
    }*/
    
    try
    {
      std::filesystem::path sceneSource{CandyEngine::GetInternalAssetsDirectory() / "scenes" / "EmptyScene.scene"};
      std::filesystem::path sceneDestination{project->GetAssetsDirectory() / "scenes" / "EmptyScene.scene"};
      if (std::filesystem::copy_file(sceneSource, sceneDestination, std::filesystem::copy_options::overwrite_existing))
      {
        project->metaData.startScenePath = sceneSource;
        CANDY_CORE_INFO("Created new empty scene file for project: {0}", projectName);
      }
      else
      {
        CANDY_CORE_ERROR("Failed to create new empty scene file for project: {0}", projectName);
      }
    }
    catch(std::filesystem::filesystem_error& e)
    {
      CANDY_CORE_ERROR("Failed to copy empty scene file to {0}. Error: {1}", project->metaData.startScenePath.string(), e.what());
      return false;
    }
    
    project->metaData.engineVersion = CandyEngine::EngineVersion();
    project->metaData.applicationVersion = Version(0, 0, 1);
    //project->projectFilePath = projectFile;
    data.activeProject = project;
    CANDY_CORE_ASSERT(data.activeProject != nullptr, "Failed to create new project. Active project is null");
    return Serialize(project->metaData, project->projectFilePath);
    
  }
  
  /*bool ProjectManager::CreateProjectDirectories(const Project& project)
  {
    if (!std::filesystem::create_directory(project.assetsDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new assets directory {0}", project.assetsDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.cacheDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new cache directory {0}", project.cacheDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.packagesDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new packages directory {0}", project.packagesDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.libraryDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new library directory {0}", project.libraryDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.logsDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new logs directory {0}", project.logsDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.configDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new project settings directory {0}", project.configDirectory.string());
      return false;
    }
    if (!std::filesystem::create_directory(project.metaDirectory))
    {
      CANDY_CORE_ERROR("Failed to create new meta directory {0}", project.metaDirectory.string());
      return false;
    }
    return true;
  }*/
  bool ProjectManager::SaveProject()
  {
    if (data.activeProject)
    {
      if (IsValidProjectFileType(data.activeProject->projectFilePath))
      {
        return Serialize(data.activeProject->metaData, data.activeProject->projectFilePath);
      }
      else
      {
        CANDY_CORE_ERROR("Failed to save project. Invalid project file path stored {0}", data.activeProject->projectFilePath.string());
        return false;
      }
    }
    else
    {
      CANDY_CORE_ERROR("Failed to save project. No active project");
      return false;
    }
  }
  bool ProjectManager::SaveProjectAs(const std::filesystem::path& filepath)
  {
    if (data.activeProject)
    {
      
      if (IsValidProjectFileType(filepath))
      {
        //Create file in directory
        Serialize(data.activeProject->metaData, filepath);
        data.activeProject->projectFilePath = filepath;
        return Serialize(data.activeProject->metaData, filepath);
      }
      else
      {
        CANDY_CORE_ERROR("Cannot save project, file path {0} is not a valid project file type", filepath.string());
        return false;
      }
    }
    else
    {
      CANDY_CORE_ERROR("Cannot save project, no active project");
      return false;
    }
  }
  bool ProjectManager::LoadProject(const std::filesystem::path& projectPath)
  {
    CANDY_CORE_INFO("Loading project: {0}", projectPath.string());
    if (std::filesystem::is_directory(projectPath))
    {
      bool loaded = LoadProjectDirectory(projectPath);
      CANDY_CORE_INFO("Loaded project: {0}", projectPath.string());
      return loaded;
    }
    else if (std::filesystem::is_regular_file(projectPath))
    {
      std::filesystem::path projectDirectory = projectPath.parent_path();
      if (std::filesystem::exists(projectDirectory))
      {
        bool loaded = LoadProjectDirectory(projectDirectory);
        CANDY_CORE_INFO("Loaded project: {0}", projectPath.string());
        return loaded;
      }
      else
      {
        CANDY_CORE_ERROR("Cannot load project {0}, parent directory does not exist", projectPath.string());
        return false;
      }
    }
    else
    {
      CANDY_CORE_ERROR("Cannot load project {0}, path is not a directory or file", projectPath.string());
      return false;
    }
  }
  bool ProjectManager::LoadOrCreateProject(const std::string& projectName)
  {
    std::filesystem::path projectsDirectory = CandyEngine::GetProjectsDirectory();
    std::filesystem::path projectDirectory = projectsDirectory / projectName;
    if (std::filesystem::exists(projectDirectory))
    {
      return LoadProjectDirectory(projectDirectory);
    }
    else
    {
      return NewProject(projectName, projectsDirectory);
    }
  }
  bool ProjectManager::LoadProjectDirectory(const std::filesystem::path& projectDirectoryPath)
  {
    ProjectDirectoryValidationData validationData = ValidateProjectDirectory(projectDirectoryPath);
    if (validationData.IsValid())
    {
      return LoadProjectFile(validationData.candyFilePath.value());
    }
    else
    {
      CANDY_CORE_ERROR("Cannot load project directory {0}, failed to validate directory", projectDirectoryPath.string());
      return false;
    }
  }
  bool ProjectManager::LoadProjectFile(const std::filesystem::path& projectFilePath)
  {
    if (IsValidProjectFileType(projectFilePath))
    {
      SharedPtr<Project> project = CreateSharedPtr<Project>(projectFilePath);
      ProjectMetaData metaData;
      if (Deserialize(&metaData, projectFilePath))
      {
        project->projectFilePath = projectFilePath;
        project->metaData = metaData;
        data.activeProject = project;
        return true;
      }
      else
      {
        CANDY_CORE_ERROR("Failed to deserialize project file {0}", projectFilePath.string());
        return false;
      }
    }
    else
    {
      CANDY_CORE_ERROR("Cannot load project file {0}, path is not a valid project file type", projectFilePath.string());
      return false;
    }
  }
  const SharedPtr<Project>& ProjectManager::GetActiveProject()
  {
    return data.activeProject;
  }
  
  
  std::string ProjectManager::ProjectName()
  {
    if (data.activeProject)
    {
      return data.activeProject->projectFilePath.stem().string();
    }
    else
    {
      CANDY_CORE_ASSERT(false, "Cannot get project name, no active project");
      
      return "";
    }
  }
  const std::filesystem::path& ProjectManager::ProjectFilePath()
  {
    CANDY_CORE_ASSERT(data.activeProject, "Cannot get project file path, no active project");
    return data.activeProject->projectFilePath;
  }
  const ProjectMetaData& ProjectManager::GetMetaData()
  {
    CANDY_CORE_ASSERT(data.activeProject, "Cannot get project meta data, no active project");
    return data.activeProject->metaData;
  }
  const std::filesystem::path& ProjectManager::GetAssetsDirectory()
  {
    CANDY_CORE_ASSERT(data.activeProject, "Cannot get project assets directory, no active project");
    return data.activeProject->GetAssetsDirectory();
  }
  const std::filesystem::path& ProjectManager::GetConfigDirectory()
  {
    CANDY_CORE_ASSERT(data.activeProject, "Cannot get project config directory, no active project");
    return data.activeProject->GetResourceManager().GetConfigDirectory();
  }
  const std::filesystem::path& ProjectManager::GetStartScenePath()
  {
    CANDY_CORE_ASSERT(data.activeProject, "Cannot get project start scene path, no active project");
    return data.activeProject->metaData.startScenePath;
  }
  
  
  
  
  bool ProjectManager::Serialize(const ProjectMetaData& metaData, const std::filesystem::path& filepath)
  {
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    auto projectNode = root["Project"];
    projectNode |= c4::yml::MAP;
    
    projectNode["StartScene"] << metaData.startScenePath.string();
    projectNode["EngineVersion"] << metaData.engineVersion;
    projectNode["ApplicationVersion"] << metaData.applicationVersion;
    
    
    
    FILE* out = fopen(filepath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", filepath.string());
      return false;
    }
    c4::yml::emit_yaml(tree, out);
    fclose(out);
    return true;
  }
  
  bool ProjectManager::Deserialize(ProjectMetaData* metaData, const std::filesystem::path& filepath)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(metaData, "ProjectMetaData pointer is null, cannot deserialize project");
    CANDY_CORE_INFO("DESERIALIZING PROJECT");
    
    // read the file into a string
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath.string());
      return false;
    }
    // parse the YAML string
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto projectNode = root["Project"];
    if (projectNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize project file {0}. Empty Project Root Node", filepath.string());
      return false;
    }
    std::string startScenePath;
    projectNode["StartScene"] >> startScenePath;
    projectNode["EngineVersion"] >> metaData->engineVersion;
    projectNode["ApplicationVersion"] >> metaData->applicationVersion;
    
    
    metaData->startScenePath = startScenePath;
    
    return true;
  }
}