#pragma once

#include "renderer/RendererApi.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLRenderer : public RendererApi
    {
    public:
        OpenGLRenderer() = default;
        ~OpenGLRenderer() = default;

        void Init() const override;

        void Clear() const override;

        void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const override;
    };
}