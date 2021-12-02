//
// Created by christian on 1/19/20.
//
#include "gla/platform/opengl/opengl_index_buffer.h"
#include <glad/glad.h>

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
opengl_index_buffer::opengl_index_buffer(const void *data, uint32_t count)
    : m_Count(count), m_RendererID(0) {
  glGenBuffers(1, &m_RendererID);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data,
               GL_STATIC_DRAW);
}

/////////////////////////////////////////////////////////////////////////////////////////
opengl_index_buffer::~opengl_index_buffer() { glDeleteBuffers(1, &m_RendererID); }

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_index_buffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_index_buffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // namespace stinky