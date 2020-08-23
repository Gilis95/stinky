#include "application/Application.h"


#include "stinkypch.h"
#include "event/ApplicationEvent.h"

#include "event/Event.h"
#include "GLFW/glfw3.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Application::Application(Window::API windowApi) :
            m_IsRunning(false), m_EventController() {
        Init(windowApi);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application::~Application() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Init(Window::API windowApi) {
        Log::Init();

        m_Window = Window::Create(windowApi);

        m_Window->SetEventCallback(std::bind(&EventController::OnEvent, &m_EventController,
                                             std::placeholders::_1));

        // KeyPressed, KeyReleased, KeyTyped,
        m_EventController.RegisterEvent(EventType::KeyPressed);
        m_EventController.RegisterEvent(EventType::KeyReleased);
        m_EventController.RegisterEvent(EventType::KeyTyped);

        // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled 
        m_EventController.RegisterEvent(EventType::MouseButtonPressed);
        m_EventController.RegisterEvent(EventType::MouseButtonReleased);
        m_EventController.RegisterEvent(EventType::MouseMoved);
        m_EventController.RegisterEvent(EventType::MouseScrolled);


        // WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        m_EventController.RegisterEvent(EventType::WindowClose);
        m_EventController.RegisterEvent(EventType::WindowResize);
        m_EventController.RegisterEvent(EventType::WindowFocus);
        m_EventController.RegisterEvent(EventType::WindowLostFocus);
        m_EventController.RegisterEvent(EventType::WindowMoved);

        //AppTick, AppUpdate, AppRender,
        m_EventController.RegisterEvent(EventType::AppRender);
        m_EventController.RegisterEvent(EventType::AppTick);
        m_EventController.RegisterEvent(EventType::AppUpdate);

        m_EventController.RegisterEventHandler(
                {
                        EventType::WindowClose, STINKY_BIND(Application::Close)
                }
        );

        m_EventController.RegisterEventHandler(
                {
                        EventType::AppUpdate, std::bind(
                        &Window::OnUpdate,
                        m_Window.get(),
                        std::placeholders::_1)
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Close(const Event &closeEvent) {
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
