//
// Created by christian on 06/08/2020.
//
#include "renderer/Renderer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::Renderer(const Ref<RendererApi> &rendererApi)
            : m_RendererApi(rendererApi) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::~Renderer() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::BeginScene(glm::mat4 viewProjection) {
        m_ViewProjection = viewProjection;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::EndScene() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Draw(const SceneNode &sceneNode) const {
        sceneNode.shader->SetMat4("u_ViewProjection", m_ViewProjection);
        sceneNode.shader->Bind();
        sceneNode.vertexArray->Bind();

        m_RendererApi->DrawIndexed(sceneNode.vertexArray);
    }

}