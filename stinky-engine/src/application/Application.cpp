#include <Tracy.hpp>
#include <core/Time.h>

#include "application/Application.h"
#include "event/ApplicationEvent.h"
#include "event/Event.h"
#include "window/Window.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Application::Application(TimeFrame &&minTimestep) :
            m_IsRunning(false), m_EventController(), m_MinTimestep(std::forward<TimeFrame>(minTimestep)) {
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
        TracyAppInfo(applicationRevision.c_str(), applicationRevision.size())
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Close() {
        m_IsRunning = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Run() {
        m_IsRunning = true;
        AppUpdateEvent updateEvent;

        TimeFrame begin;
        TimeFrame timestep;
        TimeFrame leftFrameTime;
        while (m_IsRunning) {
            begin.AssignCurrentTime();

            std::for_each(
                    m_LayerStack.begin(),
                    m_LayerStack.end(),
                    [&](Layer *layer) -> void {
                        layer->OnUpdate(std::max(m_MinTimestep, timestep));
                    });

            m_EventController.OnEvent(updateEvent);
            {
                ZoneScopedN("LimitFrameRate")

                bool first = true;

                do {
                    // Capture the end of frame
                    timestep.AssignCurrentTime();
                    // Subtract frame start from it. This will be the time, that frame has taken until now.
                    timestep -= begin;
                    ContinueUnless(first)
                    // Subtract timestep from min timestep. If this value is greater than 0, we should wait this amount
                    // of time before next frame.
                    leftFrameTime = m_MinTimestep;
                    leftFrameTime -= timestep;
                    first = false;
                } while (stinky::this_thread::sleep(leftFrameTime, leftFrameTime));
            }
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
