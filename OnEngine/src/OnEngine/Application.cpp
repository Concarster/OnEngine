#include "OnPCH.h"
#include "Application.h"

#include <glad\glad.h>

namespace on
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ON_ENGINE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

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

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
            
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event & event)
    {
        EventDispatcher distpacher(event);
        distpacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        ON_ENGINE_TRACE("{0}", event);

        for (auto iterate = m_LayerStack.end(); iterate != m_LayerStack.begin(); )
        {
            (*--iterate)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer * layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer * overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent & event)
    {
        m_Running = false;
        return true;
    }


}