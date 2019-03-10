#pragma once
#include "OnEngine/Window.h"

#include <GLFW\glfw3.h>

namespace on
{

    class WinWindow : public Window
    {
    public:
        WinWindow(const WindowProps& props);
        virtual ~WinWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }

        inline unsigned int GetHeight() const override { return m_Data.Height; }

        /*Window Settings*/
        inline void SetEventCallBack(const EventCallBackFn& callBack) override { m_Data.EventCallBack = callBack; }

        void SetVSync(bool enable) override;

        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void ShutDown();

        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallBack;
        };

        WindowData m_Data;
    };

}