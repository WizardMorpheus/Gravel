#include "grvpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGlRenderer.h"
#include "GLFW/glfw3.h"

//TEMP
#include "Gravel/Application.h"
#include "glad/glad.h"

//	Layer definitions for the ImGuiLayer.
//	this is a debug overlayer that is always the final layer to be rendered.

namespace Gravel
{

	//	default constructor, 
	//	creates a Layer with the debug name "ImgUILayer"
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	//	default destructor.
	ImGuiLayer::~ImGuiLayer()
	{
	}


	//	declaration for the Layer Attatchment Callback
	void ImGuiLayer::OnAttatch()
	{

		//	Initialises ImGui by creating the context and setting the colout scheme
		ImGui::CreateContext();
		ImGui::StyleColorsDark();


		//	creates an ImGui IO object by retrieving the IO reference.
		ImGuiIO& io = ImGui::GetIO();
		//	setting backend flags so that ImGui understands that this application uses the cursor
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//	setting of keycodes.
		// TEMPORARY: should eventually use Gravel key codes
		io.KeyMap[ImGuiKey_Tab]			= GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]	= GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow]	= GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]		= GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]	= GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]		= GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]	= GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]		= GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End]			= GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert]		= GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]		= GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]	= GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]		= GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]		= GLFW_KEY_ENTER; 
		io.KeyMap[ImGuiKey_Escape]		= GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A]			= GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C]			= GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V]			= GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X]			= GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y]			= GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z]			= GLFW_KEY_Z;

		//	initialises OpenGl3 for ImGui.
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	//	callback for when the layer is detatched from the layerstack.
	void ImGuiLayer::OnDetatch()
	{

	}

	//	callback for when the application updates and causes all of its layers to update aswell.
	void ImGuiLayer::OnUpdate()
	{

		//	retireves the IO so that information always remains current.
		ImGuiIO& io = ImGui::GetIO();
		//	retrives the application reference.
		Application& app = Application::Get();
		//	sets the Displaysize of the ImGui IO to the applications width and height so that on each frame the
		//	io is set to the same size as the window.
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//	calculates the time sionce the application has begun running.
		//		NOT ENTIRELY SURE WHY      1.0f - 60.0f
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f - 60.0f);
		m_Time = time;

		//	creates a new frame for ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//	shows the demo Window 
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		//	renders ImGui.
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	//	the callback for when Events occur on the ImGui Layer.
	void ImGuiLayer::OnEvent(Event& event)
	{
		//	dispatches all incoming relevant events through the dispatcher system.
		EventDispatcher Dispatcher(event);
		Dispatcher.Dispatch<MouseMovedEvent>		(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnMouseMovedEvent));
		Dispatcher.Dispatch<MouseButtonDownEvent>	(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnMouseButtonDownEvent));
		Dispatcher.Dispatch<MouseButtonUpEvent>		(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnMouseButtonUpEvent));
		Dispatcher.Dispatch<MouseScrolledEvent>		(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnMouseScrolledEvent));
		Dispatcher.Dispatch<KeyDownEvent>			(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnKeyDownEvent));
		Dispatcher.Dispatch<KeyUpEvent>				(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnKeyUpEvent));
		Dispatcher.Dispatch<KeyTypedEvent>			(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnKeyTypedEvent));
		Dispatcher.Dispatch<WindowResizeEvent>		(GRAVEL_BIND_EVENT_FNC(ImGuiLayer::OnWindowResizeEvent));

	}


	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}


	bool ImGuiLayer::OnMouseButtonDownEvent(MouseButtonDownEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}


	bool ImGuiLayer::OnMouseButtonUpEvent(MouseButtonUpEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}


	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();

		return false;
	}


	bool ImGuiLayer::OnKeyDownEvent(KeyDownEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl	= io.KeysDown[GLFW_KEY_LEFT_CONTROL]	|| io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]		|| io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt	= io.KeysDown[GLFW_KEY_LEFT_ALT]		|| io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]		|| io.KeysDown[GLFW_KEY_RIGHT_SUPER];


		return false;
	}


	bool ImGuiLayer::OnKeyUpEvent(KeyUpEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}


	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}


}