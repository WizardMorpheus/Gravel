#pragma once

#include "../Core.h"

#include <string>
#include <functional>



namespace Gravel
{
	//Currently events are handled when and where they occur, immediately.
	//regardless of frame, times etc. Will be changed later to avoid performance issues.

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
		ECat_Application	= BIT(0),
		ECat_Input			= BIT(1),
		ECat_Keyboard		= BIT(2),
		ECat_Mouse			= BIT(3),
		ECat_Mouse_Button	= BIT(4)
	};

	//macros
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType()						{return EventType::##type;}\
								virtual EventType GetEventType() const override			{return GetStaticType();}\
								virtual const char* GetName() const override			{return #type;}

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
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& E)
			: m_Event(E)
		{
		}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& E) { return os << E.ToString(); }

}
