#include <application/Application.h>

#include <StinkyPrerequisites.h>


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
        Scope<FPSCamera>  m_Camera;
        Scope<GraphicLayerAbstractionFactory> m_GLAFactory;
        Scope<Window> m_Window;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication();
}

