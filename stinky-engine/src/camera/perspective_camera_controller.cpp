//
// Created by christian on 30/08/2020.
//
#include <Tracy.hpp>
#include "camera/track_ball_camera.h"
#include "camera/perspective_camera_controller.h"
#include "core/Time.h"
#include "event/mouse_event.h"
#include "event/key_event.h"
#include "event/windows_event.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    perspective_camera_controller::perspective_camera_controller(float translationSpeed, float rotationSpeed)
            : m_TranslationSpeed(translationSpeed), m_RotationSpeed(rotationSpeed),
              _M_old_mouse_position(1.0f, 1.0f, 0.0f),
              _M_new_mouse_position(1.0f, 1.0f, 0.0f), _M_left_mouse_button_pressed(false), _M_middle_mouse_button_pressed(false),
              m_Rotate(false), m_Pan(false), _M_translation_vec(0.0f, 0.0f, 0.0f) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    perspective_camera_controller::~perspective_camera_controller() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_left() {
        --_M_translation_vec.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_right() {
        ++_M_translation_vec.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_up() {
        --_M_translation_vec.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_down() {
        ++_M_translation_vec.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_near() {
        --_M_translation_vec.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::move_far() {
        ++_M_translation_vec.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::on_update(const time_frame &ts) {
        ZoneScopedN("CameraUpdate")
        if (_M_translation_vec.x != 0 || _M_translation_vec.y != 0 || _M_translation_vec.z != 0) {
            ZoneScopedN("CameraTranslation")

            _M_translation_vec *= ts.MiliSeconds();
            translate(_M_translation_vec);

            _M_translation_vec.x = 0;
            _M_translation_vec.y = 0;
            _M_translation_vec.z = 0;
        }

        if (m_Pan) {
            pan(_M_old_mouse_position, _M_new_mouse_position, ts);
            m_Pan = false;
        }

        if (m_Rotate) {
            ZoneScopedN("CameraRotation")

            rotate(_M_old_mouse_position, _M_new_mouse_position, ts);
            m_Rotate = false;
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::on_keyboard_event(const key_pressed_event &event) {
        if (!(event.key ^ key::Left)) {
            move_left();
        } else if (!(event.key ^ key::Right)) {
            move_right();
        } else if (!(event.key ^ key::up)) {
            move_near();
        } else if (!(event.key ^ key::down)) {
            move_far();
        } else if (!(event.key ^ key::Q)) {
            move_up();
        } else if (!(event.key ^ key::E)) {
            move_down();
        }
    }

    void perspective_camera_controller::on_mouse_scrolled(const mouse_scrolled_event &event) {
        _M_translation_vec.z += event.y_offset;
        _M_translation_vec.x += event.x_offset;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::OnMousePressed(const mouse_button_pressed_event &event) {
        _M_left_mouse_button_pressed = event.button == mouse_code::ButtonLeft;
        _M_middle_mouse_button_pressed = event.button == mouse_code::ButtonMiddle;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::OnMouseReleased(const mouse_button_released_event &event) {
        _M_left_mouse_button_pressed = event.button != mouse_code::ButtonLeft && _M_left_mouse_button_pressed;
        _M_middle_mouse_button_pressed = event.button != mouse_code::ButtonMiddle && _M_middle_mouse_button_pressed;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::OnMouseMoved(const mouse_moved_event &event) {
        if (_M_left_mouse_button_pressed || _M_middle_mouse_button_pressed) {
            _M_old_mouse_position.x = _M_new_mouse_position.x;
            _M_old_mouse_position.y = _M_new_mouse_position.y;

            _M_new_mouse_position.x = event.x;
            _M_new_mouse_position.y = event.y;

            m_Rotate = _M_left_mouse_button_pressed;
            m_Pan = _M_middle_mouse_button_pressed;
            return;
        } else {
            // if button is released frame must be updated according last change, before we update new position
            ReturnIf(m_Rotate || m_Pan)

            _M_new_mouse_position.x = event.x;
            _M_new_mouse_position.y = event.y;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void perspective_camera_controller::OnWindowResize(const window_resize_event &event) {
        on_window_resize(event.width, event.height);
    }
}
