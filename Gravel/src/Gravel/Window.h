#pragma once

#include "grvpch.h"

#include "Gravel/Core.h"
#include "Gravel/Events/Event.h"


//	base class structure for window, to be extended and abstracted to work on different operating systems.
namespace Gravel
{

	//	window properties struct.
	struct WindowProps
	{
		//	title of the window, its width and height in pixels.
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//	default constructor, Creates window properties for a window titled "Gravel Engine", at 720p resolution.
		WindowProps(const std::string& title = "Gravel Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};


	//desktop system based window interface
	class GRAVEL_API Window
	{
	public:
		//	"macro?" for declaring a function that returns void and takes an Event& as only parameter.
		using EventCallbackFn = std::function<void(Event&)>;

		//	default destructor, to be implemented on platform specific basis.
		virtual ~Window() {}

		//	OnUpdate() function, called when the window updates, implemented platform specific.
		virtual void OnUpdate() = 0;

		//	getters for the width and height of the window.
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;


		//	sets the callback function for events for the window, implemented platform specific.
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		//	enables or disables VSync for the window, implemented platform specific.
		virtual void SetVSync(bool enabled) = 0;
		//	returns true if VSync is enabled.
		virtual bool IsVSync() const = 0;

		//	Create() function for a window. creates a window and returns it's pointer.
		static Window* Create(const WindowProps& props = WindowProps());
	};

}