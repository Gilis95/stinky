#pragma once

#include "stinkypch.h"

#include "event/Event.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct WindowProperties {
    public:
        std::string m_Title;
        int m_Width, m_Height;

        WindowProperties(const std::string &title = "stinky engine", const int width = 1280,
                         const int height = 720)
                : m_Title(title), m_Width(width), m_Height(height) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Window {
    public:
        enum class API : int {
            none, GLFW
        };

        static Scope<Window> Create(const API &api, const WindowProperties &properties = {});

        virtual ~Window() = default;

        virtual void Init() = 0;

        virtual void SetEventCallback(EventHandler::EventHandlerFn callback) = 0;

        virtual void OnUpdate(const Event &) = 0;

        virtual void Shutdown() = 0;
    };
}