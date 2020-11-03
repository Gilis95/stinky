#include "application/Application.h"


#include "stinkypch.h"
#include "event/ApplicationEvent.h"

#include "event/Event.h"
#include "GLFW/glfw3.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Application::Application(Window::API windowApi) :
            m_IsRunning(false), m_EventController(), m_Window(Window::Create(windowApi, m_EventController)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application::~Application() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::RegisterEvents(){
        m_Window->RegisterEvents();
        //AppTick, AppUpdate, AppRender,
        m_EventController.RegisterEvent(EventType::AppRender);
        m_EventController.RegisterEvent(EventType::AppTick);
        m_EventController.RegisterEvent(EventType::AppUpdate);

        m_EventController.RegisterEventHandler(
                {
                        EventType::WindowClose, [this](const Event &event) { Close(); }
                }
        );

        m_EventController.RegisterEventHandler(
                {
                        EventType::AppUpdate, [window = m_Window.get()](const Event &event) { window->OnUpdate(event); }
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Init() {
        Log::Init();
        m_Window->Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Close() {
        m_IsRunning = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Run() {
        m_IsRunning = true;

        while (m_IsRunning) {
            //TODO:: Use platform independent tool
            float time = (float) glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            std::for_each(
                    m_LayerStack.begin(),
                    m_LayerStack.end(),
                    [&](Layer *layer) -> void {
                        layer->OnUpdate(timestep);
                    });

            m_EventController.OnEvent(AppUpdateEvent());
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
