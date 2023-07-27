#include <candy/app/Application.hpp>
#include "TestLayer.hpp"
using namespace Candy;
int main(int argc, char** argv)
{
  
  ApplicationData appData{"CandyApp", 1.0};
  ApplicationCommandLineArgs commandLineArgs{argc, argv};
  appData.commandLineArgs = commandLineArgs;
  Application app(appData);
  TestLayer testLayer;
  app.PushLayer(&testLayer);
  //CANDY_PROFILE_END_SESSION();
  app.Run();
  
  
  
  return 0;
}
