#pragma once

#include "event/Layer.h"
#include "renderer/Renderer.h"
#include "renderer/RendererFactory.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public Layer
    {
    public:
        StinkyLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;

    private:
        Ref<RendererFactory> m_RendererFactory;

        Renderer m_Renderer;
        Ref<VertexArray> m_VertexArray;
        Ref<Shader> m_Shader;
        Ref<Texture> m_Texture;
    };

}
