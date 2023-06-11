#pragma once

#include "../../core/application/Application.hpp"
#ifdef CANDY_PLATFORM_WINDOWS

extern Candy::Application* Candy::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    std::cout << "Started main" << std::endl;
    Candy::Log::Init();
    CANDY_CORE_INFO("Initialized Logging");
    
	auto app = Candy::CreateApplication({ argc, argv });
    
    CANDY_CORE_INFO("Created Application");
    CANDY_CORE_INFO("Running application");
    
	app->Run();


    CANDY_CORE_INFO("Deleting application");
	delete app;
	
}

#endif