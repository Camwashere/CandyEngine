#include <candy/app/Application.hpp>
#include "TestLayer.hpp"
#include <editor/EditorLayer.hpp>
using namespace Candy;
int main(int argc, char** argv)
{
  
  ApplicationData appData{"CandyApp", {1,0,0}};
  ApplicationCommandLineArgs commandLineArgs{argc, argv};
  appData.commandLineArgs = commandLineArgs;
  Application app(appData);
  ProjectConfig config{"Candy Project", "assets", "assets", appData.version};
  Project project(config);
  EditorLayer editorLayer(&project);
  app.PushLayer(&editorLayer);
  
  //TestLayer testLayer;
  //app.PushLayer(&testLayer);
  //CANDY_PROFILE_END_SESSION();
  app.Run();
  CANDY_CORE_INFO("Application exited");
  
  
  return 0;
}
