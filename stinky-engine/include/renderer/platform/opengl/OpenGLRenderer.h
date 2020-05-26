#pragma once

#include "renderer/RendererApi.h"

namespace stinky
{
    class OpenGLRenderer : public RendererApi
    {
    public:
        OpenGLRenderer() = default;
        ~OpenGLRenderer() = default;

        void init() const override;

        void clear() const override;

        void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const override;
    };

}