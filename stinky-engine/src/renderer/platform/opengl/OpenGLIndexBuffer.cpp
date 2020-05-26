//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>
#include "renderer/platform/opengl/OpenGLIndexBuffer.h"

#include "Logger.h"

namespace stinky {
    OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, unsigned int count) : m_Count(count) {
        GLCall(glGenBuffers(1, &m_RendererID));
        bind();
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));

    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void OpenGLIndexBuffer::bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGLIndexBuffer::unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}