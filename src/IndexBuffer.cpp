//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>
#include "IndexBuffer.h"

#include "Logger.h"

IndexBuffer::IndexBuffer(const void *data, unsigned int count) : m_Count(count) {
    GLCall(glGenBuffers(1, &m_RendererID));
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}