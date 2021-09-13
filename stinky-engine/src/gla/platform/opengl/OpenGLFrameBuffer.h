//
// Created by christian on 10/08/2020.
//

#pragma once

#include "gla/frame_buffer.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLFrameBuffer : public frame_buffer {
    public:
        OpenGLFrameBuffer(const frame_buffer_specification &spec);

        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        void bind() override;

        void unbind() override;

        void window_resize(uint32_t width, uint32_t height) override;

        [[nodiscard]] uint32_t
        get_color_attachment_renderer_id() const override { return m_ColorAttachment; }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////