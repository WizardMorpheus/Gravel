#include "grvpch.h"
#include "Gravel/Log.h"
#include "WindowsWindow.h"

#include "Gravel\Events\Application_Event.h"
#include "Gravel\Events\Keyboard_Event.h"
#include "Gravel\Events\Mouse_Event.h"

#include <glad/glad.h>

//	implementation of the WindowsWindow Class
namespace Gravel
{

	//	boolean representing whether GLFW has been initialised.
	//	makes sure it is not initialised twice.
	static bool s_GLFWInitialized = false;

	//	function that is called whenever, GLFW encounters an error, loggs the error using the ERROR CORE logger.
	static void GLFWErrorCallback(int error, const char* description)
	{
		GRAVEL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	//	window create function, returns a pointer to a window with the window properties specified.
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	//	default constructor, initialises the window with the properties given.
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	//	default destructor,calls the shutdown() function.
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	//	Initialise function.
	void WindowsWindow::Init(const WindowProps& props)
	{
		//	sets the windows variables to those inside the given props.
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		//	loggs the creation of the window.
		GRAVEL_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		//	checks if GLFW has been initialised yet.
		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			//	attempts to Initialise GLFW.
			int success = glfwInit();
			//	uses debug asserts to logg if GLFW could not initialise.
			GRAVEL_CORE_ASSERT(success, "Could not Initialize GLFW!");
			//	sets the actual glfwErrorCallback to the one created above.
			glfwSetErrorCallback(GLFWErrorCallback);
			//	sets the GLFWInitialised variable to true, so the GLFW is not initialised twice.
			s_GLFWInitialized = true;
		}

		//	sets the window variable to a new glfw Window with the windows properties.
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//	sets the current context of GLFW to the window that was just created.
		glfwMakeContextCurrent(m_Window);
		// initialses GLAD by setting its status to the status based from the glfw Proc
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//	assert to inform in debug if GLAD has not loaded correctly
		GRAVEL_CORE_ASSERT(status, "failed to initialise GLAD");
		//	IDK what this does yet have to look up.
		glfwSetWindowUserPointer(m_Window, &m_Data);
		//	turns on VSync.
		SetVSync(true);





		//-----------------SetGLFW Callbacks----------------

		//	changes the width and height variables for the window to the new ones after resize.
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//	gets the data for the window.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//	sets the W and H variables to the new ones.
				data.Width = width;
				data.Height = height;

				//	loggs the resize event.
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		//	sets the callback function for the closing of a window.
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				//	gets the window data
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//	creates a window close event.
				WindowCloseEvent event;
				//	calls the window event callback function on the WindowClose Event, resulting in the shutdown() function.
				data.EventCallback(event);
			});


		//	sets the callback for keyboad events when the window is in focus.
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				//	gets the window data.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				//	checks the action type.
				switch (action)
				{
					case GLFW_PRESS:
					{
						//	creates a keydown event and sends it to callback.
						KeyDownEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						//	creates a keyup event and sends it to callback.
						KeyUpEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						//	creates a keydown event with repeat and sends it to callback.
						KeyDownEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});



		//	sets the callback for mouse button events when the window is in focus.
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
			{
				//	gets the window data.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//	checks the action type of the event.
				switch (action)
				{
					case GLFW_PRESS:
					{
						//	creates a MouseButtonDown Event and sends it to callback.
						MouseButtonDownEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						//	creates a MouseButtonUp Event and sends it to callback.
						MouseButtonUpEvent event(button);
						data.EventCallback(event);
						break;
					}
				}

			});


		//	sets the callback for when the mouse is scrolled and the window is in focus.
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				//	gets teh window data.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				//	creates a Mouse Scrolled event with the x and y offsets  and sends it to callback.
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);

			});

		//	sets the callback for a change in the cursor position when the window is in focus.
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				//	gets the window data.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				//	creates a MouseMoved event with the new mouse position and sends it to callback.
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	//	shutdown() function, destroys the glfwWindow.
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	//	onUpdat() function, polls event and swaps buffers.
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	//	Turns VSync for the window on or off.
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	//	returns true if VSync is enabled for the window.
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}