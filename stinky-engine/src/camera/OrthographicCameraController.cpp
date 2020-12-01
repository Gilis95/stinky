//
// Created by christian on 23/08/2020.
//

#include "camera/OrthographicCamera.h"
#include "camera/OrthographicCameraController.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/Timestep.h"
#include "event/WindowsEvent.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OrthographicCameraController::OrthographicCameraController(OrthographicCamera &camera,
                                                               float aspectRatio)
            : m_Camera(camera), m_CameraPosition(camera.GetPosition()), m_CameraSpeed(1.0f),
              m_CameraRotation(m_Camera.GetRotation()), m_CameraMoveFunctions(7),
              m_CameraRotationSpeed(180.0f), m_AspectRatio(aspectRatio), m_ZoomLevel(1.0) {
        m_CameraMoveFunctions.emplace(KeyCode::Left,
                                      [this] { MoveLeft(); });
        m_CameraMoveFunctions.emplace(KeyCode::Right,
                                      [this] { MoveRight(); });
        m_CameraMoveFunctions.emplace(KeyCode::Up,
                                      [this] { MoveUp(); });
        m_CameraMoveFunctions.emplace(KeyCode::Down,
                                      [this] { MoveDown(); });
        m_CameraMoveFunctions.emplace(KeyCode::Q,
                                      [this] { RotateLeft(); });
        m_CameraMoveFunctions.emplace(KeyCode::E,
                                      [this] { RotateRight(); });
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnUpdate(const Timestep &ts) {
        // Translation
        if (m_CameraPosition.x != 0 || m_CameraPosition.y != 0) {
            m_CameraPosition *= (ts * m_CameraSpeed);

            m_Camera.Translate(m_CameraPosition);

            m_CameraPosition.x = 0;
            m_CameraPosition.y = 0;
        }

        // Rotation
        ReturnUnless(m_CameraRotation != 0)
        m_CameraRotation *= (ts * m_CameraRotationSpeed);
        m_Camera.Rotate(m_CameraRotation);

        m_CameraRotation = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent) {
        const auto keyCode = keyPressedEvent.m_Key;

        auto functionToExecute = m_CameraMoveFunctions.find(keyCode);
        ReturnIf(functionToExecute == m_CameraMoveFunctions.end())

        functionToExecute->second();
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