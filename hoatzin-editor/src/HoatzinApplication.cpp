//
// Created by christian on 21/10/2020.
//

#include <application/entry_point.h>
#include <asset/asset_manager.h>
#include <asset/handler/gltf/gltf_handler.h>
#include <camera/fps_camera.h>
#include <core/Time.h>
#include <core/project.h>
#include <event/event.h>
#include <event/layer.h>
#include <gla/graphic_layer_abstraction_factory.h>
#include <window/window.h>

#include "HoatzinApplication.h"
#include "event/HoatzinEditorLayer.h"
#include "imgui/platform/glfw/ImGuiInitializer.h"

namespace stinky {
    namespace hoatzin {
        namespace {
            uint32_t WIDTH = 1280;
            uint32_t HEIGHT = 720;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        HoatzinApplication::HoatzinApplication()
                : application(time_frame(10000000)), m_Camera(create_scope<fps_camera>(WIDTH, HEIGHT)),
                  m_GLAFactory(graphic_layer_abstraction_factory::create(graphic_layer_abstraction_factory::API::OpenGL)),
                  m_Window(window::Create(window::api::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        void HoatzinApplication::register_event_handlers() {
            application::register_event_handlers();

            m_EventController.register_event_handler<glfw_window_post_init_event>(
                    [](const glfw_window_post_init_event &event) {
                        ImGuiInitializer::HandleGLFWInit(event);
                    }
            );

            m_EventController.register_event_handler<mouse_scrolled_event>(
                    [camera = m_Camera.get()](const mouse_scrolled_event &event) {
                        camera->on_mouse_scrolled(event);
                    }
            );

            m_EventController.register_event_handler<mouse_button_pressed_event>(
                    [camera = m_Camera.get()](const mouse_button_pressed_event &event) {
                        camera->on_mouse_pressed(event);
                    }
            );

            m_EventController.register_event_handler<mouse_moved_event>(
                    [camera = m_Camera.get()](const mouse_moved_event &event) {
                        camera->on_mouse_moved(event);
                    }
            );

            m_EventController.register_event_handler<mouse_button_released_event>(
                    [camera = m_Camera.get()](const mouse_button_released_event &event) {
                        camera->on_mouse_released(event);
                    }
            );

            m_EventController.register_event_handler<key_pressed_event>(
                    [camera = m_Camera.get()](const key_pressed_event &event) {
                        camera->on_keyboard_event(event);
                    }
            );

            m_EventController.register_event_handler<window_resize_event>(
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
            gltf_handler handler;
            asset_manager::instance().import_file("/home/christian/workspace/games/stinky/assets/Cube.gltf");
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    application *create_application() {
        auto& manager = project_manager::instance();
        manager.open("/home/christian/workspace/games/stinky/first.stinky");
        return new hoatzin::HoatzinApplication();
    }
}