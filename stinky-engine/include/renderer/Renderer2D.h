//
// Created by christian on 1/19/20.
//
#pragma once

#include "renderer/Renderer.h"
#include "gla/RendererApi.h"
#include "gla/GraphicLayerAbstractionFactory.h"

#include <glm/glm.hpp>

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Renderer2D : public Renderer {
    public:
        Renderer2D(const Ref<GraphicLayerAbstractionFactory> &rendererFactory);

        void Init() const;

        void Clear() const;

        SceneNode
        CreateQuad(const glm::vec2 &translate, const glm::vec2 &scale, const glm::vec4 &color);

    private:
        Ref<GraphicLayerAbstractionFactory> m_RendererFactory;
    };
}