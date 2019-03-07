#pragma once

#ifdef ON_WINDOW

extern on::Application* on::CreateApplication();

void main(int argc, char** argv)
{
    on::Log::Init();
    ON_ENGINE_INFO("Welcome to OnEngine!");

    double versionNum = 1.0;
    ON_ENGINE_INFO("Version:{}.0", versionNum);

    ON_ENGINE_WARN("Initializing Logger System!");

    ON_ENGINE_INFO("Logger System Initialized!");

    ON_CLIENT_INFO("Logger System Initialized!");

    auto Game = on::CreateApplication();
    Game->Run();
    delete Game;
}

#endif // ON_WINDOW
