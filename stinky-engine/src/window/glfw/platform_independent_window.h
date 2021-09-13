#pragma once

#include "window/window.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct GLFWwindow;

namespace stinky {
    class event;

    class event_controller;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class platform_independent_window : public window {
    public:
        struct WindowData {
            event_controller &eventController;
            std::string title;
            int width, height;

            WindowData(event_controller &eventController, std::string title, int width, int height) : eventController(
                    eventController), title(std::move(title)), width(width), height(height) {
            }
        };

        platform_independent_window(const WindowProperties &properties, event_controller &eventController);

        ~platform_independent_window() override;

        void Init() override;

        void OnUpdate(const event &) override;

        void Shutdown() override;
    private:
        WindowData m_Data;
        GLFWwindow *m_Window;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////