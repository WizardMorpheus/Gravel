#include "grvpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace Gravel {
	//	implementation of the Application class held by the Application.h file


	//macro that binds a function x using std::bind
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;


	//	default constructor. sets the window variable to a new windwo which is created when the constructor is called.
	//	sets the event callback of the window to the OnEvent()
	Application::Application() 
	{
		GRAVEL_CORE_ASSERT(!s_Instance, "Application Already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	}

	//default destructor
	Application::~Application()
	{
	}

	//pushlayer() function, pushes a layer onto the end of the layerstack.
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		//	calls the OnAttach Callback for the layer that was attatched.
		layer->OnAttatch();
	}

	//pushoverlay() function, pushes a layer as an overlay to the front of the layerstack.
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		//	calls the OnAttach Callback for the layer that was attatched.
		layer->OnAttatch();
	}


	//	the OnEvent() function, dispatches window close events, loggs events,
	//	then proceeds to pass events through the layerstack
	void Application::OnEvent(Event& e)
	{

		//	creates a dispatcher to dispatch the window close event specifically, closes the window if the event is one.
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

		//	loggs the event using the logging macros defined in the log.h file
		GRAVEL_CLIENT_TRACE(e);

		//	passes the event through the layerstack, calling the OnEvent() function for each layer on the event 
		//	the OnEvent() function is defined separately for each Layer upon its creation as a subclass. 
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			//	calls the OnEvent() function on the event for the layer
			(*--it)->OnEvent(e);
			//	if the event has now been handled, breaks from the loop so that processing is not done twice.
			if (e.Handled())
				break;
		}

	}
		

	//	the run() function, contains the code that runs whenever an application is told to run.
	void Application::run()
	{
		//	while the application is running, this continues untill the WindowClose Event occurrs.
		while (m_Running)
		{
			//sets the window colour to that specified (currently Magenta)
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// calls the OnUpdate Function for all layers throughout the LayerStack.
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//do stuff

			auto [x, y] = Input::GetMousePos();
			GRAVEL_CORE_TRACE("mouse pos : {0}, {1}", x, y);


			//	calls the OnUpdate function for the window.
			m_Window->OnUpdate();
		}
	}


	//	OnWindowClose Event, sets the 'running' bool to false, exiting the while loop in the run() function
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

