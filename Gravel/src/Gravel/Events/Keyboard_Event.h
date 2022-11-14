#pragma once
#include "grvpch.h"

#include "Event.h"

namespace Gravel
{

	class GRAVEL_API KeyboardEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(ECat_Input | ECat_Keyboard);
	protected:
		KeyboardEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};


	class GRAVEL_API KeyDownEvent : public KeyboardEvent
	{
	public:
		KeyDownEvent(int keycode, int repeatcount)
			: KeyboardEvent(keycode), m_RepeatCount(repeatcount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Down)
	private:
		int m_RepeatCount;
	};


	class GRAVEL_API KeyUpEvent : public KeyboardEvent
	{
	public:
		KeyUpEvent(int keycode)
			: KeyboardEvent(keycode) {}

		std::string ToString()
		{
			std::stringstream ss;
			ss << "KeyUpEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Up)
	};

}