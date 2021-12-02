//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>

#include <utility>

#include "gla/platform/opengl/OpenGLVertexBuffer.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::OpenGLVertexBuffer(BufferLayout layout, unsigned int size)
    : m_Layout(std::move(layout)) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
}

/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::OpenGLVertexBuffer(BufferLayout layout, const void *data,
                                       unsigned int size)
    : m_Layout(std::move(layout)) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexBuffer::SetData(const void *data, unsigned int size) {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
} // namespace stinky