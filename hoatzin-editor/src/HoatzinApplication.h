//
// Created by christian on 21/10/2020.
//
#pragma once

#include <application/application.h>
#include <scene/scene.h>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class window;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    namespace hoatzin{
        class HoatzinApplication : public application {
        public:
            HoatzinApplication();

            void register_event_handlers() override;

            void init() override;

            window* get_window() override;
        private:
            unique_ptr<fps_camera> m_Camera;
            unique_ptr<graphic_layer_abstraction_factory> m_GLAFactory;
            unique_ptr<window> m_Window;
        };

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    application *create_application();
}