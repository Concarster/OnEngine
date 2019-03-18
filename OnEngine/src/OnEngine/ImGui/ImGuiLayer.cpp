#include "OnPCH.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "OnEngine\Platform\OpenGL\ImGuiGLRenderer.h"


//We REMOVE this
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OnEngine\Application.h"

namespace on
{

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }


    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        /* Setup ImGui Context Creation */
        ImGui::CreateContext();

        /* Setting BgColor */
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        ImGui::StyleColorsClassic ();

        /* Setup back-end capabilities flags */
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        //io.BackendPlatformName = "imgui_impl_glfw";

        //Temporary
        /* Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array. */
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        /*Initiliaze ImGuiGL*/
        ImGui_ImplOpenGL3_Init("#version 420");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::GetInstance();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event & event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseButtonPressedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));

        dispatcher.Dispatch<MouseButtonReleasedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));

        dispatcher.Dispatch<MouseMovedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));

        dispatcher.Dispatch<MouseScrolledEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

        dispatcher.Dispatch<KeyPressedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));

        dispatcher.Dispatch<KeyReleasedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));

        dispatcher.Dispatch<KeyTypedEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

        dispatcher.Dispatch<WindowResizeEvent>(ON_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MousePos = ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseWheelH += event.GetXOffset();
        io.MouseWheel += event.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.KeysDown[event.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];

        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];

        /*KeySuper is the WindowsKey*/
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];


        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.KeysDown[event.GetKeyCode()] = true;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        int keyCode = event.GetKeyCode();

        if (keyCode > 0 && keyCode < 0x10000)
            io.AddInputCharacter((unsigned short)keyCode);

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent & event)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());

        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        glViewport(0, 0, event.GetWidth(), event.GetHeight());

        return false;
    }

}