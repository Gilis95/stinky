#pragma once

#include "renderer/RendererApi.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

#include "stinkypch.h"

namespace stinky {
    class RendererFactory
    {
    public:
        enum class API
        {
            none, OpenGL
        };

        virtual ~RendererFactory() = default;

        static Ref<RendererFactory> create(const API& api = API::OpenGL);

        [[nodiscard]] virtual Ref<RendererApi> createRendererApi() const = 0;
        [[nodiscard]] virtual Ref<IndexBuffer> createIndexBuffer(const void* data, unsigned int count) const = 0;
        [[nodiscard]] virtual Ref<VertexBuffer> createVertexBuffer(unsigned int size, const BufferLayout& layout) const  = 0;
        [[nodiscard]] virtual Ref<VertexBuffer> createVertexBuffer(const void* data, unsigned int size, const BufferLayout& layout) const = 0;
        [[nodiscard]] virtual Ref<VertexArray> createVertexArray() const = 0;
        [[nodiscard]] virtual Ref<Shader> createShader(const std::string& filePath) const = 0;
        [[nodiscard]] virtual Ref<Texture> createTexture(const std::string& path) const = 0;
    };
}
