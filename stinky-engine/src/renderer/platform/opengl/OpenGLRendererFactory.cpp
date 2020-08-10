#include "renderer/platform/opengl/OpenGLRendererFactory.h"
#include "renderer/platform/opengl/OpenGLRenderer.h"
#include "renderer/platform/opengl/OpenGLIndexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexArray.h"
#include "renderer/platform/opengl/OpenGLShader.h"
#include "renderer/platform/opengl/OpenGLTexture.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<RendererApi> OpenGLRendererFactory::createRendererApi() const
    {
        return CreateRef<OpenGLRenderer>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<IndexBuffer> OpenGLRendererFactory::createIndexBuffer(const void* data, unsigned int count) const
    {
        return CreateRef<OpenGLIndexBuffer>(data, count);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer> OpenGLRendererFactory::createVertexBuffer(unsigned int size, const BufferLayout& layout) const
    {
        return CreateRef<OpenGLVertexBuffer>(layout, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexBuffer> OpenGLRendererFactory::createVertexBuffer(const void* data, unsigned int size, const BufferLayout& layout) const
    {
        return CreateRef<OpenGLVertexBuffer>(layout, data, size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<VertexArray> OpenGLRendererFactory::createVertexArray() const
    {
        return CreateRef<OpenGLVertexArray>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Shader> OpenGLRendererFactory::createShader(const std::string& filePath) const
    {
        return CreateRef<OpenGLShader>(filePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLRendererFactory::createTexture(const std::string& filePath) const
    {
        return CreateRef<OpenGLTexture>(filePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<Texture> OpenGLRendererFactory::createTexture(uint32_t width, uint32_t height) const
    {
        return CreateRef<OpenGLTexture>(width, height);
    }
}