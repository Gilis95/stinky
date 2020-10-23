#pragma once

#include "event/Event.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppTickEvent : public Event {
    public:
        AppTickEvent() : EVENT_CONSTRUCTOR(AppTick) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() : EVENT_CONSTRUCTOR(AppUpdate) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() : EVENT_CONSTRUCTOR(AppRender) {}
    };
}  // namespace stinky