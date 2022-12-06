#pragma once
#include "grvpch.h"

#include "Event.h"


namespace Gravel
{

	//creation of Window Specific events 


	//the window resize event, inherits from the basic event class
	class GRAVEL_API WindowResizeEvent : public Event
	{
	public:
		//constructor that sets the width(m_Width) and height(m_Height) variables to those specified.
		WindowResizeEvent(unsigned int Width, unsigned int Height)
			: m_Width(Width), m_Height(Height) {}

		// getters for the width and height of the window respectively.
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		//override for the Event::ToString() function, allows for the event to called by the logging macros
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		//sets the event class type and category
		EVENT_CLASS_TYPE(Window_Resize)
		EVENT_CLASS_CATEGORY(ECat_Application)

	private:
		//Width and Height variables for the window
		unsigned int m_Width, m_Height;
	};


	//the window close event, believe it or not it closes the window
	class GRAVEL_API WindowCloseEvent : public Event
	{
	public:
		//default constructor
		WindowCloseEvent() {}

		//sets the event class type and category
		EVENT_CLASS_TYPE(Window_Close)
		EVENT_CLASS_CATEGORY(ECat_Application)
	};


	//Application tick event
	class GRAVEL_API AppTickEvent : public Event
	{
	public:
		//default constructor
		AppTickEvent() {}

		//sets the event c;ass type and category
		EVENT_CLASS_TYPE(App_Tick)
		EVENT_CLASS_CATEGORY(ECat_Application)
	};

	//application update event, called whenever the event updates lad
	class GRAVEL_API AppUdateEvent : public Event
	{
	public:
		//default constructor
		AppUdateEvent() {}

		//sets the event class type and category
		EVENT_CLASS_TYPE(App_Update)
		EVENT_CLASS_CATEGORY(ECat_Application)
	};

	// the application render event, called whenever the application has to render, AKA every frame
	class GRAVEL_API AppRenderEvent : public Event
	{
	public:
		//default constructor
		AppRenderEvent() {}

		//sets the event class type and category.
		EVENT_CLASS_TYPE(App_Render)
		EVENT_CLASS_CATEGORY(ECat_Application)
	};

}