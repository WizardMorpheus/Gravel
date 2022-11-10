#pragma once

#include "Event.h"

#include <sstream>

namespace Gravel
{

	class GRAVEL_API KeyboardEvent : public Event
	{
		inline int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(ECat_Input | ECat_Keyboard);
	protected:
		KeyboardEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};


	class GRAVEL_API KeyDownEvent : public KeyboardEvent
	{
		KeyDownEvent(int keycode, int repeatcount)
			: KeyboardEvent(keycode), m_RepeatCount(repeatcount) {}

		inline int GetRepeatCount() const { retun RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Down)
	private:
		int m_RepeatCount;
	};


	class GRAVEL_API KeyUpEvent : public: KeyboardEvent
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
	}

}