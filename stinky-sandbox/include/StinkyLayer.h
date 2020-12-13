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
        explicit StinkyLayer(GraphicLayerAbstractionFactory *glaFactory, FPSCamera *cameraController,
                             EventController &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(const Timestep &ts) override;

    private:
        GraphicLayerAbstractionFactory *m_GLAFactory;
        Scene m_Scene;
        Ref<FrameBuffer> m_FrameBuffer;
        FPSCamera *m_Camera;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
