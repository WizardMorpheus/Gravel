#include "Application.h"
#include "Events/Application_Event.h"
#include "Gravel/Log.h"

namespace Gravel {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		GRAVEL_CLIENT_DEBUG(e);


		while (true);
	}

}

