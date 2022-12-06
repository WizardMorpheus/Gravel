#pragma once

#include "Gravel\Core.h"
#include "Layer.h"

#include <vector>

namespace Gravel
{

	//	the LayerStack Class, acts as a container for layer pointers, allowing their order to be rearranged and for them to be accessed sequentialy.
	class GRAVEL_API LayerStack
	{
	public:
		//	default constructor and destrutor
		LayerStack();
		~LayerStack();

		//	push and pop functions 
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// begin() and end() functions, return the begin() and end() iterators of the layerstack.
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		//	the layerstack.
		std::vector<Layer*> m_Layers;
		//	an iterator for the layerstack.
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}