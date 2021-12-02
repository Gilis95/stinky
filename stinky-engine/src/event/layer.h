#pragma once

#include "stinky_prerequisites.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class layer {
public:
  explicit layer(std::string name = "Layer");

  virtual ~layer() = default;

  virtual void on_attach() {}

  virtual void on_detach() {}

  virtual void on_update(const time_frame &ts) {}

  [[nodiscard]] const std::string &get_name() const { return m_DebugName; }

protected:
  const std::string m_DebugName;
};
} // namespace stinky