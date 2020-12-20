
#include <application/EntryPoint.h>
#include <camera/TrackBallCamera.h>
#include <core/StinkyMacros.h>
#include <core/Time.h>
#include <event/Event.h>
#include <event/Layer.h>
#include <gla/GraphicLayerAbstractionFactory.h>

#include <window/Window.h>
#include "StinkyApplication.h"
#include "StinkyLayer.h"

namespace stinky {
    namespace {
        uint32_t WIDTH = 1280;
        uint32_t HEIGHT = 720;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyApplication::StinkyApplication()
            : Application(TimeFrame(3333333)),
              m_Camera(CreateScope<TrackBallCamera>()),
              m_GLAFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
              m_Window(Window::Create(Window::API::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
    }

    void StinkyApplication::RegisterEventHandlers() {
        Application::RegisterEventHandlers();

        m_EventController.RegisterEventHandler<MouseScrolledEvent>(
                [cameraController = m_Camera.get()](const MouseScrolledEvent &event) {
                    cameraController->OnMouseScrolled(event);
                }
        );

        m_EventController.RegisterEventHandler<MouseButtonPressedEvent>(
                [cameraController = m_Camera.get()](const MouseButtonPressedEvent &event) {
                    cameraController->OnMousePressed(event);
                }
        );

        m_EventController.RegisterEventHandler<MouseMovedEvent>(
                [cameraController = m_Camera.get()](const MouseMovedEvent &event) {
                    cameraController->OnMouseMoved(event);
                }
        );

        m_EventController.RegisterEventHandler<MouseButtonReleasedEvent>(
                [cameraController = m_Camera.get()](const MouseButtonReleasedEvent &event) {
                    cameraController->OnMouseReleased(event);
                }
        );

        m_EventController.RegisterEventHandler<KeyPressedEvent>(
                [cameraController = m_Camera.get()](const KeyPressedEvent &event) {
                    cameraController->OnKeyboardEvent(event);
                }
        );
    }

    void StinkyApplication::Init() {
        Application::Init();

        PushLayer(new StinkyLayer(m_GLAFactory.get(), m_Camera.get(), m_EventController, WIDTH,
                                  HEIGHT));
    }

    Window *StinkyApplication::GetWindow() {
        return m_Window.get();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new StinkyApplication();
    }

}
