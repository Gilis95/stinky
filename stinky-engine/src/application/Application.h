#pragma once

#include "event/Event.h"
#include "event/EventController.h"
#include "event/LayerStack.h"

#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Application {
    public:
        Application();

        virtual ~Application();

        virtual void RegisterEventHandlers();

        virtual void Init();

        void Close();

        void Run();

        //Layers
        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        virtual Window* GetWindow() = 0;
    protected:
        EventController m_EventController;
    private:
        LayerStack m_LayerStack;

        float m_LastFrameTime = 0.0f;
        bool m_IsRunning;

    };

    extern Application *CreateApplication();

} //namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////