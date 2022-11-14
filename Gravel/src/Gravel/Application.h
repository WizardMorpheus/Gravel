#pragma once
#include "grvpch.h"

#include "Core.h"

#include "Events/Event.h"
#include "Window.h"
#include "Events/Application_Event.h"


namespace Gravel {

	class GRAVEL_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();

}