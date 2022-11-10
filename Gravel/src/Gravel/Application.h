#pragma once

#include "Core.h"

#include "Events/Event.h"

namespace Gravel {

	class GRAVEL_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* CreateApplication();

}