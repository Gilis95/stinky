#include "renderer/platform/opengl/OpenGLRendererFactory.h"
#include "renderer/platform/opengl/OpenGLRenderer.h"
#include "renderer/platform/opengl/OpenGLIndexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexArray.h"
#include "renderer/platform/opengl/OpenGLShader.h"
#include "renderer/platform/opengl/OpenGLTexture.h"

namespace stinky {
    Ref<RendererApi> OpenGLRendererFactory::createRendererApi() const {
        return createRef<OpenGLRenderer>();
    }

    Ref<IndexBuffer> OpenGLRendererFactory::createIndexBuffer(const void* data, unsigned int count) const {
        return createRef<OpenGLIndexBuffer>(data, count);
    }

    Ref<VertexBuffer> OpenGLRendererFactory::createVertexBuffer(unsigned int size, const BufferLayout& layout) const {
        return createRef<OpenGLVertexBuffer>(layout, size);
    }

    Ref<VertexBuffer> OpenGLRendererFactory::createVertexBuffer(const void* data, unsigned int size, const BufferLayout& layout) const {
        return createRef<OpenGLVertexBuffer>(layout, data, size);
    }

    Ref<VertexArray> OpenGLRendererFactory::createVertexArray() const {
        return createRef<OpenGLVertexArray>();
    }

    Ref<Shader> OpenGLRendererFactory::createShader(const std::string& filePath) const {
        return createRef<OpenGLShader>(filePath);
    }

    Ref<Texture> OpenGLRendererFactory::createTexture(const std::string& filePath) const {
        return createRef<OpenGLTexture>(filePath);
    }
}