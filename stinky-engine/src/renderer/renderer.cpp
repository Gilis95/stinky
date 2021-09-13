//
// Created by christian on 06/08/2020.
//
#include <Tracy.hpp>
#include "renderer/renderer.h"

#include "ecs/material_component.h"
#include "ecs/mesh_components.h"
#include "ecs/program_component.h"
#include "ecs/transform_component.h"
#include "gla/graphic_layer_abstraction_factory.h"
#include "gla/index_buffer.h"
#include "gla/vertex_buffer.h"
#include "gla/vertex_array.h"
#include "gla/renderer_api.h"
#include "gla/shader.h"
#include "gla/texture.h"
#include "stinkypch.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    renderer::renderer(const graphic_layer_abstraction_factory *rendererFactory)
            : m_RendererFactory(rendererFactory), _M_renderer_api(m_RendererFactory->create_renderer_api()) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    renderer::~renderer() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void renderer::init() const {
        _M_renderer_api->init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void renderer::clear() const {
        _M_renderer_api->clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void renderer::begin_scene(const glm::mat4 &view, const glm::mat4 &projection) {
        m_View = view;
        m_Projection = projection;
        _M_texture_id = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void renderer::end_scene() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void renderer::draw(const RenderCommand &command) {
        ZoneScopedN("RenderDrawCall")
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), command.transform_component.translation);
        glm::mat4 translationRotationX = glm::rotate(translation, command.transform_component.rotation.x,
                                                     glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 translationRotationY = glm::rotate(translationRotationX, command.transform_component.rotation.y,
                                                     glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 translationRotation = glm::rotate(translationRotationY, command.transform_component.rotation.z,
                                                    glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 modelMatrix = glm::scale(translationRotation, command.transform_component.scale);

        if (command.material_component.type == material_type::TEXTURED) {
            command.material_component.material->bind(_M_texture_id);
            //initialize shader program
            command.program_component.program->bind();
            command.program_component.program->set_mat4("u_ViewMatrix", m_View);
            command.program_component.program->set_mat4("u_ProjectionMatrix", m_Projection);
            command.program_component.program->set_mat4("u_ModelMatrix", modelMatrix);
            command.program_component.program->set_integer("u_Texture", _M_texture_id);

            // draw
            command.meshComponent.vertex_array->Bind();
            _M_renderer_api->draw_indexed(command.meshComponent.vertex_array->get_index_buffer()->get_count(),
                                          command.material_component.get_flag(stinky::material_flag::DepthTest));

            // cleanup
            command.meshComponent.vertex_array->Unbind();
            command.material_component.material->unbind(_M_texture_id);

            ++_M_texture_id;
        } else {
            //initialize shader program
            command.program_component.program->bind();
            command.program_component.program->set_mat4("u_ViewMatrix", m_View);
            command.program_component.program->set_mat4("u_ProjectionMatrix", m_Projection);
            command.program_component.program->set_mat4("u_ModelMatrix", modelMatrix);
            command.program_component.program->set_float4("u_Colour", command.material_component.colour);

            // draw
            command.meshComponent.vertex_array->Bind();
            _M_renderer_api->draw_indexed(command.meshComponent.vertex_array->get_index_buffer()->get_count(),
                                          command.material_component.get_flag(stinky::material_flag::DepthTest));

            // cleanup
            command.meshComponent.vertex_array->Unbind();
        }
    }


}