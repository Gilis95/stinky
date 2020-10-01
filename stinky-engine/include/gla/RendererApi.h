#pragma once

#include "VertexArray.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class RendererApi {
    public:
        virtual ~RendererApi() = default;

        virtual void Init() const = 0;

        virtual void Clear() const = 0;

        virtual void
        DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0) const = 0;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
