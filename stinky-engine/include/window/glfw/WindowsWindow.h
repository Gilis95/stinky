#pragma once

#include <GLFW/glfw3.h>

#include "window/Window.h"
#include "event/Event.h"

namespace stinky {

    class WindowsWindow : public Window
    {
    public:
        struct WindowData
        {
            std::string titile;
            int width, height;
            EventHandler::EventHandlerFn eventHandlerFn;
        };

        WindowsWindow(const WindowProperties& properties);

        ~WindowsWindow();

        void Init() override;

        void SetEventCallback(EventHandler::EventHandlerFn callback) override;

        void OnUpdate(const Event&) override;

        void Shutdown() override;
    private:
        WindowData m_Data;
        GLFWwindow* m_Window;
    };
}