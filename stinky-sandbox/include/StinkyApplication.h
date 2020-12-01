#include "application/Application.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyApplication : public Application {
    public:
        StinkyApplication();

        void RegisterEventHandlers() override;

        void Init() override;

        Window *GetWindow() override;

    private:
        Scope<PerspectiveCameraController>  m_CameraController;
        Scope<GraphicLayerAbstractionFactory> m_GLAFactory;
        Scope<Window> m_Window;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication();
}

