//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>

#include "gla/platform/opengl/OpenGLVertexArray.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
static GLenum ShaderDataTypeToOpenGLBaseType(const uint32_t &type) {
  if (type & static_cast<int>(component_type::FLOAT)) {
    return GL_FLOAT;
  } else if (type & static_cast<int>(component_type::DOUBLE)) {
    return GL_DOUBLE;
  } else if (type & (static_cast<int>(component_type::INT32) |
                     static_cast<int>(component_type::INT64))) {
    return GL_INT;
  } else if (type & static_cast<int>(component_type::BOOL)) {
    return GL_BOOL;
  } else {
    STINKY_ERROR("Unknown component type!");
    return 0;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &m_RendererID); }

/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &m_RendererID);
}

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexArray::Bind() const {
  glBindVertexArray(m_RendererID);

  ReturnUnless(m_IndexBuffer);
  m_IndexBuffer->bind();
}

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexArray::Unbind() const {
  glBindVertexArray(0);

  ReturnUnless(m_IndexBuffer);
  m_IndexBuffer->unbind();
}

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexArray::set_index_buffer(
    const shared_ptr<index_buffer> &indexBuffer) {
  glBindVertexArray(m_RendererID);
  indexBuffer->bind();

  m_IndexBuffer = indexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////////////
void OpenGLVertexArray::add_vertex_buffer(const shared_ptr<vertex_buffer> &vb) {
  Bind();
  vb->Bind();

  const auto &layout = vb->GetBufferLayout();
  for (const auto &element : layout) {

    auto glType = ShaderDataTypeToOpenGLBaseType(element.type);
    if (glType == GL_INT) {
      glEnableVertexAttribArray(m_VertexBufferIndex);
      glVertexAttribIPointer(m_VertexBufferIndex, element.GetComponentCount(),
                             glType,
                             layout.GetStride(), (const void *)element.offset);
    } else {
        glEnableVertexAttribArray(m_VertexBufferIndex);
        glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.type),
                              element.normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              (const void *)element.offset);
    }

    ++m_VertexBufferIndex;
  }

  m_VertexBuffers.push_back(vb);

  vb->Unbind();
  Unbind();
}
} // namespace stinky