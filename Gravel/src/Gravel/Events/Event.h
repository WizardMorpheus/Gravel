#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace Gravel
{
	//Currently events are handled when and where they occur, immediately.
	//regardles of frame, times etc. Will be changed later to avoid performance issues.

	enum class EventType
	{
		None = 0,
		Window_Close, Window_Move, Window_Resize, Window_Focus, Window_UnFocus,
		App_Tick, App_Render, App_Update,
		Key_Down, Key_Up,
		Mouse_Button_Up, Mouse_Button_Down, Mouse_Moved, Mouse_Scrolled
	};

	enum EventCategory
	{
		None = 0,
		Application		= BIT(0),
		Input			= BIT(1),
		Keyboard		= BIT(2),
		Mouse			= BIT(3),
		Mouse_Button	= BIT(4)
	};

	//macros
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType()						{return EventType::##type;}\
								virtual EventType GetEventType() const override			{return GetStaticType();}\
								virtual const char* GetName const override				{return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override	{return category;}


	class GRAVEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool Is(EventCategory C)
		{
			return GetCategoryFlags() & C;
		}
	protected:
		bool Handled = false;
	};

}