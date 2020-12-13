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

        /**
         * This is the first function called after class creation.
         * It's used for registering user application event handlers to event controller here.
         *
         * NOTE: Base class should be called, if user extend this function.
         */
        virtual void RegisterEventHandlers();

       /**
        * This is second function called after class creation.
        * It's used for initializing debugger, logger and window.
        *
        * NOTE: Base class should be called, if user extend this function.
        */
        virtual void Init();

        void Close();

        /**
         * Main game loop.
         */
        void Run();

        //Layers
        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        virtual Window *GetWindow() = 0;

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