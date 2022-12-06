#include <stdio.h>


#include <Gravel.h>


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


class GBox : public Gravel::Application
{
public:
	//default constructor
	GBox()
	{
		//pushes a new ExampleLayer to the new GBox's LayerStack
		PushLayer(new ExampleLayer);
	}

	//default destructor
	~GBox()
	{

	}

};


// external implementation of Gravel::CreateApplication referenced in 'Entry.h'
Gravel::Application* Gravel::CreateApplication()
{
	//creates a new GravelBox application, returns it and odes nothing else.
	return new GBox();
}
