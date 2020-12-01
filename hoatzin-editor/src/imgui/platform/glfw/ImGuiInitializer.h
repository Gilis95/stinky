#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
struct GLFWwindow;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Event;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky::hoatzin::ImGuiInitializer {
    void HandleGLFWInit(const Event &event);
    void Execute(GLFWwindow *window);
}
