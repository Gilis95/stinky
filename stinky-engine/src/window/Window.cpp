#include "event/EventController.h"
#include "window/Window.h"
#include "window/glfw/PlatformIndependentWindow.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Window::Window(EventController &controller) : m_EventController(controller) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Scope<Window> Window::Create(const API &api, EventController &eventController, const WindowProperties &properties) {
        switch (api) {
            case API::GLFW:
                return CreateScope<PlatformIndependentWindow>(properties, eventController);
            default: STINKY_LOG_ERROR_AND_BREAK("Wrong window abstraction used");
                return nullptr;
        }
    }
}