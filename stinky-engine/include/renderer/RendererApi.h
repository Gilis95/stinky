#pragma once
#include "renderer/VertexArray.h"

namespace stinky
{
    class RendererApi
    {
    public:
        virtual ~RendererApi() = default;

        virtual void init() const = 0;

        virtual void clear() const = 0;


        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const = 0;
    };

}
