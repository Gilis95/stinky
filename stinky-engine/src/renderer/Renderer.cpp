//
// Created by christian on 1/19/20.
//
#include "stinkypch.h"
#include "renderer/Renderer.h"

namespace stinky
{

    /////////////////////////////////////////////////////////////////////////////////////////
    Renderer::Renderer(const Ref<RendererApi>& rendererApi) : m_RendererApi(std::move(rendererApi))
    {
        init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::init() const
    {
        m_RendererApi->Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::clear() const
    {
        m_RendererApi->Clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Renderer::draw(const Ref<VertexArray>& va, const Ref<Shader>& shader) const
    {
        shader->Bind();
        va->Bind();

        m_RendererApi->DrawIndexed(va);
    }

}