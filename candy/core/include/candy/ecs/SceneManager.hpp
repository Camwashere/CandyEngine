#pragma once
#include "Scene.hpp"
namespace Candy::ECS
{
  class SceneManager
  {
  private:
    static constexpr const char* SCENE_FILE_EXTENSION=".scene";
    static constexpr std::string GetSceneFileName(const std::string& sceneName){return sceneName + SCENE_FILE_EXTENSION;}
  
  private:
    std::filesystem::path scenesPath;
    SharedPtr<Scene> activeScene;
  
  private:
    [[nodiscard]] bool CanCreateScene(const std::string& sceneName)const;
  
  
  public:
    explicit SceneManager(const std::filesystem::path&  scenesPath);
  
  public:
    std::filesystem::path GetActiveScenePath()const;
    std::filesystem::path GetScenePath(const std::string& sceneName)const;
    const std::filesystem::path& GetScenesPath()const{return scenesPath;}
    const SharedPtr<Scene>& GetActiveScene()const{return activeScene;}
    bool DoesSceneExist(const std::string& sceneName)const;
    bool IsSceneLoaded()const;
    bool LoadScene(const std::string& sceneName);
    bool LoadSceneFromPath(const std::filesystem::path& scenePath);
    bool SaveActiveScene();
    bool NewScene(const std::string& sceneName);
    
    
  };
}