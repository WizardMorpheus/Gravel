#pragma once

#include "Core.h"

namespace Gravel {

	class GRAVEL_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* CreateApplication();

}