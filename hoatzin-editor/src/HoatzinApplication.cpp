//
// Created by christian on 21/10/2020.
//

#include "application/EntryPoint.h"
#include "event/Event.h"
#include "event/EventController.h"

#include "HoatzinApplication.h"
#include "HoatzinEditorLayer.h"
#include "ImGuiLayer.h"

namespace stinky {
    namespace hoatzin {
        /////////////////////////////////////////////////////////////////////////////////////////
        HoatzinApplication::HoatzinApplication() : Application(Window::API::GLFW) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::RegisterEvents() {
            Application::RegisterEvents();
            m_EventController.RegisterEventHandler({
                                                           EventType::GLFWWindowPostInitEvent,
                                                           [](const Event &event) {
                                                               ImGuiLayer::HandleGLFWInit(event);
                                                           }
                                                   });
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::Init() {
            Application::Init();
            PushLayer(new HoatzinEditorLayer(Application::m_EventController));
        }


    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new hoatzin::HoatzinApplication();
    }

}