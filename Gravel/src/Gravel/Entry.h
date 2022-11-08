#pragma once

#ifdef GRAVEL_PLATFORM_WINDOWS

extern Gravel::Application* Gravel::CreateApplication();

int main(int argc, char** argv) 
{
	printf("Gravel_Engine..");
	auto app = Gravel::CreateApplication();
	app->run();
	delete app;
}

#endif