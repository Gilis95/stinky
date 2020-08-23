#pragma once


#include <glm/glm.hpp>

#include "event/EventController.h"
#include "event/Layer.h"
#include "renderer/FrameBuffer.h"
#include "renderer/OrthographicCamera.h"
#include "renderer/OrthographicCameraController.h"
#include "renderer/Renderer2D.h"
#include "renderer/RendererFactory.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public Layer {
    public:
        StinkyLayer(EventController& eventController);

        virtual void OnAttach() override;

        virtual void OnDetach() override;

        virtual void OnUpdate(const Timestep &ts) override;

    private:
        Ref<RendererFactory> m_RendererFactory;
        Renderer2D m_Renderer;
        Renderer::SceneNodes m_SceneNodes;
        Ref<FrameBuffer> m_FrameBuffer;

        OrthographicCamera m_OrthographicCamera;
        OrthographicCameraController m_OrthographicCameraController;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
