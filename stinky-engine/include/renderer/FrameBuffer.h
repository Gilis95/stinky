//
// Created by christian on 10/08/2020.
//

#pragma once

#include "stinkypch.h"

namespace stinky {
    struct FrameBufferSpecification {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class FrameBuffer {
    public:
        FrameBuffer(const FrameBufferSpecification &spec) : m_Specification(spec) {
        }

        virtual ~FrameBuffer() = default;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual void WindowResize(uint32_t width, uint32_t height) = 0;

        [[nodiscard]] virtual uint32_t GetColorAttachmentRendererID() const = 0;

        [[nodiscard]] const FrameBufferSpecification &GetSpecification() const {
            return m_Specification;
        }

    protected:
        FrameBufferSpecification m_Specification;
    };
}