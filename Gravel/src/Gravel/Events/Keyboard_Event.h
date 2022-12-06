#pragma once
#include "grvpch.h"

#include "Event.h"

namespace Gravel
{
	//creation of various event subclasses that are affiliated with the keyboard


	//base keyboard event class. includes all data shared by any keyboard event.
	class GRAVEL_API KeyboardEvent : public Event
	{
	public:
		//	getter for the keycode of the keyboard event.
		inline int GetKeyCode() const { return m_KeyCode; }

		//sets the event class category using the macro defined in the Event.h file
		EVENT_CLASS_CATEGORY(ECat_Input | ECat_Keyboard);
	protected:
		//default constructor, will only ever be used by subclasses and therefore exists within the protected scope.
		//sets the keycode variable to the keycode given in the parameter
		KeyboardEvent(int keycode)
			: m_KeyCode(keycode) {}

		//keycode variable
		int m_KeyCode;
	};


	//keyDown event
	class GRAVEL_API KeyDownEvent : public KeyboardEvent
	{
	public:
		//default constructor takes a keycode and repeat count as parameters
		//sets the keycode variable by calling the default constructor for the base class, and then sets the repeat count variable.
		KeyDownEvent(int keycode, int repeatcount)
			: KeyboardEvent(keycode), m_RepeatCount(repeatcount) {}

		//getter for the repeat count
		inline int GetRepeatCount() const { return m_RepeatCount; }

		//override for the toString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		//sets the event class type using the macro defined in the Event.h file
		EVENT_CLASS_TYPE(Key_Down)
	private:
		//repeat count variable.
		int m_RepeatCount;
	};


	//keyUp event
	class GRAVEL_API KeyUpEvent : public KeyboardEvent
	{
	public:
		//default constructor, takes a keycode as only parameter
		//sets teh keycode variable by calling the base class default constructor.
		KeyUpEvent(int keycode)
			: KeyboardEvent(keycode) {}

		//override for the ToString() function
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyUpEvent: " << m_KeyCode;
			return ss.str();
		}

		//sets the event class type using the macro defined in the Event.h file.
		EVENT_CLASS_TYPE(Key_Up)
	};

}