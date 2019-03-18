#pragma once
#include "OnEngine/Util/Defs.h"
#include "Layer.h"

#include <vector>

namespace on
{

    class ON_API LayerSatck
    {
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_LayerInsert;

    public:
        LayerSatck();
        ~LayerSatck();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() {  return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    };


}