#include <iostream>
#include <malloc.h>
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "renderer/Renderer.h"
#include "renderer/RendererFactory.h"
#include "renderer/VertexArray.h"
#include "window/Window.h"


int main() {

    bool closed = false;

    stinky::Scope< stinky::Window> window = stinky::Window::create(stinky::Window::API::GLFW);

    window->setCloseCallback([&]()
        {
            closed = true;
        });

    float positions[16] = {
            -2.0f, -2.0f, -1.0f, -1.0f, //0
            2.0f, -2.0f, 1.0f, -1.0f, //1
            -2.0f, 2.0f, -1.0f, 1.0f, //2
            2.0f, 2.0f, 1.0f, 1.0f, //3
    };

    unsigned int indices[6] = {
            0, 1, 2,
            1, 3, 2
    };

    {
       // GLCall(glEnable(GL_BLEND));
       // GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

        auto factory = stinky::RendererFactory::create(stinky::RendererFactory::API::OpenGL);

        //create vertex array and bind it
        stinky::Ref< stinky::VertexArray> vertexArray = factory->createVertexArray();
        //create array buffer, containing shape positions and bind it

        stinky::Ref < stinky::VertexBuffer> vertexBuffer = factory->createVertexBuffer({ 
            {stinky::ShaderDataType::Float2,"position"},
            {stinky::ShaderDataType::Float2,"texCoord"},
        });

        vertexBuffer->setData(positions, 16 * sizeof(float));


        //Create index buffer, that will define shape vertex positions
        stinky::Ref < stinky::IndexBuffer> indexBuffer = factory->createIndexBuffer(indices, 6);

        //bind currently bound array buffer to first element of currently bound vertex array
        vertexArray->addVertexBuffer(vertexBuffer);
        vertexArray->setIndexBuffer(indexBuffer);


        //Parse fragment and vertex shader and bind them
        
        stinky::Ref < stinky::Shader> shader = factory->createShader("../resources/shaders/basic.shader");
        stinky::Ref < stinky::Texture> texture = factory->createTexture("../resources/mb.png");

        texture->bind(0);
        shader->bind();
        shader->setInteger("u_Texture", 0);

        stinky::Renderer renderer(factory->createRendererApi());

        while (!closed) {
            renderer.clear();
            renderer.draw(vertexArray, indexBuffer, shader);
        }
    }

    return 0;
}
