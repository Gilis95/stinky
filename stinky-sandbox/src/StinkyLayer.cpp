#include "StinkyLayer.h"


#include "renderer/Renderer.h"
#include "renderer/RendererFactory.h"
#include "renderer/VertexBuffer.h"

namespace stinky {

    StinkyLayer::StinkyLayer()
        : Layer("Stinky Layer")
        , m_RendererFactory(RendererFactory::create(RendererFactory::API::OpenGL))
        , m_Renderer(CreateRef<Renderer>(m_RendererFactory->createRendererApi()))
        , m_VertexArray(m_RendererFactory->createVertexArray()) {
    }

    void StinkyLayer::OnAttach() {
        float positions[16] = {
        0.7f, -1.0f,  1.0f, -1.0f, //0
        0.7f, 1.0f, 1.0f, 1.0f, //1
        -0.7f, 1.0f, -1.0f, 1.0f, //2
        -0.7f, -1.0f, -1.0f, -1.0f, //3
        };

        unsigned int indices[6] = {
                0, 1, 2,
                2, 3, 0
        };


        //create array buffer, containing shape positions and bind it

        const auto vertexBuffer = m_RendererFactory->createVertexBuffer(positions, 16 * sizeof(float), {
            {ShaderDataType::Float2,"position"},
            {ShaderDataType::Float2,"texCoord"},
            });

        //bind currently bound array buffer to first element of currently bound vertex array
        m_VertexArray->addVertexBuffer(vertexBuffer);

        //Create index buffer, that will define shape vertex positions
        const auto indexBuffer = m_RendererFactory->createIndexBuffer(indices, 6);


        m_VertexArray->setIndexBuffer(indexBuffer);
        //Parse fragment and vertex shader and bind them

        const auto texture = m_RendererFactory->createTexture("D:\\workspace\\stinky\\stinky-sandbox\\resources\\mb.png");
        texture->bind(0);

        m_Shader = m_RendererFactory->createShader("D:\\workspace\\stinky\\stinky-sandbox\\resources\\shaders\\basic.shader");
        m_Shader->bind();
        m_Shader->setInteger("u_Texture", 0);
    }

    void StinkyLayer::OnDetach() {

    }

    void StinkyLayer::OnUpdate(Timestep ts)
    {
        m_Renderer->clear();
        m_Renderer->draw(m_VertexArray, m_Shader);
    }

}
