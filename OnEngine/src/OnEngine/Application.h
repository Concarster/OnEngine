#pragma once
#include "Defs.h"
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
    };
     
    /*To Be defining in the client*/
    Application* CreateApplication();
}