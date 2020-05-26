#pragma once

#include "renderer/IndexBuffer.h"

namespace stinky {
    class OpenGLIndexBuffer : public IndexBuffer {
    private:
        unsigned int m_RendererID;
        const unsigned int m_Count;
    public:
        OpenGLIndexBuffer(const void* data, unsigned int count);

        ~OpenGLIndexBuffer();

        void bind() const override;

        void unbind() const override;

        unsigned int getCount() const override {
            return m_Count;
        }
    };
}