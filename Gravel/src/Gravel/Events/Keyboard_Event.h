#pragma once

#include "Event.h"

#include <sstream>

namespace Gravel
{

	class GRAVEL_API KeyboardEvent : public Event
	{
		inline int GetKeyCode() const { return KeyCode; }

		// macro goes here
	protected:
		KeyboardEvent(int keycode)
			: KeyCode(keycode) {}

		int KeyCode;
	};


	class GRAVEL_API KeyDownEvent : public KeyEvent
	{
		KeyDownEvent(int keycode, int repeatcount)
			: KeyEvent(keycode), RepeatCount(repeatcount) {}

		inline int GetRepeatCount() const { retun RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		//insert other macro here 
	private:
		int RepeatCount;
	};


}