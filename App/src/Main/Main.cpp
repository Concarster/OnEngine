#include <OnEngine.h>

class ExampleLayer : public on::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        ON_CLIENT_INFO("ExampleLayer::Update");
    }

    void OnEvent(on::Event& event) override
    {
        ON_CLIENT_TRACE("{0}", event);
    }
};


class App : public on::Application
{
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {

    }
};

on::Application * on::CreateApplication()
{
    return new App();
}