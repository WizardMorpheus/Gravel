#pragma once

#ifdef GRAVEL_PLATFORM_WINDOWS

extern Gravel::Application* Gravel::CreateApplication();

int main(int argc, char** argv) 
{
	Gravel::Log::Init();

	int t = 13;
	GRAVEL_CORE_INFO("testing core: {0}", t);




	auto app = Gravel::CreateApplication();
	app->run();
	delete app;
}

#endif