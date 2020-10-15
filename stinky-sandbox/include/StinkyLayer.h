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
        StinkyLayer(EventController &eventController);

        virtual void OnAttach() override;

        virtual void OnDetach() override;

        virtual void OnUpdate(const Timestep &ts) override;

    private:
        Ref<GraphicLayerAbstractionFactory> m_RendererFactory;
        Scene                               m_Scene;
        Ref<FrameBuffer>                    m_FrameBuffer;
        Scope<PerspectiveCamera>            m_Camera;
        Scope<PerspectiveCameraController>  m_CameraController;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
