#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "event/ApplicationEvent.h"
#include "renderer/Renderer2D.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer(EventController &eventController)
            : Layer("Stinky Layer"),
              m_RendererFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL))
            , m_Renderer(m_RendererFactory)
            , m_PerspectiveCamera(-1.68f, 1.68f, 45.0f, 1.0f)
            , m_PerspectiveCameraController(&m_PerspectiveCamera) {


        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonPressed, std::bind(
                        &PerspectiveCameraController::OnMousePressed,
                        &m_PerspectiveCameraController, std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseMoved, std::bind(
                        &PerspectiveCameraController::OnMouseMoved,
                        &m_PerspectiveCameraController, std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonReleased, std::bind(
                        &PerspectiveCameraController::OnMouseReleased,
                        &m_PerspectiveCameraController, std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::KeyPressed, std::bind(
                        &PerspectiveCameraController::OnKeyboardEvent,
                        &m_PerspectiveCameraController, std::placeholders::_1)
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnAttach() {
        m_FrameBuffer = m_RendererFactory->CreateFrameBuffer({1280, 720});
        m_SceneNodes.push_back(
                m_Renderer.DrawCube(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.5f, 0.5f, 0.5f), {1.0f, 0.0f, 0.0f, 1.0f}));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnDetach() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnUpdate(const Timestep &ts) {
        m_FrameBuffer->Unbind();
        m_Renderer.Clear();

        m_PerspectiveCameraController.OnUpdate(ts);
        m_Renderer.BeginScene(m_PerspectiveCamera.GetViewProjectionMatrix());

        std::for_each(m_SceneNodes.begin(), m_SceneNodes.end(),
                      [&](const Renderer::SceneNode &sceneNode) -> void {
                          m_Renderer.Draw(sceneNode);
                      });
        m_FrameBuffer->Bind();

        m_Renderer.EndScene();
    }
}
