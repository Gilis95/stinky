//
// Created by christian on 23/08/2020.
//

#include "camera/OrthographicCamera.h"
#include "camera/OrthographicCameraController.h"
#include "core/Time.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowsEvent.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OrthographicCameraController::OrthographicCameraController(OrthographicCamera &camera,
                                                               float aspectRatio)
            : m_Camera(camera), m_CameraPosition(camera.GetPosition()), m_CameraSpeed(1.0f),
              m_CameraRotation(m_Camera.GetRotation()),
              m_CameraRotationSpeed(180.0f), m_AspectRatio(aspectRatio), m_ZoomLevel(1.0) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnUpdate(const TimeFrame &ts) {
        // Translation
        if (m_CameraPosition.x != 0 || m_CameraPosition.y != 0) {
            m_CameraPosition *= (ts.MiliSeconds() * m_CameraSpeed);

            m_Camera.Translate(m_CameraPosition);

            m_CameraPosition.x = 0;
            m_CameraPosition.y = 0;
        }

        // Rotation
        ReturnUnless(m_CameraRotation != 0)
        m_CameraRotation *= (ts.MiliSeconds() * m_CameraRotationSpeed);
        m_Camera.Rotate(m_CameraRotation);

        m_CameraRotation = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent) {
        if (!(keyPressedEvent.m_Key ^ Key::Left)) {
            MoveLeft();
        } else if (!(keyPressedEvent.m_Key ^ Key::Right)) {
            MoveRight();
        } else if (!(keyPressedEvent.m_Key ^ Key::Up)) {
            MoveUp();
        } else if (!(keyPressedEvent.m_Key ^ Key::Down)) {
            MoveDown();
        } else if (!(keyPressedEvent.m_Key ^ Key::Q)) {
            RotateLeft();
        } else if (!(keyPressedEvent.m_Key ^ Key::E)) {
            RotateRight();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveLeft() {
        m_CameraPosition.x = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveRight() {
        m_CameraPosition.x = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveUp() {
        m_CameraPosition.y = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveDown() {
        m_CameraPosition.y = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::RotateLeft() {
        m_CameraRotation = 1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::RotateRight() {
        m_CameraRotation = -1.0f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnWindowResize(const WindowResizeEvent &event) {

        WindowResize(static_cast<float>(event.m_Width), static_cast<float>(event
                .m_Height));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::WindowResize(float width, float height) {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                               -m_ZoomLevel, m_ZoomLevel);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnZoom(const MouseScrolledEvent &e) {
        m_ZoomLevel -= e.m_YOffset * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                               -m_ZoomLevel, m_ZoomLevel);
    }

}