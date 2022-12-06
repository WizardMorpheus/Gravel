#pragma once
#include "grvpch.h"

#include "Event.h"

namespace Gravel
{
	//creation of all event subclasses affiliated with the mouse.


	//the MouseMoved Event
	class GRAVEL_API MouseMovedEvent : public Event
	{
	public:
		//default constructor, sets the internal mouse x and y variables to the ones given as parameters
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		//	getters for the mouse x and y values in this Event
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		//override for the Event::ToString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		//	sets the event clas type and categories using the macros defined in the Event.h file
		EVENT_CLASS_TYPE(Mouse_Moved)
		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Input)
	private:
		//	mouse x and y values for this event.
		float m_MouseX, m_MouseY;
	};


	//the mouseScrolled Event
	class GRAVEL_API MouseScrolledEvent : public Event 
	{
	public:
		//default constructor, sets the x and t offset variables to the ones specified in parameters.
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		//	getters for the x and y offset variables
		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		//	override of the Event::ToString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		//	sets the event class type and categories using the macros defined in the Event.h file
		EVENT_CLASS_TYPE(Mouse_Scrolled)
		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Input)

	private:
		//	x and y offset variables.
		float m_xOffset, m_yOffset;
	};


	//	the mouseButton event, base class for mouse down and up.
	class GRAVEL_API MouseButtonEvent : public Event 
	{
	public:
		// getter for the button that was pressed.
		inline int GetMouseButton() const { return m_Button; }

		//sets the event class categories using the macro defined in the Event.h file.
		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Mouse_Button)
	protected:
		//default constructor, sets the button variable to the one given as parameter
		//only used by subclasses so exists in the protected scope.
		MouseButtonEvent(int button)
			: m_Button(button) {}
		//the button variable representing which button was pressed.
		int m_Button;
	};


	//	the MouseButtonDown Event
	class GRAVEL_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		//default constructor, sets the button variable to the one given as parameter by calling the base class constructor.
		MouseButtonDownEvent(int button)
			: MouseButtonEvent(button) {}

		//	override for the Event::ToString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << m_Button;
			return ss.str();
		}

		//	sets the event class type using the macro defined in the Event.h file.
		EVENT_CLASS_TYPE(Mouse_Button_Down)
	};


	//	the MouseButtonUp Event
	class GRAVEL_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		//	default constructor, set the button variable to the one specified in parameter by calling the base class constructor.
		MouseButtonUpEvent(int button)
			: MouseButtonEvent(button) {}


		//	override for the Event::ToString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << m_Button;
			return ss.str();
		}

		//	sets the event class type using the macro defined in the Event.h file.
		EVENT_CLASS_TYPE(Mouse_Button_Up)
	};
}