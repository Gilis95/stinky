#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "camera/PerspectiveCamera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/MaterialComponent.h"
#include "ecs/MeshComponents.h"
#include "ecs/ProgramComponent.h"
#include "ecs/TransformComponent.h"
#include "event/ApplicationEvent.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexArray.h"
#include "gla/VertexBuffer.h"

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
    StinkyLayer::StinkyLayer(GraphicLayerAbstractionFactory *glaFactory, PerspectiveCameraController *cameraController,
                             EventController &eventController, unsigned width, unsigned height)
            : Layer("Stinky Layer"),
              m_GLAFactory(glaFactory),
              m_Camera(CreateScope<PerspectiveCamera>()),
              m_CameraController(cameraController),
              m_Scene(glaFactory) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnAttach() {
        Entity cameraEntity(m_Scene.CreateEntity());
        cameraEntity.AddComponent<CameraComponent>(m_Camera.get(), true);

        m_CameraController->SetCamera(m_Camera.get());

        m_FrameBuffer = m_GLAFactory->CreateFrameBuffer({1280, 720});
        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        //create array buffer, containing shape positions and bind it
        const auto cubeVertexBuffer = m_GLAFactory->CreateVertexBuffer(cubeVertices,
                                                                       CUBE_VERTICES_COUNT *
                                                                       sizeof(float), {
                                                                               {ShaderDataType::Float4, "position"}
                                                                       });
        //Create index buffer, that will define shape vertex positions
        const auto cubeIndexBuffer = m_GLAFactory->CreateIndexBuffer(cubeIndices, CUBE_INDICES_COUNT);

        auto cubeVertexArray = m_GLAFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        cubeVertexArray->AddVertexBuffer(cubeVertexBuffer);
        cubeVertexArray->SetIndexBuffer(cubeIndexBuffer);

        auto entity1 = m_Scene.CreateEntity();
        entity1.AddComponent<MeshComponent>(cubeVertexArray);
        entity1.AddComponent<TransformComponent>(glm::vec3(0.8f, 0.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                 glm::vec3(0.0f));
        entity1.AddComponent<ProgramComponent>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/shaders/basic.shader"));
        entity1.AddComponent<MaterialComponent>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));


        //create array buffer, containing shape positions and bind it
        const auto quadVertexBuffer = m_GLAFactory->CreateVertexBuffer(quadVertices,
                                                                       16 *
                                                                       sizeof(float), {
                                                                               {ShaderDataType::Float4, "position"}
                                                                       });

        //Create index buffer, that will define shape vertex positions
        const auto quadIndexBuffer = m_GLAFactory->CreateIndexBuffer(quadIndices, 6);

        auto quadVertexArray = m_GLAFactory->CreateVertexArray();
        //bind currently bound array buffer to first element of currently bound vertex array
        quadVertexArray->AddVertexBuffer(quadVertexBuffer);
        quadVertexArray->SetIndexBuffer(quadIndexBuffer);

        auto entity = m_Scene.CreateEntity();
        entity.AddComponent<MeshComponent>(quadVertexArray);
        entity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(2.0f, 2.0f, 2.0f),
                                                glm::vec3(0.0f));
        entity.AddComponent<ProgramComponent>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/shaders/skybox.glsl"));
        entity.AddComponent<MaterialComponent>(m_GLAFactory->CreateCubeTexture(
                "/home/christian/workspace/stinky/stinky-sandbox/assets/textures/skybox.png"));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnDetach() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnUpdate(const Timestep &ts) {
        m_FrameBuffer->Unbind();
        m_Scene.OnUpdate();
        m_CameraController->OnUpdate(ts);

        m_FrameBuffer->Bind();
    }
}
