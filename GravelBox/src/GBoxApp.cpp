#include <stdio.h>


#include <Gravel.h>


class ExampleLayer : public Gravel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GRAVEL_CLIENT_INFO("Example Layer:: Update");
	}

	void OnEvent(Gravel::Event& event) override
	{
		GRAVEL_CORE_TRACE("{0}", event);
	}
};


class GBox : public Gravel::Application
{
public:
	GBox()
	{
		PushLayer(new ExampleLayer);
	}

	~GBox()
	{

	}

};

Gravel::Application* Gravel::CreateApplication()
{
	return new GBox();
}
