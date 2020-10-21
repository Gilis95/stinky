#pragma once

#include "stinkypch.h"

#include "event/Event.h"
#include "event/EventController.h"
#include "event/Layer.h"
#include "event/LayerStack.h"
#include "window/Window.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Application {
    public:
        Application(Window::API api);

        virtual ~Application();

        void Init(Window::API);

        void Close();

        void Run();

        //Layers
        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

    protected:
        EventController m_EventController;
    private:
        Scope<Window> m_Window;
        LayerStack m_LayerStack;

        float m_LastFrameTime = 0.0f;
        bool m_IsRunning;
    };

    extern Application *CreateApplication();

} //namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////