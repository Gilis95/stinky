#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "camera/PerspectiveCamera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/MeshComponents.h"
#include "ecs/TransformationComponents.h"
#include "event/ApplicationEvent.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"

namespace stinky {
    namespace {
        constexpr unsigned VERTICES_COUNT = 32;
        glm::vec4 vertices[8] = {
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

        constexpr unsigned int INDICES_COUNT = 36;

        unsigned indices[INDICES_COUNT] = {
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
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer(EventController &eventController)
            : Layer("Stinky Layer"),
              m_RendererFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
              m_Camera(CreateScope<PerspectiveCamera>()),
              m_CameraController(CreateScope<PerspectiveCameraController>(m_Camera.get())),
              m_Scene(m_RendererFactory.get()) {
        Entity entity(m_Scene.CreateEntity());
        entity.AddComponent<CameraComponent>(m_Camera.get(), true);

        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonPressed, std::bind(
                        &PerspectiveCameraController::OnMousePressed,
                        m_CameraController.get(), std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseMoved, std::bind(
                        &PerspectiveCameraController::OnMouseMoved,
                        m_CameraController.get(), std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonReleased, std::bind(
                        &PerspectiveCameraController::OnMouseReleased,
                        m_CameraController.get(), std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::KeyPressed, std::bind(
                        &PerspectiveCameraController::OnKeyboardEvent,
                        m_CameraController.get(), std::placeholders::_1)
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnAttach() {
        m_FrameBuffer = m_RendererFactory->CreateFrameBuffer({1280, 720});
        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        auto entity = m_Scene.CreateEntity();
        entity.AddComponent<MeshComponent>(VERTICES_COUNT, vertices, INDICES_COUNT, indices);
        entity.AddComponent<TranslateComponent>(glm::vec3(0.0f, 0.0f, -2.0f));
        entity.AddComponent<ScaleComponent>(glm::vec3(0.5f, 0.5f, 0.5f));
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
