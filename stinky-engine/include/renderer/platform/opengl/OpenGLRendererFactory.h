#pragma once

#include "renderer/RendererFactory.h"

namespace stinky {
    class OpenGLRendererFactory :public RendererFactory
    {
    public:
        OpenGLRendererFactory() = default;
        ~OpenGLRendererFactory() = default;

        [[nodiscard]] Ref<RendererApi> createRendererApi() const override;
        [[nodiscard]] Ref<IndexBuffer> createIndexBuffer(const void* data, unsigned int count) const override;
        [[nodiscard]] Ref<VertexBuffer> createVertexBuffer(unsigned int size, const BufferLayout& layout = {}) const override;
        [[nodiscard]] Ref<VertexBuffer> createVertexBuffer(const void* data, unsigned int size, const BufferLayout& layout = {}) const override;
        [[nodiscard]] Ref<VertexArray> createVertexArray() const override;
        [[nodiscard]] Ref<Shader> createShader(const std::string& filePath) const override;
        [[nodiscard]] Ref<Texture> createTexture(const std::string& path) const override;
    };
}
