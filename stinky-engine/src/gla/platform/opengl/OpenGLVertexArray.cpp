//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>

#include "gla/platform/opengl/OpenGLVertexArray.h"


namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    static GLenum ShaderDataTypeToOpenGLBaseType(const ShaderDataType &type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;

            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;

            case ShaderDataType::Bool:
                return GL_BOOL;
            default: STINKY_LOG_ERROR_AND_BREAK("Unknown ShaderDataType!");
                return 0;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);

        ReturnUnless(m_IndexBuffer)
        m_IndexBuffer->bind();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);

        ReturnUnless(m_IndexBuffer)
        m_IndexBuffer->unbind();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLVertexArray::set_index_buffer(const shared_ptr<index_buffer> &indexBuffer) {
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
            switch (element.m_Type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(m_VertexBufferIndex,
                                          element.GetComponentCount(),
                                          ShaderDataTypeToOpenGLBaseType(element.m_Type),
                                          element.m_Normalized ? GL_TRUE : GL_FALSE,
                                          layout.GetStride(),
                                          (const void *) element.m_Offset);
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    uint8_t count = element.GetComponentCount();
                    for (uint8_t i = 0; i < count; i++) {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex,
                                              count,
                                              ShaderDataTypeToOpenGLBaseType(element.m_Type),
                                              element.m_Normalized ? GL_TRUE : GL_FALSE,
                                              layout.GetStride(),
                                              (const void *) (sizeof(float) * count * i));
                        glVertexAttribDivisor(m_VertexBufferIndex, 1);
                        m_VertexBufferIndex++;
                    }
                    break;
                }
                default: STINKY_LOG_ERROR_AND_BREAK("Unknown ShaderDataType!");
            }
        }

        m_VertexBuffers.push_back(vb);

        vb->Unbind();
        Unbind();
    }
}