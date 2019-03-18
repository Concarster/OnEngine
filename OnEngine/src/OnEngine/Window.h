#pragma once
#include "OnPCH.h"
#include "OnEngine/Util/Defs.h"

#include "OnEngine\Events\Event.h"

namespace on
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "OnEngine", unsigned int width = 1280, unsigned int height = 768)
            :Title(title),
            Width(width),
            Height(height)
        {

        }
    };

    /*Interface Desktop System based Window than will be implementin by Platform*/
    class ON_API Window
    {
    public:
        using EventCallBackFn = std::function<void(Event&)>;
        
        //Window();
        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;

        virtual unsigned int GetHeight() const = 0;

        /*Window Settings*/
        virtual void SetEventCallBack(const EventCallBackFn& callBack) = 0;
        
        virtual void SetVSync(bool enable) = 0;

        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());

    };

}