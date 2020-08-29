//
// Created by christian on 23/08/2020.
//

#include <event/MouseEvent.h>
#include <event/ApplicationEvent.h>
#include "renderer/OrthographicCameraController.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OrthographicCameraController::OrthographicCameraController(OrthographicCamera &camera,
                                                               float aspectRatio)
            : m_Camera(camera), m_CameraPosition(camera.GetPosition()), m_CameraSpeed(1.0f),
              m_CameraRotation(m_Camera.GetRotation()), m_Commands(), m_CameraMoveFunctions(7),
              m_CameraRotationSpeed(180.0f), m_AspectRatio(aspectRatio), m_ZoomLevel(1.0) {
        m_CameraMoveFunctions.emplace(KeyCode::Left,
                                      std::bind(&OrthographicCameraController::MoveLeft, this,
                                                std::placeholders::_1));
        m_CameraMoveFunctions.emplace(KeyCode::Right,
                                      std::bind(&OrthographicCameraController::MoveRight, this,
                                                std::placeholders::_1));
        m_CameraMoveFunctions.emplace(KeyCode::Up,
                                      std::bind(&OrthographicCameraController::MoveUp, this,
                                                std::placeholders::_1));
        m_CameraMoveFunctions.emplace(KeyCode::Down,
                                      std::bind(&OrthographicCameraController::MoveDown, this,
                                                std::placeholders::_1));
        m_CameraMoveFunctions.emplace(KeyCode::Q,
                                      std::bind(&OrthographicCameraController::RotateLeft, this,
                                                std::placeholders::_1));
        m_CameraMoveFunctions.emplace(KeyCode::E,
                                      std::bind(&OrthographicCameraController::RotateRight, this,
                                                std::placeholders::_1));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnUpdate(const Timestep &ts) {
        auto commandIterator = m_Commands.begin();
        ReturnIf(commandIterator == m_Commands.end());

        do {
            auto functionToExecute = m_CameraMoveFunctions.find(*commandIterator);
            if (functionToExecute != m_CameraMoveFunctions.end()) {
                functionToExecute->second(ts);
            }

            commandIterator = m_Commands.erase(commandIterator);
        } while (commandIterator != m_Commands.end());

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnKeyboardEvent(const Event &keyPressedEvent) {
        m_Commands.push_back(static_cast<const KeyPressedEvent &>(keyPressedEvent).m_Key);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveLeft(const Timestep &ts) {
        m_CameraPosition.x -= m_CameraSpeed * ts;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveRight(const Timestep &ts) {
        m_CameraPosition.x += m_CameraSpeed * ts;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveUp(const Timestep &ts) {
        m_CameraPosition.y += m_CameraSpeed * ts;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::MoveDown(const Timestep &ts) {
        m_CameraPosition.y -= m_CameraSpeed * ts;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::RotateLeft(const Timestep &ts) {
        m_CameraRotation += m_CameraRotationSpeed * ts;

        if (m_CameraRotation == 360.0f || m_CameraRotation == -360.0f)
            m_CameraRotation = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::RotateRight(const Timestep &ts) {
        m_CameraRotation -= m_CameraRotationSpeed * ts;

        if (m_CameraRotation == 360.0f || m_CameraRotation == -360.0f)
            m_CameraRotation = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnWindowResize(const Event &event) {
        auto resizeEvent = dynamic_cast<const WindowResizeEvent &>(event);

        WindowResize(static_cast<float>(resizeEvent.m_Width), static_cast<float>(resizeEvent
                .m_Height));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::WindowResize(float width, float height) {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                               -m_ZoomLevel, m_ZoomLevel);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCameraController::OnZoom(const Event &e) {

        m_ZoomLevel -= dynamic_cast<const MouseScrolledEvent &>(e).m_YOffset * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                               -m_ZoomLevel, m_ZoomLevel);

    }

}