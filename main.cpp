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
  
 
  app.Run();
 
  
  
  return 0;
}
