//
// Created by christian on 04/08/2020.
//
#include <glm/ext.hpp>
#include "stinkypch.h"
#include "renderer/Renderer3D.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer3D::Renderer3D(const Ref<RendererFactory> &rendererFactory)
            : Renderer(rendererFactory->CreateRendererApi()),
              m_RendererFactory(rendererFactory) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer3D::Init() const {
        m_RendererApi->Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer3D::Clear() const {
        m_RendererApi->Clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::SceneNode
    Renderer3D::DrawCube(const glm::vec3 &translate, const glm::vec3 &scale,
                         const glm::vec4 &color) const {
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec3 cubeCoordinates[8] = {
                //Front Quad
                {-1.0f, -1.0f, -1.0}
                , //0
                {1.0f , -1.0f, -1.0}
                , //1
                {1.0f , 1.0f , -1.0}
                , //2
                {-1.0f, 1.0f , -1.0}
                , //3

                // Back Quad
                {1.0f , -1.0f, 1.0}
                , //4
                {-1.0f, -1.0f, 1.0}
                , //5
                {-1.0f, 1.0f , 1.0}
                , //6
                {1.0f , 1.0f , 1.0} //7
        };

        unsigned int indices[36] = {
                // front side
                0, 1, 3, 1, 2, 3,

                // right side
                1, 4, 2, 4, 6, 2,

                // back side
                4, 5, 7, 5, 6, 7,

                // left side
                0, 5, 3, 5, 6, 3,

                // down side
                3, 2, 6, 2, 7, 6,

                // upper side
                0, 1, 2, 2, 3, 0,};


        glm::mat4 model = glm::translate(glm::mat4(1.0f), translate)
                          * glm::scale(glm::mat4(1.0f), {scale.x, scale.y, scale.z});

        Renderer::SceneNode rendererData;

        //create array buffer, containing shape positions and bind it
        const auto vertexBuffer = m_RendererFactory->CreateVertexBuffer(cubeCoordinates,
                                                                        24 * sizeof(float), {
                                                                                {ShaderDataType::Float3, "position"}
                                                                        });
        rendererData.vertexArray = m_RendererFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        rendererData.vertexArray->AddVertexBuffer(vertexBuffer);

        //Create index buffer, that will define shape vertex positions
        const auto indexBuffer = m_RendererFactory->CreateIndexBuffer(indices, 36);

        rendererData.vertexArray->SetIndexBuffer(indexBuffer);

        rendererData.shader = m_RendererFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/basic.shader");
        rendererData.shader->Bind();
        rendererData.shader->SetInteger("u_Texture", 0);

        Draw(rendererData);

        return rendererData;
    }
}