#pragma once

#include "window/Window.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct GLFWwindow;

namespace stinky {
    class Event;

    class EventController;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class PlatformIndependentWindow : public Window {
    public:
        struct WindowData {
            EventController &eventController;
            std::string title;
            int width, height;

            WindowData(EventController &eventController, std::string title, int width, int height) : eventController(
                    eventController), title(std::move(title)), width(width), height(height) {
            }
        };

        PlatformIndependentWindow(const WindowProperties &properties, EventController &eventController);

        ~PlatformIndependentWindow() override;

        void RegisterEvents() override;

        void Init() override;

        void OnUpdate(const Event &) override;

        void Shutdown() override;
    private:
        WindowData m_Data;
        GLFWwindow *m_Window;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////