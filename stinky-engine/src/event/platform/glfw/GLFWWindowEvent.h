//
// Created by christian on 23/10/2020.
//

#pragma once

#include <GLFW/glfw3.h>
#include <sstream>

#include "event/Event.h"

namespace stinky {
    class GLFWWindowPostInitEvent : public Event {
    public:
        explicit GLFWWindowPostInitEvent(GLFWwindow *window)
                : EVENT_CONSTRUCTOR(GLFWWindowPostInitEvent), m_Window(window) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowPostInitEvent" << m_Window;
            return ss.str();
        }

    public:
        GLFWwindow *m_Window;
    };
}