#pragma once

#include "stinkypch.h"

namespace stinky {
    struct WindowProperties
    {
    public:
        std::string m_Title;
        int m_Width, m_Height;

        WindowProperties(const std::string& title = "stinky engine", const int width = 1280, const int height = 720) :m_Title(title), m_Width(width), m_Height(height) {}
    };

    class Window
    {
    public:
        enum class API
        {
            none, GLFW
        };

        static Scope<Window> create(const API& api , const WindowProperties& properties = {});

        virtual ~Window() = default;

        virtual void init() = 0;

        virtual void setCloseCallback(const std::function<void()>& callback) = 0;

        virtual void onUpdate() = 0;

        virtual void shutdown() = 0;
    };
}