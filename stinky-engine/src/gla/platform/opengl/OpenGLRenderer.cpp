#include "gla/platform/opengl/OpenGLRenderer.h"

#include <glad/glad.h>
#include <Tracy.hpp>

#include "stinkypch.h"

#include "gla/VertexArray.h"
#include "gla/IndexBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char *message,
            const void *userParam) {
        switch (severity) {
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
            default: STINKY_LOG_ERROR_AND_BREAK("Unknown severity level: {0}", severity);
                return;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLRenderer::Clear() const {
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLRenderer::Init() const {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void
    OpenGLRenderer::DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount) const {
        ZoneScopedN("RenderApiDrawCall")

        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

}
