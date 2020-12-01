#pragma once

#include <glm/glm.hpp>

#include "event/EventController.h"
#include "event/Layer.h"
#include "scene/Scene.h"
#include "StinkyPrerequisites.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public Layer {
    public:
        explicit StinkyLayer(GraphicLayerAbstractionFactory *glaFactory, FPSCameraController *cameraController,
                             EventController &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(const Timestep &ts) override;

    private:
        GraphicLayerAbstractionFactory *m_GLAFactory;
        Scene m_Scene;
        Ref<FrameBuffer> m_FrameBuffer;
        Scope<FPSCamera> m_Camera;
        FPSCameraController *m_CameraController;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
