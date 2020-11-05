//
// Created by christian on 21/10/2020.
//

#include <application/EntryPoint.h>
#include <camera/PerspectiveCameraController.h>
#include <event/Event.h>
#include <event/EventController.h>
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
                : Application(), m_CameraController(CreateScope<PerspectiveCameraController>()),
                  m_GLAFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
                  m_Window(Window::Create(Window::API::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::RegisterEvents() {
            Application::RegisterEvents();

            m_EventController.RegisterEventHandler(
                    {
                            EventType::GLFWWindowPostInitEvent,
                            [](const Event &event) {
                                ImGuiInitializer::HandleGLFWInit(event);
                            }
                    }
            );

            m_EventController.RegisterEventHandler(
                    {
                            EventType::MouseButtonPressed,
                            [cameraController = m_CameraController.get()](const Event &event) {
                                cameraController->OnMousePressed(event);
                            }
                    }
            );

            m_EventController.RegisterEventHandler(
                    {
                            EventType::MouseMoved,
                            [cameraController = m_CameraController.get()](const Event &event) {
                                cameraController->OnMouseMoved(event);
                            }
                    }
            );

            m_EventController.RegisterEventHandler(
                    {
                            EventType::MouseButtonReleased,
                            [cameraController = m_CameraController.get()](const Event &event) {
                                cameraController->OnMouseReleased(event);
                            }
                    }
            );

            m_EventController.RegisterEventHandler(
                    {
                            EventType::KeyPressed,
                            [cameraController = m_CameraController.get()](const Event &event) {
                                cameraController->OnKeyboardEvent(event);
                            }
                    }
            );

            m_EventController.RegisterEventHandler(
                    {
                            EventType::WindowResize,
                            [cameraController = m_CameraController.get()](const Event &event) {
                                cameraController->OnWindowResize(event);
                            }
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
                    new HoatzinEditorLayer(m_GLAFactory.get(), m_CameraController.get(), WIDTH, HEIGHT));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        return new hoatzin::HoatzinApplication();
    }
}