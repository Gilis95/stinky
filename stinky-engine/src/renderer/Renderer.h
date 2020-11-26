//
// Created by christian on 06/08/2020.
//

#pragma once

#include <glm/glm.hpp>

#include "core/StinkyMemory.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    struct RenderCommand {
        const MeshComponent &meshComponent;
        const TransformComponent &transformComponent;
        const ProgramComponent &programComponent;
        const MaterialComponent &materialComponent;
    };

    class Renderer {
    public:
        explicit Renderer(const GraphicLayerAbstractionFactory *rendererFactory);
        virtual ~Renderer();

        void Init() const;
        void Clear() const;
        void BeginScene(const glm::mat4 &view, const glm::mat4 &projection);
        void Draw(const RenderCommand &command);
        void EndScene();
    protected:
        const GraphicLayerAbstractionFactory *m_RendererFactory;
        Scope<RendererApi> m_RendererApi;
        glm::mat4 m_View{};
        glm::mat4 m_Projection{};
        int m_TextureId = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
