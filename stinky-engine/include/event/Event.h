#pragma once

#include "stinkypch.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };


#define EVENT_OVERRIDE_FUNCTIONS(type) [[nodiscard]] static EventType GetStaticType() { return EventType::type; }\
                               [[nodiscard]] virtual EventType GetEventType() const override { return GetStaticType(); }\
                               [[nodiscard]] virtual const char* GetName() const override { return #type; }


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual std::string ToString() const { return GetName(); }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct EventHandler
    {
        using EventHandlerFn = std::function<void(const Event&)>;

        EventType m_EventType;
        EventHandlerFn m_EventHandlerFunction;
    };
}

