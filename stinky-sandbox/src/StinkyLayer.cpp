#include <glm/ext.hpp>
#include "StinkyLayer.h"

#include "event/ApplicationEvent.h"
#include "renderer/Renderer2D.h"
#include "renderer/RendererFactory.h"
#include "renderer/VertexBuffer.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyLayer::StinkyLayer(EventController &eventController)
            : Layer("Stinky Layer"),
              m_RendererFactory(RendererFactory::create(RendererFactory::API::OpenGL)),
              m_Renderer(m_RendererFactory), m_OrthographicCamera(-1.68f, 1.68f, -1.0f, 1.0f),
              m_OrthographicCameraController(m_OrthographicCamera, 1.68f) {

        eventController.RegisterEventHandler(
                {
                        EventType::KeyPressed, std::bind(
                        &OrthographicCameraController::OnKeyboardEvent,
                        &m_OrthographicCameraController, std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseScrolled, std::bind(
                        &OrthographicCameraController::OnZoom,
                        &m_OrthographicCameraController, std::placeholders::_1)
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::WindowResize, [&](const Event &event) {
                    auto resizeEvent = dynamic_cast<const WindowResizeEvent &>(event);

                    m_OrthographicCameraController.WindowResize(
                            static_cast<float>(resizeEvent.m_Width), static_cast<float>(resizeEvent
                                    .m_Height));
                    m_FrameBuffer->WindowResize(resizeEvent.m_Width, resizeEvent
                            .m_Height);
                }
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnAttach() {
        m_FrameBuffer = m_RendererFactory->CreateFrameBuffer({1280, 720});
        m_SceneNodes.push_back(
                m_Renderer.CreateQuad({-0.5f, 0.5f}, {0.1f, 0.1f}, {1.0f, 0.0f, 0.0f, 1.0f}));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnDetach() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void StinkyLayer::OnUpdate(const Timestep &ts) {
        m_FrameBuffer->Unbind();
        m_Renderer.Clear();

        m_OrthographicCameraController.OnUpdate(ts);
        m_Renderer.BeginScene(m_OrthographicCamera.GetViewProjectionMatrix());

        std::for_each(m_SceneNodes.begin(), m_SceneNodes.end(),
                      [&](const Renderer::SceneNode &sceneNode) -> void {
                          m_Renderer.Draw(sceneNode);
                      });
        m_FrameBuffer->Bind();

        m_Renderer.EndScene();
    }
}
