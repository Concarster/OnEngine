#include <OnEngine.h>


class App : public on::Application
{
public:
    App()
    {

    }

    ~App()
    {

    }
};

on::Application * on::CreateApplication()
{
    return new App();
}