#include "event/EventController.h"

namespace stinky{
    DEFINE_EVENT_HANDLER(AppRenderEvent)
    DEFINE_EVENT_HANDLER(AppTickEvent)
    DEFINE_EVENT_HANDLER(AppUpdateEvent)
    DEFINE_EVENT_HANDLER(KeyPressedEvent)
    DEFINE_EVENT_HANDLER(KeyReleasedEvent)
    DEFINE_EVENT_HANDLER(KeyTypedEvent)
    DEFINE_EVENT_HANDLER(MouseButtonPressedEvent)
    DEFINE_EVENT_HANDLER(MouseButtonReleasedEvent)
    DEFINE_EVENT_HANDLER(MouseMovedEvent)
    DEFINE_EVENT_HANDLER(MouseScrolledEvent)
    DEFINE_EVENT_HANDLER(WindowResizeEvent)
    DEFINE_EVENT_HANDLER(WindowCloseEvent)
    DEFINE_EVENT_HANDLER(GLFWWindowPostInitEvent)
}