//
// Created by christian on 23/08/2020.
//

#include "camera/orthographic_camera.h"
#include "camera/orthographic_camera_controller.h"
#include "core/Time.h"
#include "event/application_event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/windows_event.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    orthographic_camera_controller::orthographic_camera_controller(orthographic_camera &camera,
                                                                   float aspectRatio)
            : m_Camera(camera), m_CameraPosition(camera.get_position()), m_CameraSpeed(1.0f),
              m_CameraRotation(m_Camera.GetRotation()),
              m_CameraRotationSpeed(180.0f), m_AspectRatio(aspectRatio), m_ZoomLevel(1.0) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::on_update(const time_frame &ts) {
        // Translation
        if (m_CameraPosition.x != 0 || m_CameraPosition.y != 0) {
            m_CameraPosition *= (ts.MiliSeconds() * m_CameraSpeed);

            m_Camera.translate(m_CameraPosition);

            m_CameraPosition.x = 0;
            m_CameraPosition.y = 0;
        }

        // Rotation
        ReturnUnless(m_CameraRotation != 0)
        m_CameraRotation *= (ts.MiliSeconds() * m_CameraRotationSpeed);
        m_Camera.rotate(m_CameraRotation);

        m_CameraRotation = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::on_keyboard_event(const key_pressed_event &keyPressedEvent) {
        if (!(keyPressedEvent.key ^ key::Left)) {
            MoveLeft();
        } else if (!(keyPressedEvent.key ^ key::Right)) {
            MoveRight();
        } else if (!(keyPressedEvent.key ^ key::up)) {
            MoveUp();
        } else if (!(keyPressedEvent.key ^ key::down)) {
            MoveDown();
        } else if (!(keyPressedEvent.key ^ key::Q)) {
            RotateLeft();
        } else if (!(keyPressedEvent.key ^ key::E)) {
            RotateRight();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::MoveLeft() {
        m_CameraPosition.x = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::MoveRight() {
        m_CameraPosition.x = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::MoveUp() {
        m_CameraPosition.y = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::MoveDown() {
        m_CameraPosition.y = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::RotateLeft() {
        m_CameraRotation = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::RotateRight() {
        m_CameraRotation = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::OnWindowResize(const window_resize_event &event) {

        WindowResize(static_cast<float>(event.width), static_cast<float>(event
                .height));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::WindowResize(float width, float height) {
        m_AspectRatio = width / height;
        m_Camera.set_projection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel, m_ZoomLevel);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void orthographic_camera_controller::OnZoom(const mouse_scrolled_event &e) {
        m_ZoomLevel -= e.y_offset * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.set_projection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                                -m_ZoomLevel, m_ZoomLevel);
    }

}