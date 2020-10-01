#pragma once


#include <glm/glm.hpp>
#include <camera/OrthographicCameraController.h>

#include "event/EventController.h"
#include "event/Layer.h"
#include "gla/FrameBuffer.h"
#include "camera/PerspectiveCamera.h"
#include "camera/PerspectiveCameraController.h"
#include "renderer/Renderer3D.h"
#include "gla/GraphicLayerAbstractionFactory.h"

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
        Renderer3D m_Renderer;
        Renderer::SceneNodes m_SceneNodes;
        Ref<FrameBuffer> m_FrameBuffer;

//        OrthographicCamera m_OrthographicCamera;
//        OrthographicCameraController m_OrthographicCameraController;

        PerspectiveCamera m_PerspectiveCamera;
        PerspectiveCameraController m_PerspectiveCameraController;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
