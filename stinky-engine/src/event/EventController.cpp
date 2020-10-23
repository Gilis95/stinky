//
// Created by christian on 23/08/2020.
//
#include "event/EventController.h"

#include <unordered_map>

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    EventController::EventController() : m_EventHandlers() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void EventController::RegisterEvent(int type) {
        m_EventHandlers[type];
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void EventController::RegisterEventHandler(const EventHandler &handler) {
        m_EventHandlers[handler.m_EventType].push_back(handler.m_EventHandlerFunction);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void EventController::OnEvent(const Event &event) {
        auto handlers = m_EventHandlers.find(event.m_EventType);

        if (handlers != m_EventHandlers.end()) {
            std::for_each(
                    handlers->second.begin(),
                    handlers->second.end(),
                    [&](EventHandler::EventHandlerFn &handlerFunction) -> void {
                        handlerFunction(event);
                    });
        }
    }
}