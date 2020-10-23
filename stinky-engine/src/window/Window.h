#pragma once

#include <utility>

#include "stinkypch.h"

#include "event/Event.h"

namespace stinky {
    class EventController;
}

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct WindowProperties {
    public:
        std::string m_Title;
        int m_Width, m_Height;

        WindowProperties(std::string title = "stinky engine",
                         const int width = 1280,
                         const int height = 720)
                : m_Title(std::move(title)), m_Width(width), m_Height(height) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Window {
    public:
        enum class API : int {
            none, GLFW
        };

        Window(EventController &controller);

        static Scope <Window>
        Create(const API &api, EventController &eventController, const WindowProperties &properties = {});

        virtual ~Window() = default;

        virtual void Init();

        virtual void OnUpdate(const Event &) = 0;

        virtual void Shutdown() = 0;
    protected:
        EventController &m_EventController;
    };
}