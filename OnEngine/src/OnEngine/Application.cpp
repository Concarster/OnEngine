#include "Application.h"
#include <OnEngine\Log.h>
#include <OnEngine\Events\ApplicationEvent.h>

namespace on
{

    Application::Application()
    {
    }


    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent event(1440, 900);

        if (event.IsInCategory(EventCategoryApplication))
        {
            ON_CLIENT_TRACE(event);
            while (true);
        }
        else if (event.IsInCategory(EventCategoryInput))
        {
            ON_CLIENT_TRACE("I'm Just in EventCategoryInput");
        }
        else
        {
            ON_CLIENT_TRACE("I'm not in EventCategoryApplication");
        }
        
        //while (true);
    }


}