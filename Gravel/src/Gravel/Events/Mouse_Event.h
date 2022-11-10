pragma once

#include "Event.h"

#include <sstream>

namespace Gravel
{

	class GRAVEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX, << ", " m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Moved)
		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Input)
	private:
		float m_MouseX, m_MouseY;
	};


	class GRAVEL_API MouseScrolledEvent : public Event 
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Scrolled)
		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Input)

	private:
		float m_xOffset, m_yOffset;
	};


	class GRAVEL_API MouseButtonEvent : public Event 
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(ECat_Mouse | ECat_Mouse_Button)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}
		int m_Button;
	};


	class GRAVEL_API MButtonDownEvent : public MouseButtonEvent
	{
	public:
		MButtonDownEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Button_Down)
	};

	class GRAVEL_API MButtonDownEvent : public MouseButtonEvent
	{
	public:
		MButtonDownEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Button_Up)
	};
}