//
// Created by christian on 30/08/2020.
//
#include <event/MouseEvent.h>
#include <event/KeyEvent.h>
#include "camera/PerspectiveCamera.h"
#include "camera/PerspectiveCameraController.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCameraController::PerspectiveCameraController(PerspectiveCamera *camera) : m_Camera(camera) {
        m_CameraMoveFunctions.emplace(KeyCode::Left,
                                      [this] { MoveLeft(); });
        m_CameraMoveFunctions.emplace(KeyCode::Right,
                                      [this] { MoveRight(); });
        m_CameraMoveFunctions.emplace(KeyCode::Up,
                                      [this] { MoveNear(); });
        m_CameraMoveFunctions.emplace(KeyCode::Down,
                                      [this] { MoveFar(); });
        m_CameraMoveFunctions.emplace(KeyCode::Q,
                                      [this] { MoveUp(); });
        m_CameraMoveFunctions.emplace(KeyCode::E,
                                      [this] { MoveDown(); });
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCameraController::~PerspectiveCameraController() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::LookAt() {
//        using namespace glm;
//        vec3 zaxis = normalize(eye - target);    // The "forward" vector.
//        vec3 xaxis = normalize(cross(up, zaxis));// The "right" vector.
//        vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.
//
//        // Create a 4x4 view matrix from the right, up, forward and eye position vectors
//        mat4 viewMatrix(
//                vec4(       xaxis.x,            yaxis.x,            zaxis.x,       0 ),
//                vec4(       xaxis.y,            yaxis.y,            zaxis.y,       0 ),
//                vec4(       xaxis.z,            yaxis.z,            zaxis.z,       0 ),
//                vec4( -dot( xaxis, eye ), -dot( yaxis, eye ), -dot( zaxis, eye ),  1 )
//        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::FPSLookAt(const Timestep &ts) {
        glm::vec2 delta = m_NewMousePosition - m_OldMousePosition;

        m_Pitch += delta.y * (m_CameraSpeed + ts + 0.001f);
        m_Yaw += delta.x * (m_CameraSpeed + ts + 0.001f);

        m_Pitch = glm::clamp(m_Pitch, -90.0f, 90.0f);
        m_Yaw = std::fmod(m_Yaw, 360.0f);

        glm::quat cameraRotation = glm::toQuat(glm::eulerAngleYX(glm::radians(m_Yaw), glm::radians(m_Pitch)));
        m_Camera->SetRotation(cameraRotation);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveLeft() {
        ++m_CameraPosition.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveRight() {
        --m_CameraPosition.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveUp() {
        --m_CameraPosition.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveDown() {
        ++m_CameraPosition.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveNear() {
        --m_CameraPosition.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveFar() {
        ++m_CameraPosition.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnUpdate(const Timestep &ts) {
        if (m_CameraPosition.x != 0 || m_CameraPosition.y != 0 || m_CameraPosition.z != 0) {
            m_CameraPosition.x *= (m_CameraSpeed * ts);
            m_CameraPosition.y *= (m_CameraSpeed * ts);
            m_CameraPosition.z *= (m_CameraSpeed * ts);

            m_Camera->Translate(m_CameraPosition);

            m_CameraPosition.x = 0;
            m_CameraPosition.y = 0;
            m_CameraPosition.z = 0;
        }

        ReturnUnless(m_Rotate)
        FPSLookAt(ts);
        m_Rotate = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnKeyboardEvent(const Event &keyPressedEvent) {
        const auto keyCode = dynamic_cast<const KeyPressedEvent &>(keyPressedEvent).m_Key;

        auto functionToExecute = m_CameraMoveFunctions.find(keyCode);
        ReturnIf(functionToExecute == m_CameraMoveFunctions.end())

        functionToExecute->second();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMousePressed(const Event &event) {
        m_MousePressed = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMouseReleased(const Event &event) {
        m_MousePressed = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMouseMoved(const Event &event) {
        ReturnUnless(m_MousePressed)

        const auto mouseMovedEvent = dynamic_cast<const MouseMovedEvent &>(event);
        m_OldMousePosition = m_NewMousePosition;
        m_NewMousePosition.x = mouseMovedEvent.m_MouseX;
        m_NewMousePosition.y = mouseMovedEvent.m_MouseY;
        m_Rotate = true;
    }
}
