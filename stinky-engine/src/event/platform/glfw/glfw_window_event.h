//
// Created by christian on 23/10/2020.
//

#pragma once

#include <GLFW/glfw3.h>
#include <sstream>

#include "event/event.h"

namespace stinky {
    class glfw_window_post_init_event : public event {
    public:
        explicit glfw_window_post_init_event(GLFWwindow *window)
                : EVENT_CONSTRUCTOR(glfw_window_post_init_event), window(window) {
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "WindowPostInitEvent" << window;
            return ss.str();
        }

    public:
        GLFWwindow *window;
    };
}