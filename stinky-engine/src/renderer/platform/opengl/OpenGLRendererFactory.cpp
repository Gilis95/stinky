#include "renderer/platform/opengl/OpenGLRendererFactory.h"
#include "renderer/platform/opengl/OpenGLRenderer.h"
#include "renderer/platform/opengl/OpenGLIndexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexBuffer.h"
#include "renderer/platform/opengl/OpenGLVertexArray.h"
#include "renderer/platform/opengl/OpenGLVertexArray.h"
#include "renderer/platform/opengl/OpenGLShader.h"
#include "renderer/platform/opengl/OpenGLTexture.h"

namespace stinky {
    Ref<RendererApi> OpenGLRendererFactory::createRendererApi() {
        return createRef<OpenGLRenderer>();
    }

    Ref<IndexBuffer> OpenGLRendererFactory::createIndexBuffer(const void* data, unsigned int count) {
        return createRef<OpenGLIndexBuffer>(data, count);
    }

    Ref<VertexBuffer> OpenGLRendererFactory::createVertexBuffer(const BufferLayout& layout) {
        return createRef<VertexBuffer>(layout);
    }

    Ref<VertexArray> OpenGLRendererFactory::createVertexArray() {
        return createRef<VertexArray>();
    }

    Ref<Shader> OpenGLRendererFactory::createShader(const std::string& filePath) {
        return createRef<Shader>(filePath);
    }

    Ref<Texture> OpenGLRendererFactory::createTexture(const std::string& filePath) {
        return createRef<Texture>(filePath);
    }
}