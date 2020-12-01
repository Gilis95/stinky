//
// Created by christian on 30/08/2020.
//
#include <Tracy.hpp>
#include "camera/ArcballCamera.h"
#include "camera/PerspectiveCameraController.h"
#include "event/MouseEvent.h"
#include "event/KeyEvent.h"
#include "event/Timestep.h"
#include "event/WindowsEvent.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCameraController::PerspectiveCameraController() {
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
    void PerspectiveCameraController::MoveLeft() {
        --m_CameraPosition.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveRight() {
        ++m_CameraPosition.x;
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
        ZoneScopedN("CameraUpdate")
        if (m_CameraPosition.x != 0 || m_CameraPosition.y != 0 || m_CameraPosition.z != 0) {
            ZoneScopedN("CameraTranslation")
            Translate(ts);
        }

        ReturnUnless(m_Rotate)
        {
            ZoneScopedN("CameraRotation")
            Rotate(ts);
            m_Rotate = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent) {
        const auto keyCode = dynamic_cast<const KeyPressedEvent &>(keyPressedEvent).m_Key;

        auto functionToExecute = m_CameraMoveFunctions.find(keyCode);
        ReturnIf(functionToExecute == m_CameraMoveFunctions.end())

        functionToExecute->second();
    }

    void PerspectiveCameraController::OnMouseScrolled(const MouseScrolledEvent &event) {
        m_CameraPosition.z -= event.m_YOffset;
        m_CameraPosition.x -= event.m_XOffset;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMousePressed(const MouseButtonPressedEvent &event) {
        m_MousePressed = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMouseReleased(const MouseButtonReleasedEvent &event) {
        m_MousePressed = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnMouseMoved(const MouseMovedEvent &event) {
        const auto mouseMovedEvent = dynamic_cast<const MouseMovedEvent &>(event);

        if (m_MousePressed) {
            m_OldMousePosition = m_NewMousePosition;
            m_NewMousePosition.x = mouseMovedEvent.m_MouseX;
            m_NewMousePosition.y = mouseMovedEvent.m_MouseY;

            m_Rotate = true;
            return;
        } else {
            // if button is released new frame must update according last change, before we update new position
            ReturnIf(m_Rotate)

            m_NewMousePosition.x = mouseMovedEvent.m_MouseX;
            m_NewMousePosition.y = mouseMovedEvent.m_MouseY;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnWindowResize(const WindowResizeEvent &event) {
        OnWindowResize(event.m_Width, event.m_Height);
    }
}
