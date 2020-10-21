//
// Created by christian on 06/08/2020.
//
#include "renderer/Renderer.h"

#include "ecs/MaterialComponent.h"
#include "ecs/MeshComponents.h"
#include "ecs/ProgramComponent.h"
#include "ecs/TransformationComponents.h"
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
    void Renderer::BeginScene(const glm::mat4 &viewProjection) {
        m_ViewProjection = viewProjection;
        m_TextureId = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::EndScene() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Draw(const RenderCommand &command) {

        glm::mat4 model = glm::translate(glm::mat4(1.0f), command.translateComponent.translation)
                          * glm::scale(glm::mat4(1.0f), command.scaleComponent.scale);

        unsigned vectorsCount = command.meshComponent.verticesCount / 4;
        glm::vec4 cubeCoordinates[vectorsCount];

        for (int i = 0; i < vectorsCount; ++i) {
            cubeCoordinates[i] = model * command.meshComponent.vertices[i];
        }

        //create array buffer, containing shape positions and bind it
        const auto vertexBuffer = m_RendererFactory->CreateVertexBuffer(cubeCoordinates,
                                                                        command.meshComponent.verticesCount *
                                                                        sizeof(float), {
                                                                                {ShaderDataType::Float4, "position"}
                                                                        });
        auto vertexArray = m_RendererFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        vertexArray->AddVertexBuffer(vertexBuffer);

        //Create index buffer, that will define shape vertex positions
        const auto indexBuffer = m_RendererFactory->CreateIndexBuffer(command.meshComponent.indices,
                                                                      command.meshComponent.indicesCount);

        vertexArray->SetIndexBuffer(indexBuffer);

        if (command.materialComponent.type == MaterialType::TEXTURED) {
            command.materialComponent.material->Bind(m_TextureId);
            ++m_TextureId;
        }

        command.programComponent.program->Bind();
        command.programComponent.program->SetMat4("u_ViewProjection", m_ViewProjection);

        if (command.materialComponent.type == MaterialType::SOLID) {
            command.programComponent.program->SetFloat4("u_Colour", command.materialComponent.colour);
        } else {
            command.programComponent.program->SetInteger("u_Texture", command.materialComponent.material->m_RendererID);
        }

        vertexArray->Bind();
        m_RendererApi->DrawIndexed(vertexArray);
    }


}