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


#ifdef ON_DEBUG
#define ON_ENABLE_ASSERTS
#endif

#ifdef ON_ENABLE_ASSERTS
#define ON_CLIENT_ASSERT(x, ...) { if(!(x)) { ON_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ON_ENGINE_ASSERT(x, ...) { if(!(x)) { ON_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ON_ASSERT(x, ...)
#define ON_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ON_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

