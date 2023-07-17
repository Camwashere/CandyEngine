#include <CandyPch.hpp>
#include <candy/math/Math.hpp>
#include <iostream>

#include <candy/utils/FrameTime.hpp>
#include <candy/app/Application.hpp>
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
using namespace Candy;
int main(int argc, char** argv)
{
  std::cout << "STARTING MAIN" << std::endl;
  ApplicationData appData{"CandyApp", 1.0};
  ApplicationCommandLineArgs commandLineArgs{argc, argv};
  appData.commandLineArgs = commandLineArgs;
  Application app(appData);
  FrameTime frameTime;
  frameTime.Update();
  CANDY_CORE_INFO(frameTime.GetDeltaTime());
  
  std::cout << "Created App" << std::endl;
  //CANDY_PROFILE_END_SESSION();
  app.Run();
  
  
  return 0;
}
