#include "gla/platform/opengl/OpenGLGraphicLayerFactory.h"

#include "gla/cube_texture.h"
#include "gla/frame_buffer.h"
#include "gla/index_buffer.h"
#include "gla/shader.h"
#include "gla/texture.h"
#include "gla/vertex_buffer.h"
#include "gla/vertex_array.h"

#include "gla/platform/opengl/OpenGLCubeTexture.h"
#include "gla/platform/opengl/OpenGLFrameBuffer.h"
#include "gla/platform/opengl/OpenGLIndexBuffer.h"
#include "gla/platform/opengl/OpenGLRenderer.h"
#include "gla/platform/opengl/OpenGLShader.h"
#include "gla/platform/opengl/OpenGLTexture.h"
#include "gla/platform/opengl/OpenGLVertexBuffer.h"
#include "gla/platform/opengl/OpenGLVertexArray.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    unique_ptr<renderer_api> OpenGLGraphicLayerFactory::create_renderer_api() const {
        return CreateScope<OpenGLRenderer>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<frame_buffer>
    OpenGLGraphicLayerFactory::create_frame_buffer(
            const frame_buffer_specification &frameBufferSpecification) const {
        return CreateRef<OpenGLFrameBuffer>(frameBufferSpecification);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<index_buffer>
    OpenGLGraphicLayerFactory::create_index_buffer(const void *data, unsigned int count) const {
        return CreateRef<OpenGLIndexBuffer>(data, count);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<vertex_buffer>
    OpenGLGraphicLayerFactory::CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<vertex_buffer>
    OpenGLGraphicLayerFactory::CreateVertexBuffer(const void *data, unsigned int size,
                                                  const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, data, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<vertex_array> OpenGLGraphicLayerFactory::CreateVertexArray() const {
        return CreateRef<OpenGLVertexArray>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<shader> OpenGLGraphicLayerFactory::CreateShader(const std::string &filePath) const {
        return CreateRef<OpenGLShader>(filePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<texture> OpenGLGraphicLayerFactory::CreateTexture(const std::string &path) const {
        return CreateRef<OpenGLTexture>(path);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    shared_ptr<texture> OpenGLGraphicLayerFactory::CreateTexture(uint32_t width, uint32_t height) const {
        return CreateRef<OpenGLTexture>(width, height);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    [[nodiscard]] shared_ptr<texture> OpenGLGraphicLayerFactory::CreateCubeTexture(const std::string &path) const {
        return CreateRef<OpenGLCubeTexture>(path);
    }

}