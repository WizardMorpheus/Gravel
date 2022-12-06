#pragma once
#include "grvpch.h"

#include "../Core.h"


namespace Gravel
{
	//Currently events are handled when and where they occur, immediately.
	//regardless of frame, times etc. Will be changed later to avoid performance issues.

	//enum for different event types
	enum class EventType
	{
		None = 0,
		Window_Close, Window_Move, Window_Resize, Window_Focus, Window_UnFocus,
		App_Tick, App_Render, App_Update,
		Key_Down, Key_Up,
		Mouse_Button_Up, Mouse_Button_Down, Mouse_Moved, Mouse_Scrolled
	};


	//enum for different event Categories
	enum EventCategory
	{
		None = 0,
		ECat_Application	= BIT(0),
		ECat_Input			= BIT(1),
		ECat_Keyboard		= BIT(2),
		ECat_Mouse			= BIT(3),
		ECat_Mouse_Button	= BIT(4)
	};

	//macros that represent the code required to set an events type and categories as well as override relevent functions.
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType()						{return EventType::##type;}\
								virtual EventType GetEventType() const override			{return GetStaticType();}\
								virtual const char* GetName() const override			{return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override	{return category;}


	//event class
	class GRAVEL_API Event
	{
		//labelling the Event_Dispatcher as a friend class of the event.
		friend class EventDispatcher;
	public:
		//getters for various event variables.
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		//ToString() function allowing for the event to be converted into a message string and logged.
		virtual std::string ToString() const { return GetName(); }

		//funtion that returns bool for if an event belongs to a certain given category.
		inline bool Is(EventCategory C)
		{
			return GetCategoryFlags() & C;
		}

		// getter for handled bool
		bool Handled() const { return m_Handled; }
	protected:
		//bool representing whether the event has been handled yet.
		bool m_Handled = false;
	};


	//event d ispatcher class, friend of the event.
	class EventDispatcher
	{
		//"macro?". shorthand for describing a function that returns a bool and takes in a reference to a variable of Type T
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		//default constructor, takes a reference to an existing event and sets the dispatchers event variable to it.
		EventDispatcher(Event& E)
			: m_Event(E)
		{
		}

		/*	
			dispatch function, utilises the the above "macro?". Use the Dispatch function by giving it a Type(GRAVEL EVENT TYPE)
			and providing a std::bind to an event function as the parameter, which it will call when attempting to handle events of that type:

				Gravel::EventDispatcher dispatcher(Gravel::Event& e);
				dispatcher.Dispatch<Gravel::WindowCloseEvent>(std::bind(Gravel::Application::OnWindowClose&, this, std::placeholders::_1))
			
			the dispatcher will then handle the event it was created with if that event matches the type specified by the dispatch function.
		*/
		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			//checks if the event given to the dispatcher when constructed matches the type provided to the Dispatch() function
			// returns true if it is, false if it isn't
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				/*
					attempts to handle the event by passing it to the function specified when calling the Dispatch() function.
					if that function (which must return a bool as predetermined by the "macro?") returns true, the event is handled,
					else it is not and the event is passed to the next possible handler.
				*/
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		// event reference to the event passed to the dispatcher upon construction.
		Event& m_Event;
	};

	/*
		operator overload that overloads the insertion operator ( << ) (used when calling io functions for loggers)
		it inserts the message string returned by the ToString() function into the output stream, usually a logger.
	*/
	inline std::ostream& operator<<(std::ostream& os, const Event& E) { return os << E.ToString(); }

}
