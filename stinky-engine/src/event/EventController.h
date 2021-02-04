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
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    namespace EventHandlers {
        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename EventType>
        struct EventHandlerContainer {
            using EventHandlerFn = std::function<void(const EventType &)>;

            static std::vector<EventHandlerFn> container;
        };

        template<typename EventType> std::vector<typename EventHandlerContainer<EventType>::EventHandlerFn>
                EventHandlerContainer<EventType>::container;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class EventController {
    public:
        EventController() = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        template<class EventType>
        void RegisterEventHandler(const typename EventHandlers::EventHandlerContainer<EventType>::EventHandlerFn &handler) {
            EventHandlers::EventHandlerContainer<EventType>::container.emplace_back(handler);
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<class EventType>
        void OnEvent(const EventType &event) {
            std::for_each(
                    EventHandlers::EventHandlerContainer<EventType>::container.begin(),
                    EventHandlers::EventHandlerContainer<EventType>::container.end(),
                    [&](typename EventHandlers::EventHandlerContainer<EventType>::EventHandlerFn &handlerFunction) -> void {
                        handlerFunction(event);
                    });
        }
    };
}