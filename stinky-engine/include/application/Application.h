#pragma once

#include "stinkypch.h"

#include "event/Event.h"
#include "event/Layer.h"
#include "event/LayerStack.h"
#include "window/Window.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Application
    {
    private:
        using EventHandlers = std::vector<EventHandler::EventHandlerFn>;
    public:
        Application(Window::API);
        virtual ~Application();

        void Init(Window::API);
        void Close(const Event&);
        void Run();

        //Layers
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        //Events
        void RegisterEvent(EventType);
        void RegisterEventHandler(EventHandler);
        void OnEvent(const Event&);

    private:
        Scope<Window> m_Window;

        LayerStack m_LayerStack;
        std::unordered_map <EventType, EventHandlers> m_EventHandlers;
        float m_LastFrameTime = 0.0f;


        bool m_IsRunning;
    };

    extern Application* CreateApplication();

} //namespace stinky
