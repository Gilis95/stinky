//
// Created by christian on 23/08/2020.
//

#pragma once

#include <sstream>

#include "core/mouse_codes.h"
#include "event/event.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class mouse_moved_event : public event {
public:
  explicit mouse_moved_event(float x, float y)
      : EVENT_CONSTRUCTOR(MouseMoved), x(x), y(y) {}

  [[nodiscard]] std::string to_string() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << x << ", " << y;
    return ss.str();
  }

  float x, y;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class mouse_scrolled_event : public event {
public:
  explicit mouse_scrolled_event(float x_offset, float y_offset)
      : EVENT_CONSTRUCTOR(MouseScrolled), x_offset(x_offset),
        y_offset(y_offset) {}

  float x_offset, y_offset;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class mouse_button_pressed_event : public event {
public:
  explicit mouse_button_pressed_event(mouse_code button)
      : EVENT_CONSTRUCTOR(MouseButtonPressed), button(button) {}

  [[nodiscard]] std::string to_string() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << button;
    return ss.str();
  }

  mouse_code button;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class mouse_button_released_event : public event {
public:
  explicit mouse_button_released_event(mouse_code button)
      : EVENT_CONSTRUCTOR(MouseButtonReleased), button(button) {}

  [[nodiscard]] std::string to_string() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << button;
    return ss.str();
  }

  mouse_code button;
};
} // namespace stinky
