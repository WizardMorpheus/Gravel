#pragma once

#include "Gravel\Core.h"
#include "Gravel\Events\Event.h"

namespace Gravel
{

	//	the Layer Class.
	class GRAVEL_API Layer
	{
	public:
		//	default constructor and destructor
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		
		//	functions to be implemented when creating a subclass of Application 
		//	these functions should occurr whenever their names would suggests.
		virtual void OnAttatch() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		//	const getter function returns the debug name of the layer.
		inline const std::string GetName() const { return m_DebugName; }
	protected:
		//	debug name variable.
		std::string m_DebugName;
	};

}
