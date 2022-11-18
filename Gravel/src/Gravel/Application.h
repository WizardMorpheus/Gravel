#pragma once

#include "grvpch.h"

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/Application_Event.h"
#include "LayerStack.h"


namespace Gravel {

	class GRAVEL_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	Application* CreateApplication();

}