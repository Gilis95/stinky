#pragma once

#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class GraphicLayerAbstractionFactory {
    public:
        enum class API {
            none, OpenGL
        };

        virtual ~GraphicLayerAbstractionFactory() = default;

        static Scope<GraphicLayerAbstractionFactory> create(const API &api = API::OpenGL);

        [[nodiscard]] virtual Scope<RendererApi> CreateRendererApi() const = 0;

        [[nodiscard]] virtual Ref<FrameBuffer>
        CreateFrameBuffer(const FrameBufferSpecification &frameBufferSpecification) const = 0;

        [[nodiscard]] virtual Ref<IndexBuffer>
        CreateIndexBuffer(const void *data, unsigned int count) const = 0;

        [[nodiscard]] virtual Ref<Shader> CreateShader(const std::string &filePath) const = 0;

        [[nodiscard]] virtual Ref<Texture> CreateTexture(const std::string &path) const = 0;

        [[nodiscard]] virtual Ref<Texture> CreateTexture(uint32_t width, uint32_t height) const = 0;

        [[nodiscard]] virtual Ref<Texture> CreateCubeTexture(const std::string &path) const = 0;

        [[nodiscard]] virtual Ref<VertexBuffer>
        CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const = 0;

        [[nodiscard]] virtual Ref<VertexBuffer>
        CreateVertexBuffer(const void *data, unsigned int size,
                           const BufferLayout &layout) const = 0;

        [[nodiscard]] virtual Ref<VertexArray> CreateVertexArray() const = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
