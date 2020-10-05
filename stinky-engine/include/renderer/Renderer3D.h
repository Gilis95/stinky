//
// Created by christian on 04/08/2020.
//
#pragma once

#include "stinkypch.h"
#include "renderer/Renderer.h"
#include "gla/GraphicLayerAbstractionFactory.h"

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Renderer3D : public Renderer {
    public:
        Renderer3D(const Ref<GraphicLayerAbstractionFactory> &rendererFactory);

        void
        Init() const;

        void Clear() const;

        [[nodiscard]] SceneNode
        DrawCube(const glm::vec3 &translate, const glm::vec3 &scale, const glm::vec4 &color) const;

    private:
        const Ref<GraphicLayerAbstractionFactory> m_RendererFactory;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////