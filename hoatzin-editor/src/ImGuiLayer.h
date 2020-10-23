#pragma once

struct GLFWwindow;

namespace stinky {
    class Event;
}

namespace stinky::hoatzin {
    /////////////////////////////////////////////////////////////////////////////////////////
    namespace ImGuiLayer {
        void HandleGLFWInit(const Event &event);
        void Initialize(GLFWwindow *window);
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
