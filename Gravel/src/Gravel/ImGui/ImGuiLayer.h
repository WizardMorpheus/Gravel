#pragma once

#include "Gravel/Layer.h"
#include "Gravel/Events/Keyboard_Event.h"
#include "Gravel/Events/Mouse_Event.h"
#include "Gravel/Events/Application_Event.h"

//	Layer declaration for the ImGuiLayer.
//	this is a debug overlayer that is always the final layer to be rendered.

namespace Gravel 
{
	
	class GRAVEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttatch();
		void OnDetatch();
		void OnUpdate();
		void OnEvent(Event& event);
	private: 

		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseButtonDownEvent(MouseButtonDownEvent& e);
		bool OnMouseButtonUpEvent(MouseButtonUpEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyDownEvent(KeyDownEvent& e);
		bool OnKeyUpEvent(KeyUpEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


		float m_Time = 0.0f;
	};

}

