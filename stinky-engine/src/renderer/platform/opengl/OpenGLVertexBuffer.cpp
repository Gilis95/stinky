//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>

#include "Logger.h"
#include "renderer/platform/opengl/OpenGLVertexBuffer.h"

namespace stinky {
    OpenGLVertexBuffer::OpenGLVertexBuffer(BufferLayout& layout) : m_Layout(layout)
    {
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void OpenGLVertexBuffer::bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGLVertexBuffer::unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void OpenGLVertexBuffer::setData(const void* data, unsigned int size) {
        GLCall(glGenBuffers(1, &m_RendererID));
        bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
}