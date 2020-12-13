#include <GLFW/glfw3.h>
#include <Tracy.hpp>

#include "application/Application.h"
#include "event/ApplicationEvent.h"
#include "event/Event.h"
#include "event/Timestep.h"
#include "window/Window.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Application::Application() :
            m_IsRunning(false), m_EventController() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application::~Application() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::RegisterEventHandlers() {
        m_EventController.RegisterEventHandler<WindowCloseEvent>(
                [this](const Event &event) { Close(); }
        );

        m_EventController.RegisterEventHandler<AppUpdateEvent>(
                [window = GetWindow()](const Event &event) { window->OnUpdate(event); }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Init() {
        Log::Init();
        GetWindow()->Init();

        std::string applicationRevision("Revision: 1234");
        std::string applicationName("Application Name: stinky");

        TracyAppInfo(applicationName.c_str(), applicationName.size())
        TracyAppInfo(applicationRevision.c_str(),applicationRevision.size())
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Close() {
        m_IsRunning = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Run() {
        m_IsRunning = true;
        AppUpdateEvent updateEvent;

        while (m_IsRunning) {
            //TODO:: Use platform independent tool
            auto time = (float) glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            std::for_each(
                    m_LayerStack.begin(),
                    m_LayerStack.end(),
                    [&](Layer *layer) -> void {
                        layer->OnUpdate(timestep);
                    });

            m_EventController.OnEvent(updateEvent);
            FrameMark
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }
}
