//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>

#include "renderer/platform/opengl/OpenGLVertexBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLVertexBuffer::OpenGLVertexBuffer(const BufferLayout &layout, unsigned int size) : m_Layout(layout) {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLVertexBuffer::OpenGLVertexBuffer(const BufferLayout &layout, const void *data, unsigned int size) : m_Layout(
            layout) {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexBuffer::SetData(const void *data, unsigned int size) {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}