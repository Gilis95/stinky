#include <glad/glad.h>
#include "renderer/platform/opengl/OpenGLRenderer.h"

#include "Logger.h"

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
        case GL_DEBUG_SEVERITY_HIGH:         CRITICAL(message); return;
        case GL_DEBUG_SEVERITY_MEDIUM:       ERROR(message); return;
        case GL_DEBUG_SEVERITY_LOW:          WARN(message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: TRACE(message); return;
        }

        ASSERT(false, "Unknown severity level!");
    }

    void OpenGLRenderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void OpenGLRenderer::init() const
    {
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

}
