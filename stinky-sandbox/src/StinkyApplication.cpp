
#include <application/entry_point.h>
#include <camera/track_ball_camera.h>
#include <core/stinky_macros.h>
#include <core/Time.h>
#include <event/event.h>
#include <event/layer.h>
#include <gla/graphic_layer_abstraction_factory.h>

#include <window/window.h>
#include "StinkyApplication.h"
#include "StinkyLayer.h"

namespace stinky {
    namespace {
        uint32_t WIDTH = 1280;
        uint32_t HEIGHT = 720;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyApplication::StinkyApplication()
            : application(time_frame(3333333)),
              m_Camera(create_scope<track_ball_camera>()),
              m_GLAFactory(graphic_layer_abstraction_factory::create(graphic_layer_abstraction_factory::API::OpenGL)),
              m_Window(window::Create(window::api::GLFW, m_EventController, {"Hoatzin", WIDTH, HEIGHT})) {
    }

    void StinkyApplication::register_event_handlers() {
        application::register_event_handlers();

        m_EventController.register_event_handler<mouse_scrolled_event>(
                [cameraController = m_Camera.get()](const mouse_scrolled_event &event) {
                    cameraController->on_mouse_scrolled(event);
                }
        );

        m_EventController.register_event_handler<mouse_button_pressed_event>(
                [cameraController = m_Camera.get()](const mouse_button_pressed_event &event) {
                    cameraController->on_mouse_pressed(event);
                }
        );

        m_EventController.register_event_handler<mouse_moved_event>(
                [cameraController = m_Camera.get()](const mouse_moved_event &event) {
                    cameraController->on_mouse_moved(event);
                }
        );

        m_EventController.register_event_handler<mouse_button_released_event>(
                [cameraController = m_Camera.get()](const mouse_button_released_event &event) {
                    cameraController->on_mouse_released(event);
                }
        );

        m_EventController.register_event_handler<key_pressed_event>(
                [cameraController = m_Camera.get()](const key_pressed_event &event) {
                    cameraController->on_keyboard_event(event);
                }
        );
    }

    void StinkyApplication::init() {
        application::init();

        push_lLayer(new StinkyLayer(m_GLAFactory.get(), m_Camera.get(), m_EventController, WIDTH,
                                    HEIGHT));
    }

    window *StinkyApplication::get_window() {
        return m_Window.get();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    application *create_application() {
        return new StinkyApplication();
    }

}
