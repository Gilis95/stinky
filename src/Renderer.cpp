//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>
#include <iostream>
#include "Renderer.h"

#include "Logger.h"

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
