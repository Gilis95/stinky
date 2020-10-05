//
// Created by christian on 1/19/20.
//
#pragma once

#include <glad/glad.h>

#include "gla/VertexBuffer.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(const BufferLayout &layout, unsigned int size);

        OpenGLVertexBuffer(const BufferLayout &layout, const void *data, unsigned int size);

        ~OpenGLVertexBuffer();

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
        GLuint m_RendererID;
        BufferLayout m_Layout;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////