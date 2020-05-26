#pragma once

#include "renderer/RendererApi.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

#include "Macros.h"

namespace stinky {
    class RendererFactory
    {
    public:
        enum class API
        {
            none, OpenGL
        };

        static Ref<RendererFactory> create(API api = API::OpenGL);

        virtual Ref<RendererApi> createRendererApi() = 0;
        virtual Ref<IndexBuffer> createIndexBuffer(const void* data, unsigned int count) = 0;
        virtual Ref<VertexBuffer> createVertexBuffer(const BufferLayout& layout = {}) = 0;
        virtual Ref<VertexArray> createVertexArray() = 0;
        virtual Ref<Shader> createShader(const std::string& filePath) = 0;
        virtual Ref<Texture> createTexture(const std::string& path) = 0;
    };
}
