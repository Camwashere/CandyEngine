#pragma once
#include "../../core/base/general/CandyCoreBase.hpp"
#include "../../core/base/debug/Profiler.hpp"
#include "../../core/application/Application.hpp"

#ifdef CANDY_PLATFORM_WINDOWS

extern Candy::Application* Candy::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{

    //CANDY_PROFILE_BEGIN_SESSION("Startup", "CandyProfile-Startup.json");
	auto app = Candy::CreateApplication({ argc, argv });
	//CANDY_PROFILE_END_SESSION();

	//CANDY_PROFILE_BEGIN_SESSION("Runtime", "CandyProfile-Runtime.json");
	app->Run();
	//CANDY_PROFILE_END_SESSION();

	//CANDY_PROFILE_BEGIN_SESSION("Shutdown", "CandyProfile-Shutdown.json");
	delete app;
	//CANDY_PROFILE_END_SESSION();
}

#endif