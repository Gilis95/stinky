#pragma once

#include "stinkypch.h"

#include "renderer/IndexBuffer.h"
#include "renderer/RendererApi.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "FrameBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class RendererFactory {
    public:
        enum class API {
            none, OpenGL
        };

        virtual ~RendererFactory() = default;

        static Ref<RendererFactory> create(const API &api = API::OpenGL);

        [[nodiscard]] virtual Ref<FrameBuffer>
        CreateFrameBuffer(const FrameBufferSpecification &frameBufferSpecification) const = 0;

        [[nodiscard]] virtual Ref<IndexBuffer>
        CreateIndexBuffer(const void *data, unsigned int count) const = 0;

        [[nodiscard]] virtual Ref<RendererApi> CreateRendererApi() const = 0;

        [[nodiscard]] virtual Ref<Shader> CreateShader(const std::string &filePath) const = 0;

        [[nodiscard]] virtual Ref<Texture> CreateTexture(const std::string &path) const = 0;

        [[nodiscard]] virtual Ref<Texture> CreateTexture(uint32_t width, uint32_t height) const = 0;

        [[nodiscard]] virtual Ref<VertexBuffer>
        CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const = 0;

        [[nodiscard]] virtual Ref<VertexBuffer>
        CreateVertexBuffer(const void *data, unsigned int size,
                           const BufferLayout &layout) const = 0;

        [[nodiscard]] virtual Ref<VertexArray> CreateVertexArray() const = 0;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
