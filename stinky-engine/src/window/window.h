#pragma once

#include <utility>

#include "core/stinky_memory.h"
#include "event/event.h"

namespace stinky {
class event_controller;
}

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct WindowProperties {
public:
  std::string m_Title;
  uint32_t m_Width, m_Height;

  WindowProperties(std::string title = "stinky engine", uint32_t width = 1280,
                   uint32_t height = 720)
      : m_Title(std::move(title)), m_Width(width), m_Height(height) {}
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class window {
public:
  enum class api : int { none, GLFW };

  window(event_controller &controller);

  static unique_ptr<window> Create(const api &api,
                                   event_controller &eventController,
                                   const WindowProperties &properties = {});

  virtual ~window() = default;

  virtual void Init() = 0;

  virtual void OnUpdate(const event &) = 0;

  virtual void Shutdown() = 0;

protected:
  event_controller &_M_event_controller;
};
} // namespace stinky