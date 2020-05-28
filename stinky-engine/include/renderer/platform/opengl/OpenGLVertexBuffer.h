//
// Created by christian on 1/19/20.
//
#pragma once

#include <glad/glad.h>

#include "renderer/VertexBuffer.h"


namespace stinky {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(const BufferLayout& layout, unsigned int size);

        OpenGLVertexBuffer(const BufferLayout& layout, const void* data, unsigned int size);

        ~OpenGLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void setData(const void* data, unsigned int size) override;

        [[nodiscard]] const BufferLayout& getBufferLayout() const override
        {
            return m_Layout;
        }

        void setBufferLayout(BufferLayout& layout) override
        {
            m_Layout = layout;
        }
    private:
        GLuint m_RendererID;
        BufferLayout m_Layout;
    };

}
