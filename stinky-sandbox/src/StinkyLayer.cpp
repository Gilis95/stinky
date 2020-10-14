#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "camera/PerspectiveCamera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/TransformationComponents.h"
#include "event/ApplicationEvent.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer(EventController &eventController)
            : Layer("Stinky Layer"),
              m_RendererFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
              m_Camera(CreateScope<PerspectiveCamera>()),
              m_CameraController(CreateScope<PerspectiveCameraController>(m_Camera.get())),
              m_Scene(m_RendererFactory.get())
    {
        auto entity = m_Scene.CreateCameraEntity();
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
        auto entity = m_Scene.CreateCubeEntity();
        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
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
