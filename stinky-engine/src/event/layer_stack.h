#pragma once

#include <vector>

#include "event/layer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class layer_stack {
    public:
        layer_stack() = default;

        ~layer_stack();

        void push_layer(layer *layer);

        void push_overlay(layer *overlay);

        void PopLayer(layer *layer);

        void PopOverlay(layer *overlay);

        [[nodiscard]] std::vector<layer *>::iterator begin() { return m_Layers.begin(); }

        [[nodiscard]] std::vector<layer *>::iterator end() { return m_Layers.end(); }

        [[nodiscard]] std::vector<layer *>::reverse_iterator rbegin() { return m_Layers.rbegin(); }

        [[nodiscard]] std::vector<layer *>::reverse_iterator rend() { return m_Layers.rend(); }

        [[nodiscard]] std::vector<layer *>::const_iterator begin() const { return m_Layers.begin(); }

        [[nodiscard]] std::vector<layer *>::const_iterator end() const { return m_Layers.end(); }

        [[nodiscard]] std::vector<layer *>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }

        [[nodiscard]] std::vector<layer *>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}