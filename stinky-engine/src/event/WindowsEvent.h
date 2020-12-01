//
// Created by christian on 22/10/2020.
//
#pragma once

#include "event/Event.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
                : EVENT_CONSTRUCTOR(WindowResize), m_Width(width), m_Height(height) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        uint32_t m_Width, m_Height;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() : EVENT_CONSTRUCTOR(WindowClose) {}
    };
}
