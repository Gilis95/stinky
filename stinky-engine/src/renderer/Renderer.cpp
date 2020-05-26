//
// Created by christian on 1/19/20.
//
#include <iostream>

#include "Logger.h"
#include "renderer/Renderer.h"

namespace stinky {
    Renderer::Renderer(const Ref<RendererApi>& rendererApi) : m_RendererApi(rendererApi) {}


    void Renderer::init() const
    {
        m_RendererApi->init();
    }


    void Renderer::clear() const {
        m_RendererApi->clear();
    }

    void Renderer::draw(const Ref <VertexArray>& va, const Ref<IndexBuffer>& ib, const Ref <Shader>& shader) const {
        shader->bind();
        va->bind();
        ib->bind();

        m_RendererApi->drawIndexed(va, ib->getCount());
    }
}