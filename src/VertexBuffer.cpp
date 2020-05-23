//
// Created by christian on 1/19/20.
//


#include <GL/glew.h>
#include "../include/VertexBuffer.h"
#include "../include/Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendererID));
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}