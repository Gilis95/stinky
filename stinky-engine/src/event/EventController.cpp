#include "event/EventController.h"

namespace stinky{
    REGISTER_EVENT_HANDLER(AppRenderEvent)
    REGISTER_EVENT_HANDLER(AppTickEvent)
    REGISTER_EVENT_HANDLER(AppUpdateEvent)
    REGISTER_EVENT_HANDLER(KeyPressedEvent)
    REGISTER_EVENT_HANDLER(KeyReleasedEvent)
    REGISTER_EVENT_HANDLER(KeyTypedEvent)
    REGISTER_EVENT_HANDLER(MouseButtonPressedEvent)
    REGISTER_EVENT_HANDLER(MouseButtonReleasedEvent)
    REGISTER_EVENT_HANDLER(MouseMovedEvent)
    REGISTER_EVENT_HANDLER(MouseScrolledEvent)
    REGISTER_EVENT_HANDLER(WindowResizeEvent)
    REGISTER_EVENT_HANDLER(WindowCloseEvent)
    REGISTER_EVENT_HANDLER(GLFWWindowPostInitEvent)
}