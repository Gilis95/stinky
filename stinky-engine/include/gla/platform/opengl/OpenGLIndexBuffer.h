#pragma once

#include "gla/IndexBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLIndexBuffer : public IndexBuffer {
    private:
        unsigned int m_RendererID;
        const unsigned int m_Count;
    public:
        OpenGLIndexBuffer(const void *data, unsigned int count);

        ~OpenGLIndexBuffer();

        void Bind() const override;

        void Unbind() const override;

        unsigned int GetCount() const override {
            return m_Count;
        }
    };
}