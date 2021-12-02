//
// Created by christian on 1/19/20.
//
#include "stinkypch.h"

#include <glm/ext.hpp>

#include "gla/vertex_array.h"
#include "gla/vertex_buffer.h"

namespace stinky {
//    /////////////////////////////////////////////////////////////////////////////////////////
//    struct VertexData {
//        glm::vec4 coordinates;
//        glm::vec2 textureCoordinates;
//    };
//
//    /////////////////////////////////////////////////////////////////////////////////////////
//    Renderer2D::Renderer2D(const Ref<GraphicLayerAbstractionFactory>
//    &rendererFactory)
//            : Renderer(rendererFactory->CreateRendererApi()),
//            m_RendererFactory(rendererFactory) {
//        Init();
//    }
//
//    /////////////////////////////////////////////////////////////////////////////////////////
//    void Renderer2D::Init() const {
//        m_RendererApi->Init();
//    }
//
//    /////////////////////////////////////////////////////////////////////////////////////////
//    void Renderer2D::Clear() const {
//        m_RendererApi->Clear();
//    }
//
//    /////////////////////////////////////////////////////////////////////////////////////////
//    Renderer::SceneNode
//    Renderer2D::CreateQuad(const glm::vec2 &translate, const glm::vec2 &scale,
//                           const glm::vec4 &color) {
//        VertexData data[4] = {
//                {
//                        {-1.0f, -1.0f, 0.0f, 1.0f}, {-1.0f, -1.0f}
//                }
//                , //0
//                {
//                        {1.0f , -1.0f, 0.0f, 1.0f}, {1.0f , -1.0f}
//                }
//                , //1
//                {
//                        {1.0f , 1.0f , 0.0f, 1.0f}, {1.0f , 1.0f}
//                }
//                , //2
//                {
//                        {-1.0f, 1.0f , 0.0f, 1.0f}, {-1.0f, 1.0f}
//                } //3
//        };
//
//        unsigned int indices[6] = {
//                0, 1, 3, 1, 2, 3
//        };
//
//        Renderer::SceneNode rendererData;
//
//        glm::mat4 model =glm::translate(glm::mat4(1.0f), {translate.x,
//        translate.y, 1.0})
//                         * glm::scale(glm::mat4(1.0f), {scale.x,
//                         scale.y, 1.0f});
//
//        for (auto &i : data) {
//            i.coordinates = model * i.coordinates;
//        }
//
//        rendererData.vertexArray = m_RendererFactory->CreateVertexArray();
//        //create array buffer, containing shape positions and bind it
//        const auto positionBuffer =
//        m_RendererFactory->CreateVertexBuffer(&data, sizeof(data), {
//                {  ShaderDataType::Float4, "position"}
//                , {ShaderDataType::Float2, "texCoord"}
//        });
//
//        //bind currently bound array buffer to first element of currently
//        bound vertex array
//        rendererData.vertexArray->AddVertexBuffer(positionBuffer);
//
//        //Create index buffer, that will define shape vertex positions
//        const auto indexBuffer = m_RendererFactory->CreateIndexBuffer(indices,
//        6);
//
//        rendererData.vertexArray->SetIndexBuffer(indexBuffer);
//
//        //Parse fragment and vertex shader and bind them
//        rendererData.texture = m_RendererFactory->CreateTexture(1, 1);
////        rendererData.texture =
///m_RendererFactory->CreateTexture("/home/christian/workspace/stinky/stinky-sandbox/resources/mb.png");
//        uint32_t defaultWhiteTextureData = 0xffffffff;
//        rendererData.texture->SetData(&defaultWhiteTextureData);
//        rendererData.texture->Bind(0);
//
//        rendererData.shader = m_RendererFactory->CreateShader(
//                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/basic.shader");
//        rendererData.shader->Bind();
//        rendererData.shader->SetInteger("u_Texture", 0);
//
//        return rendererData;
//    }

}