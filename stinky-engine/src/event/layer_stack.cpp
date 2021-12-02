
#include "event/layer_stack.h"
#include "event/layer.h"

class value;
namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
layer_stack::~layer_stack() {
  for (layer *layer : m_Layers) {
    layer->on_detach();
    delete layer;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void layer_stack::push_layer(layer *layer) {
  m_Layers.push_back(layer);
  ++m_LayerInsertIndex;
  layer->on_attach();
}

/////////////////////////////////////////////////////////////////////////////////////////
void layer_stack::push_overlay(layer *overlay) {
  m_Layers.push_back(overlay);
  overlay->on_attach();
}

/////////////////////////////////////////////////////////////////////////////////////////
void layer_stack::PopLayer(layer *layer) {
  auto it =
      std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
  if (it != m_Layers.begin() + m_LayerInsertIndex) {
    layer->on_detach();
    m_Layers.erase(it);
    --m_LayerInsertIndex;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void layer_stack::PopOverlay(layer *overlay) {
  auto it =
      std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
  if (it != m_Layers.end()) {
    overlay->on_detach();
    m_Layers.erase(it);
  }
}

} // namespace stinky
