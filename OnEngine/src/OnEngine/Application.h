#pragma once
#include "Defs.h"
#include "Window.h"
#include "OnEngine\Layers\LayerSatck.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"

namespace on
{

    class ON_API Application
    {
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerSatck m_LayerStack;

    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    private:
        bool OnWindowClosed(WindowCloseEvent& event);
    };
     
    /*To Be defining in the client*/
    Application* CreateApplication();
}