#pragma once

#include <chrono>
#include "core/Time.h"
#include "event/Event.h"
#include "event/EventController.h"
#include "event/LayerStack.h"

#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Application {
    public:
        /**
         * @param minTimestep - minimum allowed amount of time between frames
         */
        Application(TimeFrame&& minTimestep);

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
         * NOTE: When this function is being extended, it either should be called by extender, or its logic should be
         * copied.
         */
        virtual void Init();

        void Close();

        /**
         * Main game loop.
         */
        void Run();

        /**
         * Application main loop, loops through layers queue and calls OnUpdate function of each queue element.
         * This function adds to the end of this queue, provided layer.
         *
         * @param layer - layer to be pushed at the end of layers queue
         */
        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        /**
         * User must choose platform specific window implementation. This function is used by application class for
         * initialization purposes.
         */
        virtual Window *GetWindow() = 0;

    protected:
        EventController m_EventController;
    private:
        LayerStack m_LayerStack;

        bool m_IsRunning;
        const TimeFrame m_MinTimestep;
    };

    extern Application *CreateApplication();

} //namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////