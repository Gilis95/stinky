//
// Created by christian on 21/10/2020.
//

#include <application/EntryPoint.h>
#include <camera/ArcballCameraController.h>
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
                : Application(), m_CameraController(CreateScope<ArcballCameraController>()),
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
                    [cameraController = m_CameraController.get()](const MouseScrolledEvent &event) {
                        cameraController->OnMouseScrolled(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseButtonPressedEvent>(
                    [cameraController = m_CameraController.get()](const MouseButtonPressedEvent &event) {
                        cameraController->OnMousePressed(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseMovedEvent>(
                    [cameraController = m_CameraController.get()](const MouseMovedEvent &event) {
                        cameraController->OnMouseMoved(event);
                    }
            );

            m_EventController.RegisterEventHandler<MouseButtonReleasedEvent>(
                    [cameraController = m_CameraController.get()](const MouseButtonReleasedEvent &event) {
                        cameraController->OnMouseReleased(event);
                    }
            );

            m_EventController.RegisterEventHandler<KeyPressedEvent>(
                    [cameraController = m_CameraController.get()](const KeyPressedEvent &event) {
                        cameraController->OnKeyboardEvent(event);
                    }
            );

            m_EventController.RegisterEventHandler<WindowResizeEvent>(
                    [cameraController = m_CameraController.get()](const WindowResizeEvent &event) {
                        cameraController->PerspectiveCameraController::OnWindowResize(event);
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
                    new HoatzinEditorLayer(m_GLAFactory.get(), m_CameraController.get(), m_EventController, WIDTH,
                                           HEIGHT));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new hoatzin::HoatzinApplication();
    }
}