//
// Created by christian on 1/19/20.
//
#pragma once

#include <glad/glad.h>

#include "gla/IndexBuffer.h"
#include "gla/VertexBuffer.h"
#include "gla/VertexArray.h"


namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray();

        void Bind() const override;

        void Unbind() const override;

        [[nodiscard]] const std::vector<Ref<VertexBuffer>> &
        GetVertexBuffers() const override { return m_VertexBuffers; }

        [[nodiscard]] const Ref<IndexBuffer> &
        GetIndexBuffer() const override { return m_IndexBuffer; }

        void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        void AddVertexBuffer(const Ref<VertexBuffer> &vb) override;

    private:
        GLuint m_RendererID;
        GLuint m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}