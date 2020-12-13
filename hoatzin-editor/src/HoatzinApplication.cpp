//
// Created by christian on 21/10/2020.
//

#include <application/EntryPoint.h>
#include <camera/TrackBallCamera.h>
#include <event/Event.h>
#include <event/Layer.h>
#include <gla/GraphicLayerAbstractionFactory.h>
#include <window/Window.h>

#include "event/HoatzinEditorLayer.h"
#include "HoatzinApplication.h"
#include "imgui/platform/glfw/ImGuiInitializer.h"

namespace stinky {
    namespace hoatzin {
        namespace {
            uint32_t WIDTH = 1280;
            uint32_t HEIGHT = 720;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        HoatzinApplication::HoatzinApplication()
                : Application(), m_Camera(CreateScope<TrackBallCamera>(WIDTH, HEIGHT)),
                  m_GLAFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
                  m_Window(Window::Create(Window::API::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::RegisterEventHandlers() {
            Application::RegisterEventHandlers();

            m_EventController.RegisterEventHandler<GLFWWindowPostInitEvent>(
                    [](const Event &event) {
                        ImGuiInitializer::HandleGLFWInit(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseScrolledEvent>(
                    [camera = m_Camera.get()](const MouseScrolledEvent &event) {
                        camera->OnMouseScrolled(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseButtonPressedEvent>(
                    [camera = m_Camera.get()](const MouseButtonPressedEvent &event) {
                        camera->OnMousePressed(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseMovedEvent>(
                    [camera = m_Camera.get()](const MouseMovedEvent &event) {
                        camera->OnMouseMoved(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseButtonReleasedEvent>(
                    [camera = m_Camera.get()](const MouseButtonReleasedEvent &event) {
                        camera->OnMouseReleased(event);
                    }
            );

            m_EventController.RegisterEventHandler<KeyPressedEvent>(
                    [camera = m_Camera.get()](const KeyPressedEvent &event) {
                        camera->OnKeyboardEvent(event);
                    }
            );

            m_EventController.RegisterEventHandler<WindowResizeEvent>(
                    [camera = m_Camera.get()](const WindowResizeEvent &event) {
                        camera->PerspectiveCameraController::OnWindowResize(event);
                    }
            );

        }

        /////////////////////////////////////////////////////////////////////////////////////////
        Window *HoatzinApplication::GetWindow() {
            return m_Window.get();
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::Init() {
            Application::Init();

            PushLayer(
                    new HoatzinEditorLayer(m_GLAFactory.get(), m_Camera.get(), m_EventController, WIDTH,
                                           HEIGHT));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new hoatzin::HoatzinApplication();
    }
}