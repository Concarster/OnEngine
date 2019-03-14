#pragma once
#include "OnEngine\Layers\Layer.h"

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
       
    };

}