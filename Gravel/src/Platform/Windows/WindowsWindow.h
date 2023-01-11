#pragma once

#include "Gravel/Window.h"

#include <GLFW/glfw3.h>

struct GLFWWindow;

//	implementation for Window class on thw Windows OS.
namespace Gravel
{
	//	subclass for windows OS
	class WindowsWindow : public Window
	{
	public:
		//	default constructor and destructor.
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		//	overrides the OnUpdate() function.
		void OnUpdate() override;

		//	overrides the width and height getters.
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }


		//	overrides the event callback, and VSync functions.
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;


		// OS specific Impl of the GetNativeWindow() getter.   returns the pointer to the GLFW Window.
		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		//	Initialise and shutdown functions.
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		//	the pointer variable for the window.
		GLFWwindow* m_Window;

		//	the struct for the window data to be stored.
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		//	window data variable.
		WindowData m_Data;
	};
}