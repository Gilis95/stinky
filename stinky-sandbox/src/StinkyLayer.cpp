#include <glm/ext.hpp>
#include "StinkyLayer.h"


#include "renderer/Renderer2D.h"
#include "renderer/RendererFactory.h"
#include "renderer/VertexBuffer.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer()
            : Layer("Stinky Layer"), m_RendererFactory(RendererFactory::create(RendererFactory::API::OpenGL)),
              m_Renderer(m_RendererFactory), m_ViewProjection(glm::ortho(-1.68f, 1.68f, -1.0f, 1.0f, -1.0f, 1.0f)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnAttach() {
        m_FrameBuffer = m_RendererFactory->CreateFrameBuffer({1280, 720});
        m_SceneNodes.push_back(m_Renderer.CreateQuad({-0.5f, 0.5f}, {0.1f, 0.1f}, {1.0f, 0.0f, 0.0f, 1.0f}));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnDetach() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnUpdate(Timestep ts) {
        m_FrameBuffer->Unbind();
        m_Renderer.Clear();

        m_Renderer.BeginScene(m_ViewProjection);

        std::for_each(m_SceneNodes.begin(), m_SceneNodes.end(), [&](const Renderer::SceneNode &sceneNode) -> void {
            m_Renderer.Draw(sceneNode);
        });
        m_FrameBuffer->Bind();

        m_Renderer.EndScene();
    }
}
