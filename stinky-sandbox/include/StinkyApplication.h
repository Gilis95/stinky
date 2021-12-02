#include <application/application.h>

#include <stinky_prerequisites.h>

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyApplication : public application {
    public:
        StinkyApplication();

        void register_event_handlers() override;

        void init() override;

        window *get_window() override;

    private:
        unique_ptr<track_ball_camera>  m_Camera;
        unique_ptr<graphic_layer_abstraction_factory> m_GLAFactory;
        unique_ptr<window> m_Window;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    application *create_application();
}

