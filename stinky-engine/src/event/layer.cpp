#include "stinkypch.h"

#include "event/layer.h"

#include <utility>

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
layer::layer(std::string debugName) : m_DebugName(std::move(debugName)) {}

} // namespace stinky