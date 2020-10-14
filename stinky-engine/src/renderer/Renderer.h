//
// Created by christian on 06/08/2020.
//

#pragma once

#include "stinkypch.h"
#include "StinkyPrerequisites.h"

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class MeshVertexComponent;
    class MeshIndexComponent;
    class TranslateComponent;
    class ScaleComponent;
    class RendererApi;

    class GraphicLayerAbstractionFactory;

    struct RenderCommand {
        const MeshVertexComponent& verticesComponent;
        const MeshIndexComponent& indicesComponent;
        const TranslateComponent& translateComponent;
        const ScaleComponent& scaleComponent;
    };

    class Renderer {
    public:
        Renderer(const GraphicLayerAbstractionFactory* rendererFactory);
        virtual ~Renderer();

        void Init() const;
        void Clear() const;
        void BeginScene(const glm::mat4& viewProjection);
        void Draw(const RenderCommand& command) const;
        void EndScene();
    protected:
        const GraphicLayerAbstractionFactory* m_RendererFactory;
        Scope<RendererApi> m_RendererApi;
        glm::mat4 m_ViewProjection;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
