#pragma once
#include "Defs.h"
#include "Events\ApplicationEvent.h"
#include "Events\Event.h"

#include "Window.h"

namespace on
{

    class ON_API Application
    {
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

    private:
        bool OnWindowClosed(WindowCloseEvent& event);
    };
     
    /*To Be defining in the client*/
    Application* CreateApplication();
}