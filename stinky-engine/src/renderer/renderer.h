//
// Created by christian on 06/08/2020.
//

#pragma once

#include <glm/glm.hpp>

#include "core/stinky_memory.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    struct RenderCommand {
        const mesh_component &meshComponent;
        const transform_component &transform_component;
        const program_component &program_component;
        const material_component &material_component;
    };

    class renderer {
    public:
        explicit renderer(const graphic_layer_abstraction_factory *rendererFactory);
        virtual ~renderer();

        void init() const;
        void clear() const;
        void begin_scene(const glm::mat4 &view, const glm::mat4 &projection);
        void draw(const RenderCommand &command);
        void end_scene();
    protected:
        const graphic_layer_abstraction_factory *m_RendererFactory;
        unique_ptr<renderer_api> _M_renderer_api;
        glm::mat4 m_View{};
        glm::mat4 m_Projection{};
        int _M_texture_id = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
