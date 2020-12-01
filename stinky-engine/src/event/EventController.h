//
// Created by christian on 23/08/2020.
//

#pragma once

#include <unordered_map>
#include <functional>

#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowsEvent.h"
//if glfw defined
#include "event/platform/glfw/GLFWWindowEvent.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_EVENT_HANDLER(EventType) \
    template<>\
    void EventController::RegisterEventHandler<EventType>(const EventHandlerFn<EventType> &handler);\
    template<>\
    void EventController::OnEvent<EventType> (const EventType & event);

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_EVENT_HANDLER_STORAGE(EventType)\
    EventHandlers<EventType> m_EventHandler##EventType;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_EVENT_HANDLER(EventType) \
    template<>\
    void EventController::RegisterEventHandler<EventType>(const EventHandlerFn<EventType> &handler) { \
         m_EventHandler##EventType.emplace_back(handler);\
    }\
\
    template<>\
    void EventController::OnEvent<EventType> (const EventType & event){\
        std::for_each(\
                m_EventHandler##EventType.begin(),\
                m_EventHandler##EventType.end(),\
                [&](EventHandlerFn<EventType> &handlerFunction) -> void {\
                    handlerFunction(event);\
                });\
    }\

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class EventController {
     private:
        template<class EventType>
        using EventHandlerFn = std::function<void(const EventType &)>;

        template<class EventType>
        using EventHandlers = std::vector<EventHandlerFn<EventType>>;
    public:
        EventController() = default;

        template<class EventType>
        void RegisterEventHandler(const EventHandlerFn<EventType> &handler) {}

        template<class EventType>
        void OnEvent(const EventType &) {}

    private:
        DECLARE_EVENT_HANDLER_STORAGE(AppRenderEvent)
        DECLARE_EVENT_HANDLER_STORAGE(AppTickEvent)
        DECLARE_EVENT_HANDLER_STORAGE(AppUpdateEvent)
        DECLARE_EVENT_HANDLER_STORAGE(KeyPressedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(KeyReleasedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(KeyTypedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(MouseButtonPressedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(MouseButtonReleasedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(MouseMovedEvent)
        DECLARE_EVENT_HANDLER_STORAGE(MouseScrolledEvent)
        DECLARE_EVENT_HANDLER_STORAGE(WindowResizeEvent)
        DECLARE_EVENT_HANDLER_STORAGE(WindowCloseEvent)
        DECLARE_EVENT_HANDLER_STORAGE(GLFWWindowPostInitEvent)
    };

    DECLARE_EVENT_HANDLER(AppRenderEvent)
    DECLARE_EVENT_HANDLER(AppTickEvent)
    DECLARE_EVENT_HANDLER(AppUpdateEvent)
    DECLARE_EVENT_HANDLER(KeyPressedEvent)
    DECLARE_EVENT_HANDLER(KeyReleasedEvent)
    DECLARE_EVENT_HANDLER(KeyTypedEvent)
    DECLARE_EVENT_HANDLER(MouseButtonPressedEvent)
    DECLARE_EVENT_HANDLER(MouseButtonReleasedEvent)
    DECLARE_EVENT_HANDLER(MouseMovedEvent)
    DECLARE_EVENT_HANDLER(MouseScrolledEvent)
    DECLARE_EVENT_HANDLER(WindowResizeEvent)
    DECLARE_EVENT_HANDLER(WindowCloseEvent)
    DECLARE_EVENT_HANDLER(GLFWWindowPostInitEvent)
}