#include "StinkyApplication.h"
#include "StinkyLayer.h"
#include "application/EntryPoint.h"

#include <filesystem>

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyApplication::StinkyApplication() : Application(Window::API::GLFW) {
        PushLayer(new StinkyLayer(Application::m_EventController));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new StinkyApplication();
    }

}
