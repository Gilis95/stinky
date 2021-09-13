//
// Created by christian on 21/10/2020.
//

#include <application/entry_point.h>
#include <camera/fps_camera.h>
#include <core/project.h>
#include <core/Time.h>
#include <event/event.h>
#include <event/layer.h>
#include <gla/graphic_layer_abstraction_factory.h>
#include <window/window.h>

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
                : application(time_frame(10000000)), m_Camera(CreateScope<fps_camera>(WIDTH, HEIGHT)),
                  m_GLAFactory(graphic_layer_abstraction_factory::create(graphic_layer_abstraction_factory::API::OpenGL)),
                  m_Window(window::Create(window::api::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::register_event_handlers() {
            application::register_event_handlers();

            m_EventController.RegisterEventHandler<glfw_window_post_init_event>(
                    [](const glfw_window_post_init_event &event) {
                        ImGuiInitializer::HandleGLFWInit(event);
                    }
            );

            m_EventController.RegisterEventHandler<mouse_scrolled_event>(
                    [camera = m_Camera.get()](const mouse_scrolled_event &event) {
                        camera->on_mouse_scrolled(event);
                    }
            );

            m_EventController.RegisterEventHandler<mouse_button_pressed_event>(
                    [camera = m_Camera.get()](const mouse_button_pressed_event &event) {
                        camera->OnMousePressed(event);
                    }
            );

            m_EventController.RegisterEventHandler<mouse_moved_event>(
                    [camera = m_Camera.get()](const mouse_moved_event &event) {
                        camera->OnMouseMoved(event);
                    }
            );

            m_EventController.RegisterEventHandler<mouse_button_released_event>(
                    [camera = m_Camera.get()](const mouse_button_released_event &event) {
                        camera->OnMouseReleased(event);
                    }
            );

            m_EventController.RegisterEventHandler<key_pressed_event>(
                    [camera = m_Camera.get()](const key_pressed_event &event) {
                        camera->on_keyboard_event(event);
                    }
            );

            m_EventController.RegisterEventHandler<window_resize_event>(
                    [camera = m_Camera.get()](const window_resize_event &event) {
                        camera->perspective_camera_controller::on_window_resize(event);
                    }
            );

        }

        /////////////////////////////////////////////////////////////////////////////////////////
        window *HoatzinApplication::get_window() {
            return m_Window.get();
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::init() {
            application::init();

            push_lLayer(
                    new HoatzinEditorLayer(m_GLAFactory.get(), m_Camera.get(), m_EventController, WIDTH,
                                           HEIGHT));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    application *create_application() {
        auto& manager = project_manager::instance();
        manager.deserialize("/home/christian/gosho.yaml");
        return new hoatzin::HoatzinApplication();
    }
}