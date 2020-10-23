//
// Created by christian on 21/10/2020.
//

#include "application/EntryPoint.h"

#include "HoatzinApplication.h"
#include "HoatzinEditorLayer.h"
#include "ImGuiLayer.h"

namespace stinky {
    namespace hoatzin {
        /////////////////////////////////////////////////////////////////////////////////////////
        HoatzinApplication::HoatzinApplication() : Application(Window::API::GLFW) {
            PushLayer(new HoatzinEditorLayer(Application::m_EventController));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new hoatzin::HoatzinApplication();
    }

}