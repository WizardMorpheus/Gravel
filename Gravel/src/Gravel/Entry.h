#pragma once
#include "grvpch.h"

//	this file aacs as the entry point for Gravel Applications

//	checks if the operating system is Windows.
#ifdef GRAVEL_PLATFORM_WINDOWS

//	declares a function CreateApplication(), that is to be defined elsewhere (inside Application.h)
extern Gravel::Application* Gravel::CreateApplication();

//	the main function of the entire project.
int main(int argc, char** argv) 
{
	//	initialises the logging system.
	Gravel::Log::Init();

	//	test log
	int t = 13;
	GRAVEL_CORE_INFO("testing core: {0}", t);

	//	creates a new Application called app, runs it, then deletes it.
	auto app = Gravel::CreateApplication();
	app->run();
	delete app;
}

#endif