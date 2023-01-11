#include "grvpch.h"
#include "WindowsInput.h"

#include "Gravel/Application.h"
#include "GLFW/glfw3.h"

namespace Gravel{
	
	Input* Input::s_Instance = new WindowsInput;

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(Window, keycode);
		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonDownImpl(int button)
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(Window, button);
		return state == GLFW_PRESS;

	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(Window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

}