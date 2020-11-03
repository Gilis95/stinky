#include "window/Window.h"
#include "window/glfw/PlatformIndependentWindow.h"

#include "event/EventController.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Window::Window(EventController &controller) : m_EventController(controller) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Scope<Window> Window::Create(const API &api, EventController &eventController, const WindowProperties &properties) {
        switch (api) {
            case API::GLFW:
                return CreateScope<PlatformIndependentWindow>(properties, eventController);
            default: STINKY_LOG_ERROR_AND_BREAK("Wrong window abstraction used");
                return nullptr;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Window::RegisterEvents() {
        // KeyPressed, KeyReleased, KeyTyped,
        m_EventController.RegisterEvent(EventType::KeyPressed);
        m_EventController.RegisterEvent(EventType::KeyReleased);
        m_EventController.RegisterEvent(EventType::KeyTyped);

        // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
        m_EventController.RegisterEvent(EventType::MouseButtonPressed);
        m_EventController.RegisterEvent(EventType::MouseButtonReleased);
        m_EventController.RegisterEvent(EventType::MouseMoved);
        m_EventController.RegisterEvent(EventType::MouseScrolled);


        // WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        m_EventController.RegisterEvent(EventType::WindowClose);
        m_EventController.RegisterEvent(EventType::WindowResize);
        m_EventController.RegisterEvent(EventType::WindowFocus);
        m_EventController.RegisterEvent(EventType::WindowLostFocus);
        m_EventController.RegisterEvent(EventType::WindowMoved);
    }


}