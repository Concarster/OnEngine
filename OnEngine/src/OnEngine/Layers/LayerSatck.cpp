#include "OnPCH.h"
#include "LayerSatck.h"

namespace on
{

    LayerSatck::LayerSatck()
    {
        m_LayerInsert = m_Layers.begin();
    }


    LayerSatck::~LayerSatck()
    {
        for (Layer* layer : m_Layers)
        {
            delete layer;
        }
    }

    void LayerSatck::PushLayer(Layer * layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    }

    void LayerSatck::PushOverlay(Layer * overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerSatck::PopLayer(Layer * layer)
    {
        auto iterate = std::find(m_Layers.begin(), m_Layers.end(), layer);

        if (iterate != m_Layers.end())
        {
            m_Layers.erase(iterate);
            m_LayerInsert--;
        }
    }

    void LayerSatck::PopOverlay(Layer * overlay)
    {
        auto iterate = std::find(m_Layers.begin(), m_Layers.end(), overlay);

        if (iterate != m_Layers.end())
        {
            m_Layers.erase(iterate);
        }
    }

}