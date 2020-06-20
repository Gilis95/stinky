#include "renderer/Renderer.h"
#include "renderer/RendererFactory.h"
#include "window/Window.h"


int main() {

    bool closed = false;
    stinky::Log::init();


    auto window = stinky::Window::Create(stinky::Window::API::GLFW);

    window->SetEventCallback([&]()
        {
            closed = true;
        });

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

    {
        const auto factory = stinky::RendererFactory::create(stinky::RendererFactory::API::OpenGL);

        const stinky::Renderer renderer(factory->createRendererApi());

        //create vertex array and bind it
        auto vertexArray = factory->createVertexArray();
        //create array buffer, containing shape positions and bind it

        auto vertexBuffer = factory->createVertexBuffer(positions, 16 * sizeof(float), {
            {stinky::ShaderDataType::Float2,"position"},
            {stinky::ShaderDataType::Float2,"texCoord"},
            });

        //bind currently bound array buffer to first element of currently bound vertex array
        vertexArray->addVertexBuffer(vertexBuffer);

        //Create index buffer, that will define shape vertex positions
        const auto indexBuffer = factory->createIndexBuffer(indices, 6);

        vertexArray->setIndexBuffer(indexBuffer);

        //Parse fragment and vertex shader and bind them

        const auto texture = factory->createTexture("D:\\workspace\\stinky\\stinky-sandbox\\resources\\mb.png");
        texture->bind(0);

        auto shader = factory->createShader("D:\\workspace\\stinky\\stinky-sandbox\\resources\\shaders\\basic.shader");
        shader->bind();
        shader->setInteger("u_Texture", 0);

        while (!closed) {
            renderer.clear();
            renderer.draw(vertexArray, shader);

            window->OnUpdate();
        }
    }

    return 0;
}
