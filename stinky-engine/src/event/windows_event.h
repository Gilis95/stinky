//
// Created by christian on 22/10/2020.
//
#pragma once

#include "event/event.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class window_resize_event : public event {
    public:
        window_resize_event(unsigned int width, unsigned int height)
                : EVENT_CONSTRUCTOR(WindowResize), width(width), height(height) {
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width << ", " << height;
            return ss.str();
        }

        uint32_t width, height;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class window_close_event : public event {
    public:
        window_close_event() : EVENT_CONSTRUCTOR(WindowClose) {}
    };
}
