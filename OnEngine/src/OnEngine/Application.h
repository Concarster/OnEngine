#pragma once
#include "Defs.h"

namespace on
{

    class ON_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };
     
    /*To Be defining in the client*/
    Application* CreateApplication();
}