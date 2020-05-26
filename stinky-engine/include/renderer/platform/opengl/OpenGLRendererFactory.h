#pragma once

#include "renderer/RendererFactory.h"

namespace stinky {
    class OpenGLRendererFactory :public RendererFactory
    {
    public:
        OpenGLRendererFactory() = default;
        ~OpenGLRendererFactory() = default;

        Ref<RendererApi> createRendererApi();
        Ref<IndexBuffer> createIndexBuffer(const void* data, unsigned int count);
        Ref<VertexBuffer> createVertexBuffer(const BufferLayout& layout = {});
        Ref<VertexArray> createVertexArray();
        Ref<Shader> createShader(const std::string& filePath);
        Ref<Texture> createTexture(const std::string& path);
    };
}
