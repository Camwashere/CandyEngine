#include <candy/app/Application.hpp>

#include <editor/EditorLayer.hpp>

using namespace Candy;




int main(int argc, char** argv)
{
 
  ApplicationData appData{"CandyApp", {1,0,0}};
  ApplicationCommandLineArgs commandLineArgs{argc, argv};
  appData.commandLineArgs = commandLineArgs;
  Application app(appData);
  SharedPtr<Project> proj = Project::Load("projects/TestProject/testProject.candy");
  
  EditorLayer editorLayer;
  app.PushLayer(&editorLayer);
  
 
  app.Run();
 
  
  
  return 0;
}
