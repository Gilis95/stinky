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
    class RendererApi;
    class GraphicLayerAbstractionFactory;

    struct RenderCommand {
        const MeshComponent &meshComponent;
        const TranslateComponent &translateComponent;
        const ScaleComponent &scaleComponent;
        const ProgramComponent &programComponent;
        const MaterialComponent &materialComponent;
    };

    class Renderer {
    public:
        explicit Renderer(const GraphicLayerAbstractionFactory *rendererFactory);
        virtual ~Renderer();

        void Init() const;
        void Clear() const;
        void BeginScene(const glm::mat4 &viewProjection);
        void Draw(const RenderCommand &command);
        void EndScene();
    protected:
        const GraphicLayerAbstractionFactory *m_RendererFactory;
        Scope<RendererApi> m_RendererApi;
        glm::mat4 m_ViewProjection{};
        int m_TextureId = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
