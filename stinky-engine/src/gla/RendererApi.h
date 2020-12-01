#pragma once

#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class RendererApi {
    public:
        virtual ~RendererApi() = default;

        virtual void Init() const = 0;

        virtual void Clear() const = 0;

        virtual void DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount = 0) const = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////