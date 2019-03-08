#pragma once

#ifdef ON_ENGINE
#ifdef ON_WINDOW
#ifdef ON_BUILD_DLL

    #define ON_API __declspec(dllexport)
    #else
    #define ON_API __declspec(dllimport)

#endif // ON_BUILD_DLL

#else
#error OnEngine only support Windows!

#endif // ON_WINDOW
#endif // ON_ENGINE

#define BIT(x) (1 << x)

