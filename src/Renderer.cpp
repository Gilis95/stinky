//
// Created by christian on 1/19/20.
//

#include <GL/glew.h>
#include <iostream>
#include "../include/Renderer.h"


void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char *functionName, const char *fileName, int line) {
    while (GLenum err = glGetError()) {
        std::cout << "[OpenGL Error] (" << err << "): " <<
                  functionName << " " << fileName << ":" << line << std::endl;
        return false;
    }

    return true;
}


void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
