#pragma once

#include <GLFW/glfw3.h>
#include "window/Window.h"

namespace stinky {

    class WindowsWindow : public Window
    {
    public:
        struct WindowData
        {
            std::string titile;
            int width, height;
            std::function<void()> closeCallback;
        };

        WindowsWindow(const WindowProperties& properties);

        ~WindowsWindow();

        void init() override;

        void setCloseCallback(const std::function<void()>& callback) override;

        void onUpdate() override;

        void shutdown() override;
    private:
        WindowData m_Data;
        GLFWwindow* m_Window;
    };
}