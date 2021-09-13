//
// Created by christian on 1/19/20.
//
#pragma once

#include "gla/vertex_buffer.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLVertexBuffer : public vertex_buffer {
    public:
        OpenGLVertexBuffer(BufferLayout layout, unsigned int size);

        OpenGLVertexBuffer(BufferLayout layout, const void *data, unsigned int size);

        ~OpenGLVertexBuffer() override;

        void Bind() const override;

        void Unbind() const override;

        void SetData(const void *data, unsigned int size) override;

        [[nodiscard]] const BufferLayout &GetBufferLayout() const override {
            return m_Layout;
        }

        void SetBufferLayout(BufferLayout &layout) override {
            m_Layout = layout;
        }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////