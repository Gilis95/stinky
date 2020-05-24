#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <malloc.h>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int main() {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cout << "Maikata si eba eii!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 640, "Na maikati monitora", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "Maikata si eba eii!" << std::endl;
        return -1;
    }

    // create context for current window
    glfwMakeContextCurrent(window);

    glfwSwapInterval(5);

    if (!gladLoadGL()) {
        glfwTerminate();
        std::cout << "Maikata si eba eii!" << std::endl;
        return -1;
    }

    float positions[16] = {
            -2.0f, -2.0f, -1.0f, -1.0f, //0
            2.0f, -2.0f, 1.0f, -1.0f, //1
            -2.0f, 2.0f, -1.0f, 1.0f, //2
            2.0f, 2.0f, 1.0f, 1.0f, //3
    };

    unsigned int indeces[6] = {
            0, 1, 2,
            1, 3, 2
    };

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

        //create vertex array and bind it
        VertexArray vertexArray;
        //create array buffer, containing shape positions and bind it
        VertexBuffer vertexBuffer(positions, 16 * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);

        //bind currently bound array buffer to first element of currently bound vertex array
        vertexArray.addBuffer(vertexBuffer, layout);

        //Create index buffer, that will define shape vertex positions
        IndexBuffer indexBuffer(indeces, 6);

        //Parse fragment and vertex shader and bind them
        Shader shader("resources/shaders/basic.shader");
        Texture texture("/home/christian/workspace/opengl/engine/resources/mb.png");

        texture.bind();
        shader.bind();
        shader.setUniform1i("u_Texture", 0);

        Renderer renderer;

        std::cout << glGetString(GL_VERSION) << std::endl;

        while (!glfwWindowShouldClose(window)) {
            renderer.clear();
            renderer.draw(vertexArray, indexBuffer, shader);

            // swap front and back buffer
            GLCall(glfwSwapBuffers(window));

            //poll for process events
            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}