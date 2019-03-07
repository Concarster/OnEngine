#pragma once
#include <memory>
#include "Defs.h"
#include <spdlog\spdlog.h>

namespace on
{

    class ON_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

/*Engine System Logger*/
#define ON_ENGINE_TRACE(...)       ::on::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ON_ENGINE_INFO(...)        ::on::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ON_ENGINE_WARN(...)        ::on::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ON_ENGINE_ERROR(...)       ::on::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ON_ENGINE_CRITICAL(...)    ::on::Log::GetEngineLogger()->critical(__VA_ARGS__)

/*Client System Logger*/
#define ON_CLIENT_TRACE(...)       ::on::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ON_CLIENT_INFO(...)        ::on::Log::GetClientLogger()->info(__VA_ARGS__)
#define ON_CLIENT_WARN(...)        ::on::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ON_CLIENT_ERROR(...)       ::on::Log::GetClientLogger()->error(__VA_ARGS__)
#define ON_CLIENT_CRITICAL(...)    ::on::Log::GetClientLogger()->critical(__VA_ARGS__)