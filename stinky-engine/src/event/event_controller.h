//
// Created by christian on 23/08/2020.
//

#pragma once

#include <functional>
#include <unordered_map>

#include "event/application_event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/windows_event.h"
// if glfw defined
#include "event/platform/glfw/glfw_window_event.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace event_handlers {
/////////////////////////////////////////////////////////////////////////////////////////
template <typename EventType> struct event_handler_container {
  using event_handler_fn = std::function<void(const EventType &)>;

  static std::vector<event_handler_fn> container;
};

template <typename _T_event>
std::vector<typename event_handler_container<_T_event>::event_handler_fn>
    event_handler_container<_T_event>::container;
} // namespace event_handlers

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class event_controller {
public:
  event_controller() = default;

  /////////////////////////////////////////////////////////////////////////////////////////
  template <class _T_event>
  void
  register_event_handler(const typename event_handlers::event_handler_container<
                         _T_event>::event_handler_fn &handler) {
    event_handlers::event_handler_container<_T_event>::container.emplace_back(
        handler);
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  template <class _T_event> void on_event(const _T_event &event) {
    std::for_each(
        event_handlers::event_handler_container<_T_event>::container.begin(),
        event_handlers::event_handler_container<_T_event>::container.end(),
        [&](typename event_handlers::event_handler_container<
            _T_event>::event_handler_fn &handlerFunction) -> void {
          handlerFunction(event);
        });
  }
};
} // namespace stinky