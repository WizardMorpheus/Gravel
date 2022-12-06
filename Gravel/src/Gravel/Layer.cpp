#include "grvpch.h"
#include "Layer.h"


/*
*	implementation of some of the functions within the Layer Class.
*	other functions should be implemented by creating a subclass in the Application project and defined there.
*	eg.

class ExampleLayer : public Gravel::Layer
{
public:
	//constructor for example layer
	ExampleLayer()
		: Layer("Example")
	{
	}

	//overrides Layer::OnUpdate() to log an update message using the client logger.
	void OnUpdate() override
	{
		GRAVEL_CLIENT_INFO("Example Layer:: Update");
	}

	//overrides Layer::OnEvent() to log an Event message using the core logger.
	void OnEvent(Gravel::Event& event) override
	{
		GRAVEL_CORE_WARN("{0}", event);
	}
}; 

*/
namespace Gravel
{
	//default constructor, sets the name of the layer (only to be seen in debug) to the one given.
	Layer::Layer(const std::string& name)
		: m_DebugName(name)
	{
	}

	//	default destructor.
	Layer::~Layer()
	{
	}
}