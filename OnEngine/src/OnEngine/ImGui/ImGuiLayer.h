#pragma once
#include "OnEngine\Layers\Layer.h"

#include "OnEngine\Events\ApplicationEvent.h"
#include "OnEngine\Events\KeyEvent.h"
#include "OnEngine\Events\MouseEvent.h"

namespace on
{

    class ON_API ImGuiLayer : public Layer
    {
    private:
        float m_Time = 0.0f;

    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);

        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);

        bool OnMouseMovedEvent(MouseMovedEvent& event);

        bool OnMouseScrolledEvent(MouseScrolledEvent& event);

        bool OnKeyPressedEvent(KeyPressedEvent& event);

        bool OnKeyReleasedEvent(KeyReleasedEvent& event);

        bool OnKeyTypedEvent(KeyTypedEvent& event);

        bool OnWindowResizeEvent(WindowResizeEvent& event);
       
    };

}