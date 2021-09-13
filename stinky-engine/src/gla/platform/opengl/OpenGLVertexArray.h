//
// Created by christian on 1/19/20.
//
#pragma once

#include <glad/glad.h>

#include "gla/index_buffer.h"
#include "gla/vertex_buffer.h"
#include "gla/vertex_array.h"


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLVertexArray : public vertex_array {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray();

        void Bind() const override;

        void Unbind() const override;

        [[nodiscard]] const std::vector<shared_ptr<vertex_buffer>> &
        get_vertex_buffers() const override { return m_VertexBuffers; }

        [[nodiscard]] const shared_ptr<index_buffer> &
        get_index_buffer() const override { return m_IndexBuffer; }

        void set_index_buffer(const shared_ptr<index_buffer> &indexBuffer) override;

        void add_vertex_buffer(const shared_ptr<vertex_buffer> &vb) override;

    private:
        uint32_t  m_RendererID;
        uint32_t  m_VertexBufferIndex = 0;
        std::vector<shared_ptr<vertex_buffer>> m_VertexBuffers;
        shared_ptr<index_buffer> m_IndexBuffer;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////