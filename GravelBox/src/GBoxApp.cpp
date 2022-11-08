#include <stdio.h>


#include <Gravel.h>



class GBox : public Gravel::Application
{
public:
	GBox()
	{

	}

	~GBox()
	{

	}

};

Gravel::Application* Gravel::CreateApplication()
{
	return new GBox();
}
