//
// Created by christian on 10/08/2020.
//

#pragma once

#include "renderer/FrameBuffer.h"

namespace stinky {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification &spec);

        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        void Bind() override;

        void Unbind() override;

        void Resize(uint32_t width, uint32_t height) override;

        [[nodiscard]] uint32_t
        GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
    };
}