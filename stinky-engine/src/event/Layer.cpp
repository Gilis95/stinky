#include "stinkypch.h"

#include "event/Layer.h"

#include <utility>

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Layer::Layer(std::string debugName)
            : m_DebugName(std::move(debugName)) {
    }

}