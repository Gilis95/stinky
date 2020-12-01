#pragma once

#include <utility>

#include "core/StinkyMemory.h"
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
        uint32_t m_Width, m_Height;

        WindowProperties(std::string title = "stinky engine",
                         uint32_t width = 1280,
                         uint32_t height = 720)
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

        static Scope<Window>
        Create(const API &api, EventController &eventController, const WindowProperties &properties = {});

        virtual ~Window() = default;

        virtual void Init() = 0;

        virtual void OnUpdate(const Event &) = 0;

        virtual void Shutdown() = 0;
    protected:
        EventController &m_EventController;
    };
}