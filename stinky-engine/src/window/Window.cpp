#include "window/Window.h"
#include "window/glfw/WindowsWindow.h"

namespace stinky {
    Scope<Window> Window::Create(const API& api, const WindowProperties& properties)
    {
        switch (api)
        {
        case API::GLFW:
            return createScope<WindowsWindow>(properties);
        default:
            ASSERT(false, "Wrong window abstraction used");
            return nullptr;
        }


    }
}