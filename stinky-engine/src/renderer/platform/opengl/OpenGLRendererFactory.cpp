#include "renderer/platform/opengl/OpenGLRenderer.h"

#include "renderer/platform/opengl/OpenGLFrameBuffer.h"
#include "renderer/platform/opengl/OpenGLIndexBuffer.h"
#include "renderer/platform/opengl/OpenGLRendererFactory.h"
#include "renderer/platform/opengl/OpenGLShader.h"
#include "renderer/platform/opengl/OpenGLTexture.h"
#include "renderer/platform/opengl/OpenGLVertexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexArray.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<RendererApi> OpenGLRendererFactory::CreateRendererApi() const {
        return CreateRef<OpenGLRenderer>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<FrameBuffer>
    OpenGLRendererFactory::CreateFrameBuffer(const FrameBufferSpecification &frameBufferSpecification) const {
        return CreateRef<OpenGLFrameBuffer>(frameBufferSpecification);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<IndexBuffer> OpenGLRendererFactory::CreateIndexBuffer(const void *data, unsigned int count) const {
        return CreateRef<OpenGLIndexBuffer>(data, count);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer> OpenGLRendererFactory::CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer>
    OpenGLRendererFactory::CreateVertexBuffer(const void *data, unsigned int size, const BufferLayout &layout) const {
        return CreateRef<OpenGLVertexBuffer>(layout, data, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexArray> OpenGLRendererFactory::CreateVertexArray() const {
        return CreateRef<OpenGLVertexArray>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Shader> OpenGLRendererFactory::CreateShader(const std::string &filePath) const {
        return CreateRef<OpenGLShader>(filePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLRendererFactory::CreateTexture(const std::string &path) const {
        return CreateRef<OpenGLTexture>(path);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLRendererFactory::CreateTexture(uint32_t width, uint32_t height) const {
        return CreateRef<OpenGLTexture>(width, height);
    }
}