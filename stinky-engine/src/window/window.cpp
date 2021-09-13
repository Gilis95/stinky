#include "event/event_controller.h"
#include "window/window.h"
#include "window/glfw/platform_independent_window.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    window::window(event_controller &controller) : _M_event_controller(controller) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    unique_ptr<window> window::Create(const window::api &api, event_controller &eventController, const WindowProperties &properties) {
        switch (api) {
            case window::api::GLFW:
                return CreateScope<platform_independent_window>(properties, eventController);
            default: STINKY_LOG_ERROR_AND_BREAK("Wrong window abstraction used");
                return nullptr;
        }
    }
}