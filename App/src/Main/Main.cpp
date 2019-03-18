#include <OnEngine/Util/OnINC.h>

class ExampleLayer : public on::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        //ON_CLIENT_INFO("ExampleLayer::Update");

        if (on::IImput::IsKeyPressed(ON_KEY_TAB))
        {
            ON_CLIENT_TRACE("Tab Key is Pressed (poll)!");
        }
    }

    void OnEvent(on::Event& event) override
    {
        //ON_CLIENT_TRACE("{0}", event);

        if (event.GetEventType() == on::EventType::KeyPressed)
        {
            on::KeyPressedEvent& evt = (on::KeyPressedEvent&)event;
            if(evt.GetKeyCode() == ON_KEY_W)
                ON_CLIENT_TRACE("Player are Walking Up (event)!");
            ON_CLIENT_TRACE("{0}", (char)evt.GetKeyCode());
        }
    }
};


class App : public on::Application
{
public:
    App()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new on::ImGuiLayer());
    }

    ~App()
    {

    }
};

on::Application * on::CreateApplication()
{
    return new App();
}