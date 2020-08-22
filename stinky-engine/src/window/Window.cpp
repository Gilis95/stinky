#include "window/Window.h"
#include "window/glfw/PlatformIndependentWindow.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Scope<Window> Window::Create(const API &api, const WindowProperties &properties) {
        switch (api) {
            case API::GLFW:
                return createScope<PlatformIndependentWindow>(properties);
            default: STINKY_LOG_ERROR_AND_BREAK("Wrong window abstraction used");
                return nullptr;
        }


    }
}