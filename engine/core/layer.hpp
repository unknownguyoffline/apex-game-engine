#pragma once

#include <memory>
#include <vector>
class Layer
{
  public:
    virtual void onAttach()
    {
    }
    virtual void onDetach()
    {
    }
    virtual void onUpdate()
    {
    }
    void enable()
    {
        m_isEnabled = true;
    }
    void disable()
    {
        m_isEnabled = false;
    }
    bool isEnabled()
    {
        return m_isEnabled;
    }

  private:
    bool m_isEnabled = true;
};

class LayerStack
{
  public:
    void addLayer(Layer *layer)
    {
        m_layers.push_back(layer);
        layer->onAttach();
    }
    void updateEnabledLayer()
    {
        for (Layer *layer : m_layers)
        {
            if (layer->isEnabled())
                layer->onUpdate();
        }
    }
    void removeLayer(Layer *layer)
    {
        for (int i = 0; i < m_layers.size(); i++)
        {
            if (m_layers[i] == layer)
            {
                m_layers[i]->onDetach();
                m_layers.erase(m_layers.begin() + i);
            }
        }
    }
    ~LayerStack()
    {
        m_layers.clear();
    }

  private:
    std::vector<Layer *> m_layers;
};