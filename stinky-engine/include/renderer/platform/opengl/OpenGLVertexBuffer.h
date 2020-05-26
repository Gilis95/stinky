//
// Created by christian on 1/19/20.
//
#pragma once

#include <iostream>
#include <vector>

#include "Macros.h"
#include "renderer/VertexBuffer.h"


namespace stinky {
    class OpenGLVertexBuffer : VertexBuffer {
    private:
        unsigned int m_RendererID;
        BufferLayout m_Layout;
    public:
        OpenGLVertexBuffer(BufferLayout& layout);
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
    };

}
