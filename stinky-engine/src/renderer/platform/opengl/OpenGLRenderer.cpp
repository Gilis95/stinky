#include <glad/glad.h>
#include "renderer/platform/opengl/OpenGLRenderer.h"

namespace stinky {

    void OpenGLMessageCallback(
        unsigned source,
        unsigned type,
        unsigned id,
        unsigned severity,
        int length,
        const char* message,
        const void* userParam)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            STINKY_CRITICAL(message);
            return;
        case GL_DEBUG_SEVERITY_MEDIUM:
            STINKY_ERROR(message);
            return;
        case GL_DEBUG_SEVERITY_LOW:
            STINKY_WARN(message);
            return;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            STINKY_TRACE(message);
            return;
        default:
            ASSERT(false, "Unknown severity level!");
            return;
        }

    }

    void OpenGLRenderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void OpenGLRenderer::init() const
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const
    {
        uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
