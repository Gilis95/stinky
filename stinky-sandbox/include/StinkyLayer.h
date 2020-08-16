#pragma once

#include "event/Layer.h"

#include <glm/glm.hpp>

#include "renderer/FrameBuffer.h"
#include "renderer/Renderer2D.h"
#include "renderer/RendererFactory.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public Layer {
    public:
        StinkyLayer();

        virtual void OnAttach() override;

        virtual void OnDetach() override;

        virtual void OnUpdate(Timestep ts) override;

    private:
        Ref<RendererFactory> m_RendererFactory;
        Renderer2D m_Renderer;
        Renderer::SceneNodes m_SceneNodes;
        Ref<FrameBuffer> m_FrameBuffer;

        glm::mat4 m_ViewProjection;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
