#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "camera/track_ball_camera.h"
#include "core/Time.h"
#include "ecs/camera_component.h"
#include "ecs/entity.h"
#include "ecs/material_component.h"
#include "ecs/mesh_components.h"
#include "ecs/program_component.h"
#include "ecs/transform_component.h"
#include "event/windows_event.h"
#include "gla/frame_buffer.h"
#include "gla/graphic_layer_abstraction_factory.h"
#include "gla/vertex_array.h"
#include "gla/vertex_buffer.h"

namespace stinky {
    namespace {
        constexpr unsigned CUBE_VERTICES_COUNT = 32;
        glm::vec4 cubeVertices[8] = {
                //Front Quad
                {-1.0f, -1.0f, -1.0, 1.0f}, //0
                {1.0f,  -1.0f, -1.0, 1.0f}, //1
                {1.0f,  1.0f,  -1.0, 1.0f}, //2
                {-1.0f, 1.0f,  -1.0, 1.0f}, //3

                // Back Quad
                {1.0f,  -1.0f, 1.0,  1.0f}, //4
                {-1.0f, -1.0f, 1.0,  1.0f}, //5
                {-1.0f, 1.0f,  1.0,  1.0f}, //6
                {1.0f,  1.0f,  1.0,  1.0f} //7
        };

        constexpr unsigned int CUBE_INDICES_COUNT = 36;

        uint32_t cubeIndices[CUBE_INDICES_COUNT] = {
                // front side
                0, 1, 3, 1, 2, 3,

                // right side
                1, 4, 2, 4, 6, 2,

                // back side
                4, 5, 7, 5, 6, 7,

                // left side
                0, 5, 3, 5, 6, 3,

                // down side
                3, 2, 6, 2, 7, 6,

                // upper side
                0, 1, 2, 2, 3, 0
        };

        glm::vec4 quadVertices[4] = {
                {-1.0f, -1.0f, 1.0, 1.0f}, //0
                {1.0f,  -1.0f, 1.0, 1.0f}, //1
                {1.0f,  1.0f,  1.0, 1.0f}, //2
                {-1.0f, 1.0f,  1.0, 1.0f}, //3
        };

        uint32_t quadIndices[6] = {
                // front side
                0, 1, 3, 1, 2, 3
        };
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer(graphic_layer_abstraction_factory *glaFactory, track_ball_camera *camera,
                             event_controller &eventController, unsigned width, unsigned height)
            : layer("Stinky Layer"),
              m_GLAFactory(glaFactory),
              m_Camera(camera),
              m_Scene(glaFactory) {
        eventController.register_event_handler<window_resize_event>(
                [this](const window_resize_event &resizeEvent) -> void {
                    m_FrameBuffer->window_resize(resizeEvent.width, resizeEvent.height);
                });
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::on_attach() {
        entity cameraEntity(m_Scene.CreateEntity());
        cameraEntity.AddComponent<camera_component>(m_Camera, true);


        m_FrameBuffer = m_GLAFactory->create_frame_buffer({1280, 720});
        m_Camera->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
        //create array buffer, containing shape positions and bind it
        const auto cubeVertexBuffer = m_GLAFactory->CreateVertexBuffer(cubeVertices,
                                                                       CUBE_VERTICES_COUNT *
                                                                       sizeof(float), {
                                                                               {ShaderDataType::Float4, "position"}
                                                                       });
        //Create index buffer, that will define shape vertex positions
        const auto cubeIndexBuffer = m_GLAFactory->create_index_buffer(cubeIndices, CUBE_INDICES_COUNT);

        auto cubeVertexArray = m_GLAFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        cubeVertexArray->add_vertex_buffer(cubeVertexBuffer);
        cubeVertexArray->set_index_buffer(cubeIndexBuffer);

        auto entity1 = m_Scene.CreateEntity();
        entity1.AddComponent<mesh_component>(cubeVertexArray);
        entity1.AddComponent<transform_component>(glm::vec3(0.8f, 0.0f, -10.0f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                  glm::vec3(0.0f));
        entity1.AddComponent<program_component>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/shaders/basic.shader"));
        entity1.AddComponent<material_component>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));


        //create array buffer, containing shape positions and bind it
        const auto quadVertexBuffer = m_GLAFactory->CreateVertexBuffer(quadVertices,
                                                                       16 *
                                                                       sizeof(float), {
                                                                               {ShaderDataType::Float4, "position"}
                                                                       });

        //Create index buffer, that will define shape vertex positions
        const auto quadIndexBuffer = m_GLAFactory->create_index_buffer(quadIndices, 6);

        auto quadVertexArray = m_GLAFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        quadVertexArray->add_vertex_buffer(quadVertexBuffer);
        quadVertexArray->set_index_buffer(quadIndexBuffer);

        auto entity = m_Scene.CreateEntity();
        entity.AddComponent<mesh_component>(quadVertexArray);
        entity.AddComponent<transform_component>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(2.0f, 2.0f, 2.0f),
                                                 glm::vec3(0.0f));
        entity.AddComponent<program_component>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/shaders/skybox.glsl"));
        entity.AddComponent<material_component>(m_GLAFactory->CreateCubeTexture(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/textures/skybox.png"), false);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::on_detach() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::on_update(const time_frame &ts) {
        m_FrameBuffer->unbind();

        m_Camera->on_update(ts);
        m_Scene.on_update();

        m_FrameBuffer->bind();
    }
}
