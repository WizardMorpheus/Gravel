#include "grvpch.h"
#include "LayerStack.h"

//	implementation of the LayerStack Class.

namespace Gravel
{
	//	default constructor, sets the layer insert variable (an iterator for the larystack) to the begin() of the layerstack.
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	//	default destructor, iterates through the stack and deletes all the layers.
	LayerStack::~LayerStack()
	{
		for (Layer* Layer : m_Layers)
			delete Layer;
	}

	/*
		pushLayer() takes a pointer to a layer as referenceand places that pointer into the position specified by m_LayerInsert(usually begin())
		then sets m_:ayerInsert to the new value relative.
	*/
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	//	PushOverlay(), pushes a layerpointer to the end() of the LayerStack, therfore acting as an Overlay.
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}


	//removes a Layer from the layerstack after finding it.
	void LayerStack::PopLayer(Layer* layer)
	{
		//	finds the iterator associated with the layer in question
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		//	checks if a layer is actually found.
		if (it != m_Layers.end())
		{
			//	erases the layer.
			m_Layers.erase(it);
			//	sets m_LayerInsert to the new respective value.
			m_LayerInsert--;
		}
	}

	//	same thing as above but for overlays.
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}


}