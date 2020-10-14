#include "gla/platform/opengl/OpenGLGraphicLayerFactory.h"

#include "gla/FrameBuffer.h"
#include "gla/IndexBuffer.h"
#include "gla/Shader.h"
#include "gla/Texture.h"
#include "gla/VertexBuffer.h"
#include "gla/VertexArray.h"

#include "gla/platform/opengl/OpenGLFrameBuffer.h"
#include "gla/platform/opengl/OpenGLIndexBuffer.h"
#include "gla/platform/opengl/OpenGLRenderer.h"
#include "gla/platform/opengl/OpenGLShader.h"
#include "gla/platform/opengl/OpenGLTexture.h"
#include "gla/platform/opengl/OpenGLVertexBuffer.h"
#include "gla/platform/opengl/OpenGLVertexArray.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Scope<RendererApi> OpenGLGraphicLayerFactory::CreateRendererApi() const {
        return CreateScope<OpenGLRenderer>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<FrameBuffer>
    OpenGLGraphicLayerFactory::CreateFrameBuffer(
            const FrameBufferSpecification &frameBufferSpecification) const {
        return CreateRef<OpenGLFrameBuffer>(frameBufferSpecification);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<IndexBuffer>
    OpenGLGraphicLayerFactory::CreateIndexBuffer(const void *data, unsigned int count) const {
        return CreateRef<OpenGLIndexBuffer>(data, count);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer>
    OpenGLGraphicLayerFactory::CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer>
    OpenGLGraphicLayerFactory::CreateVertexBuffer(const void *data, unsigned int size,
                                                  const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, data, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexArray> OpenGLGraphicLayerFactory::CreateVertexArray() const {
        return CreateRef<OpenGLVertexArray>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Shader> OpenGLGraphicLayerFactory::CreateShader(const std::string &filePath) const {
        return CreateRef<OpenGLShader>(filePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLGraphicLayerFactory::CreateTexture(const std::string &path) const {
        return CreateRef<OpenGLTexture>(path);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLGraphicLayerFactory::CreateTexture(uint32_t width, uint32_t height) const {
        return CreateRef<OpenGLTexture>(width, height);
    }
}