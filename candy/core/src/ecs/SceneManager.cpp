#include <candy/ecs/SceneManager.hpp>
//#include "SceneSerializer.hpp"
#include <utility>
#include <candy/app/Application.hpp>
namespace Candy::ECS
{
  
  SceneManager::SceneManager(const std::filesystem::path& path) : scenesPath(path), activeScene(nullptr)
  {
    /*if (std::filesystem::is_empty(path))
    {
        CANDY_CORE_INFO("CREATING NEW SCENE");
        CANDY_CORE_ASSERT(NewScene("Untitled"));
    }
    else
    {
        std::string name = "Untitled";
        if (!name.empty())
        {
            CANDY_CORE_INFO("LOADING START SCENE {}", name);
            if (LoadScene(name))
            {
                CANDY_CORE_INFO("LOADED SCENE: {}", name);
            }
            else
            {
                CANDY_CORE_ERROR("FAILED TO LOAD SCENE: {}", name);
            }
            
        }
        else
        {
            CANDY_ASSERT(false, "PICK STARTING SCENE WHEN NOT GIVEN NOT IMPLEMENTED IN SCENE MANAGER");
        }
    }*/
    
    
  }
  
  std::filesystem::path SceneManager::GetActiveScenePath() const
  {
    if (activeScene)
    {
      return scenesPath / GetSceneFileName(activeScene->name);
    }
    return scenesPath;
  }
  
  std::filesystem::path SceneManager::GetScenePath(const std::string &sceneName) const
  {
    return scenesPath / GetSceneFileName(sceneName);
  }
  
  bool SceneManager::DoesSceneExist(const std::string &sceneName) const
  {
    return std::filesystem::exists(scenesPath / GetSceneFileName(sceneName));
  }
  
  bool SceneManager::IsSceneLoaded() const
  {
    if (activeScene)
    {
      return true;
    }
    return false;
  }
  
  bool SceneManager::LoadScene(const std::string &sceneName)
  {
    if (DoesSceneExist(sceneName))
    {
      if (activeScene)
      {
        SaveActiveScene();
      }
      activeScene = CreateSharedPtr<Scene>(sceneName);
      /*SceneSerializer serializer(activeScene);
      if (serializer.Deserialize(GetScenePath(sceneName)))
      {
        CANDY_CORE_INFO("DESERIALIZED SCENE");
        return true;
      }
      else
      {
        CANDY_CORE_ERROR("FAILED TO DESERIALIZE SCENE");
      }*/
      activeScene = nullptr;
      return false;
    }
    return false;
  }
  
  bool SceneManager::LoadSceneFromPath(const std::filesystem::path &scenePath)
  {
    if (std::filesystem::exists(scenePath))
    {
      if (activeScene)
      {
        SaveActiveScene();
      }
      activeScene = CreateSharedPtr<Scene>();
     /*SceneSerializer serializer(activeScene);
      if (serializer.Deserialize(scenePath))
      {
        return true;
      }
      else
      {
        return false;
      }*/
    }
    return false;
  }
  
  bool SceneManager::SaveActiveScene()
  {
    if (activeScene)
    {
      /*SceneSerializer serializer(activeScene);
      return serializer.Serialize(GetScenePath(activeScene->name));*/
    }
    return false;
  }
  
  
  bool SceneManager::NewScene(const std::string &sceneName)
  {
    if (CanCreateScene(sceneName))
    {
      if (activeScene)
      {
        SaveActiveScene();
      }
      
      activeScene = CreateSharedPtr<Scene>(sceneName);
      std::ofstream stream(GetScenePath(sceneName));
      stream.close();
      return std::filesystem::exists(GetScenePath(sceneName));
    }
    return false;
  }
  
  bool SceneManager::CanCreateScene(const std::string& sceneName)const
  {
    return !std::filesystem::exists(scenesPath / GetSceneFileName(sceneName));
    
  }
}