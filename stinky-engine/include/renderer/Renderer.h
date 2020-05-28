//
// Created by christian on 1/19/20.
//
#pragma once

#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include "renderer/RendererApi.h"

namespace stinky {
    class Renderer {
    public:
        Renderer(const Ref<RendererApi>& rendererApi);

        void init() const;

        void clear() const;
        void draw(const Ref<VertexArray>& va, const Ref<Shader>& shader) const;
    private:
        const Ref<RendererApi> m_RendererApi;
    };
}