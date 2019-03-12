#include "OnPCH.h"
#include "Application.h"

#include <GLFW\glfw3.h>

namespace on
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        /*Cause is an explicit Constructor*/
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }


    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor( 0.5F, 0.8F, 1.0F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event & event)
    {
        EventDispatcher distpacher(event);
        distpacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        ON_ENGINE_TRACE("{0}", event);
    }

    bool Application::OnWindowClosed(WindowCloseEvent & event)
    {
        m_Running = false;
        return true;
    }


}