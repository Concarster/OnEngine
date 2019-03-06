#pragma once

#ifdef ON_WINDOW

extern on::Application* on::CreateApplication();

void main(int argc, char** argv)
{
    printf("\n  Welcome to OnEngine!\n");

    auto Game = on::CreateApplication();
    Game->Run();
    delete Game;
}

#endif // ON_WINDOW
