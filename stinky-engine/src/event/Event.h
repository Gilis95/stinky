#pragma once

#include <utility>

#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    namespace EventType {
        const int None = 0;
        const int WindowClose = 1;
        const int WindowResize = 2;
        const int WindowFocus = 3;
        const int WindowLostFocus = 4;
        const int WindowMoved = 5;
        const int AppTick = 6;
        const int AppUpdate = 7;
        const int AppRender = 8;
        const int KeyPressed = 9;
        const int KeyReleased = 10;
        const int KeyTyped = 11;
        const int MouseButtonPressed = 12;
        const int MouseButtonReleased = 13;
        const int MouseMoved = 14;
        const int MouseScrolled = 15;

        /** Platform Specific */
        const int GLFWWindowPostInitEvent = 50;
    };


#define EVENT_CONSTRUCTOR(type) Event(EventType::type, #type)


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Event {
    public:
        Event(int eventType, std::string name) : m_EventType(eventType),
                                                 m_Name(std::move(name)) {}

        virtual ~Event() = default;

        [[nodiscard]] virtual std::string ToString() const { return m_Name; }

        int m_EventType;
        std::string m_Name;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.m_Name;
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct EventHandler {
        using EventHandlerFn = std::function<void(const Event &)>;

        int m_EventType;
        const EventHandlerFn& m_EventHandlerFunction;
    };
}

