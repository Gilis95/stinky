//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>
#include "gla/platform/opengl/OpenGLIndexBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLIndexBuffer::OpenGLIndexBuffer(const void *data, uint32_t count) : m_Count(count),
                                                                                 m_RendererID(0) {
        glGenBuffers(1, &m_RendererID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}