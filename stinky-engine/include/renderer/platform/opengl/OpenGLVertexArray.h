//
// Created by christian on 1/19/20.
//
#pragma once

#include <renderer/IndexBuffer.h>

#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"


namespace stinky {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray();

        void bind() const override;

        void unbind() const override;

       [[nodiscard]] const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
        [[nodiscard]] const Ref<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }

        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        void addVertexBuffer(const Ref<VertexBuffer>& vg) override;
    private:
        unsigned int m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}