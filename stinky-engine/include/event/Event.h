#pragma once

#include <utility>

#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };


#define EVENT_CONSTRUCTOR(type) Event(EventType::type, #type)


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Event {
    public:
        Event(EventType eventType, std::string name) : m_EventType(eventType),
                                                       m_Name(std::move(name)) {}

        virtual ~Event() = default;

        [[nodiscard]] virtual std::string ToString() const { return m_Name; }

        EventType m_EventType;
        std::string m_Name;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.m_Name;
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct EventHandler {
        using EventHandlerFn = std::function<void(const Event &)>;

        EventType m_EventType;
        EventHandlerFn m_EventHandlerFunction;
    };
}

