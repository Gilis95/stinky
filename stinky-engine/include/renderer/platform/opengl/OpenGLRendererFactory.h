#pragma once

#include <renderer/FrameBuffer.h>
#include "renderer/RendererFactory.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLRendererFactory : public RendererFactory {
    public:
        OpenGLRendererFactory() = default;

        ~OpenGLRendererFactory() = default;

        [[nodiscard]] Ref<FrameBuffer>
        CreateFrameBuffer(const FrameBufferSpecification &frameBufferSpecification) const override;

        [[nodiscard]] Ref<IndexBuffer>
        CreateIndexBuffer(const void *data, unsigned int count) const override;

        [[nodiscard]] Ref<RendererApi> CreateRendererApi() const override;

        [[nodiscard]] Ref<Shader> CreateShader(const std::string &filePath) const override;

        [[nodiscard]] Ref<Texture> CreateTexture(const std::string &path) const override;

        [[nodiscard]] Ref<Texture> CreateTexture(uint32_t width, uint32_t height) const override;

        [[nodiscard]] Ref<VertexBuffer>
        CreateVertexBuffer(unsigned int size, const BufferLayout &layout = {}) const override;

        [[nodiscard]] Ref<VertexBuffer>
        CreateVertexBuffer(const void *data, unsigned int size,
                           const BufferLayout &layout = {}) const override;

        [[nodiscard]] Ref<VertexArray> CreateVertexArray() const override;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
