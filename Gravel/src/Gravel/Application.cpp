#include "grvpch.h"

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

		for (int i = 0; i < 10000; i++) {
			WindowResizeEvent e(i, 10000-i);
			GRAVEL_CORE_WARN(e);
		}
		std::cin.get();
	}

}

