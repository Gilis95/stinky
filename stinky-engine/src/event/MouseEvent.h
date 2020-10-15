//
// Created by christian on 23/08/2020.
//

#pragma once

#include <core/MouseCodes.h>
#include "event/Event.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class MouseMovedEvent : public Event {
    public:
        explicit MouseMovedEvent(float x, float y)
                : EVENT_CONSTRUCTOR(MouseMoved), m_MouseX(x), m_MouseY(y) {}

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        float m_MouseX, m_MouseY;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class MouseScrolledEvent : public Event {
    public:
        explicit MouseScrolledEvent(float xOffset, float yOffset)
                : EVENT_CONSTRUCTOR(MouseScrolled), m_XOffset(xOffset), m_YOffset(yOffset) {}

        float m_XOffset, m_YOffset;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class MouseButtonPressedEvent : public Event {
    public:
        explicit MouseButtonPressedEvent(MouseCode button)
                : EVENT_CONSTRUCTOR(MouseButtonPressed), m_Button(button) {}

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        MouseCode m_Button;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class MouseButtonReleasedEvent : public Event {
    public:
        explicit MouseButtonReleasedEvent(MouseCode button)
                : EVENT_CONSTRUCTOR(MouseButtonReleased), m_Button(button) {}

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        MouseCode m_Button;
    };
}
