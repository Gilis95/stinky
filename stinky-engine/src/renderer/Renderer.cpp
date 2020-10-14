//
// Created by christian on 06/08/2020.
//
#include "renderer/Renderer.h"

#include "ecs/MeshComponents.h"
#include "ecs/TransformationComponents.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"
#include "gla/VertexArray.h"
#include "gla/RendererApi.h"
#include "gla/Shader.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::Renderer(const GraphicLayerAbstractionFactory *rendererFactory)
            : m_RendererFactory(rendererFactory), m_RendererApi(m_RendererFactory->CreateRendererApi()) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::~Renderer() {
    }

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
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::EndScene() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::Draw(const RenderCommand &command) const {

        glm::mat4 model = glm::translate(glm::mat4(1.0f), command.translateComponent.translation)
                          * glm::scale(glm::mat4(1.0f), command.scaleComponent.scale);

        int vectorsCount = command.verticesComponent.verticesCount / 4;
        glm::vec4 cubeCoordinates[vectorsCount];

        for (int i = 0; i < vectorsCount; ++i) {
            cubeCoordinates[i] = model * command.verticesComponent.vertices[i];
        }

        //create array buffer, containing shape positions and bind it
        const auto vertexBuffer = m_RendererFactory->CreateVertexBuffer(cubeCoordinates,
                                                                        command.verticesComponent.verticesCount *
                                                                        sizeof(float), {
                                                                                {ShaderDataType::Float4, "position"}
                                                                        });
        auto vertexArray = m_RendererFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        vertexArray->AddVertexBuffer(vertexBuffer);

        //Create index buffer, that will define shape vertex positions
        const auto indexBuffer = m_RendererFactory->CreateIndexBuffer(command.indicesComponent.indices,
                                                                      command.indicesComponent.indicesCount);

        vertexArray->SetIndexBuffer(indexBuffer);

        auto shader = m_RendererFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/basic.shader");
        shader->Bind();
        shader->SetInteger("u_Texture", 0);
        shader->SetMat4("u_ViewProjection", m_ViewProjection);

        vertexArray->Bind();

        m_RendererApi->DrawIndexed(vertexArray);
    }


}