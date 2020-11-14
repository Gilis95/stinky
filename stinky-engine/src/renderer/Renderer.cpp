//
// Created by christian on 06/08/2020.
//
#include "renderer/Renderer.h"

#include "ecs/MaterialComponent.h"
#include "ecs/MeshComponents.h"
#include "ecs/ProgramComponent.h"
#include "ecs/TransformComponent.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"
#include "gla/VertexArray.h"
#include "gla/RendererApi.h"
#include "gla/Shader.h"
#include "gla/Texture.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::Renderer(const GraphicLayerAbstractionFactory *rendererFactory)
            : m_RendererFactory(rendererFactory), m_RendererApi(m_RendererFactory->CreateRendererApi()) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::~Renderer() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Init() const {
        m_RendererApi->Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Clear() const {
        m_RendererApi->Clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::BeginScene(const glm::mat4 &view, const glm::mat4 &projection) {
        m_View = view;
        m_Projection = projection;
        m_TextureId = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::EndScene() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Draw(const RenderCommand &command) {

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), command.transformComponent.translation);
        glm::mat4 translationRotationX = glm::rotate(translation, command.transformComponent.rotation.x,
                                                     glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 translationRotationY = glm::rotate(translationRotationX, command.transformComponent.rotation.y,
                                                     glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 translationRotation = glm::rotate(translationRotationY, command.transformComponent.rotation.z,
                                                    glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 modelMatrix = glm::scale(translationRotation, command.transformComponent.scale);

        if (command.materialComponent.type == MaterialType::TEXTURED) {
            command.materialComponent.material->Bind(m_TextureId);
            //initialize shader program
            command.programComponent.program->Bind();
            command.programComponent.program->SetMat4("u_ViewMatrix", m_View);
            command.programComponent.program->SetMat4("u_ProjectionMatrix", m_Projection);
            command.programComponent.program->SetMat4("u_ModelMatrix", modelMatrix);
            command.programComponent.program->SetInteger("u_Texture", command.materialComponent.material->m_RendererID);

            // draw
            command.meshComponent.vertexArray->Bind();
            m_RendererApi->DrawIndexed(command.meshComponent.vertexArray);

            // cleanup
            command.meshComponent.vertexArray->Unbind();
            command.materialComponent.material->Unbind(m_TextureId);

            ++m_TextureId;
        } else {
            //initialize shader program
            command.programComponent.program->Bind();
            command.programComponent.program->SetMat4("u_ViewMatrix", m_View);
            command.programComponent.program->SetMat4("u_ProjectionMatrix", m_Projection);
            command.programComponent.program->SetMat4("u_ModelMatrix", modelMatrix);
            command.programComponent.program->SetFloat4("u_Colour", command.materialComponent.colour);

            // draw
            command.meshComponent.vertexArray->Bind();
            m_RendererApi->DrawIndexed(command.meshComponent.vertexArray);

            // cleanup
            command.meshComponent.vertexArray->Unbind();
        }
    }


}