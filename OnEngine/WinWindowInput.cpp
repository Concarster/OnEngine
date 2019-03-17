#include "OnPCH.h"
#include "WinWindowInput.h"

#include "OnEngine/Application.h"
#include <GLFW/glfw3.h>

namespace on
{
    on::IImput* on::IImput::s_Instance = new WinWindowInput();

    bool WinWindowInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WinWindowInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WinWindowInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float WinWindowInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();

        return x;
    }

    float WinWindowInput::GetMouseYImpl()
    {
        auto[x, y] = GetMousePositionImpl();

        return y;
    }

}