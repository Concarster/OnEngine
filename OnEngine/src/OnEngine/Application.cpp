#include "OnPCH.h"
#include "Application.h"

#include <GLFW\glfw3.h>

namespace on
{

    Application::Application()
    {
        /*Cause is an explicit Constructor*/
        m_Window = std::unique_ptr<Window>(Window::Create());
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


}