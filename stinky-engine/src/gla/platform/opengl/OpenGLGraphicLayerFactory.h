#pragma once

#include "gla/graphic_layer_abstraction_factory.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLGraphicLayerFactory : public graphic_layer_abstraction_factory {
    public:
        OpenGLGraphicLayerFactory() = default;

        ~OpenGLGraphicLayerFactory() override = default;

        [[nodiscard]] unique_ptr<renderer_api> create_renderer_api() const override;

        [[nodiscard]] shared_ptr<frame_buffer>
        create_frame_buffer(const frame_buffer_specification &frameBufferSpecification) const override;

        [[nodiscard]] shared_ptr<index_buffer>
        create_index_buffer(const void *data, unsigned int count) const override;

        [[nodiscard]] shared_ptr<shader> CreateShader(const std::string &filePath) const override;

        [[nodiscard]] shared_ptr<texture> CreateTexture(const std::string &path) const override;

        [[nodiscard]] shared_ptr<texture> CreateTexture(uint32_t width, uint32_t height) const override;

        [[nodiscard]] shared_ptr<texture> CreateCubeTexture(const std::string &path) const;

        [[nodiscard]] shared_ptr<vertex_buffer>
        CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const override;

        [[nodiscard]] shared_ptr<vertex_buffer>
        CreateVertexBuffer(const void *data, unsigned int size,
                           const BufferLayout &layout) const override;

        [[nodiscard]] shared_ptr<vertex_array> CreateVertexArray() const override;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////