#pragma once

#include <glm/glm.hpp>

#include "camera/PerspectiveCamera.h"
#include "camera/PerspectiveCameraController.h"
#include "event/EventController.h"
#include "event/Layer.h"
#include "gla/FrameBuffer.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "scene/Scene.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public Layer {
    public:
        explicit StinkyLayer(GraphicLayerAbstractionFactory *glaFactory, PerspectiveCameraController *cameraController,
                             EventController &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(const Timestep &ts) override;

    private:
        GraphicLayerAbstractionFactory*     m_GLAFactory;
        Scene                               m_Scene;
        Ref<FrameBuffer>                    m_FrameBuffer;
        Scope<PerspectiveCamera>            m_Camera;
        PerspectiveCameraController*        m_CameraController;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
