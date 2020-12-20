//
// Created by christian on 30/08/2020.
//
#include <Tracy.hpp>
#include "camera/TrackBallCamera.h"
#include "camera/PerspectiveCameraController.h"
#include "core/Time.h"
#include "event/MouseEvent.h"
#include "event/KeyEvent.h"
#include "event/WindowsEvent.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCameraController::PerspectiveCameraController(float translationSpeed, float rotationSpeed)
            : m_TranslationSpeed(translationSpeed), m_RotationSpeed(rotationSpeed) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCameraController::~PerspectiveCameraController() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveLeft() {
        --m_TranslationVec.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveRight() {
        ++m_TranslationVec.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveUp() {
        --m_TranslationVec.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveDown() {
        ++m_TranslationVec.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveNear() {
        --m_TranslationVec.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::MoveFar() {
        ++m_TranslationVec.z;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnUpdate(const TimeFrame &ts) {
        ZoneScopedN("CameraUpdate")
        if (m_TranslationVec.x != 0 || m_TranslationVec.y != 0 || m_TranslationVec.z != 0) {
            ZoneScopedN("CameraTranslation")

            m_TranslationVec *= (ts.MiliSeconds() * m_TranslationSpeed);
            Translate(m_TranslationVec);

            m_TranslationVec.x = 0;
            m_TranslationVec.y = 0;
            m_TranslationVec.z = 0;
        }

        ReturnUnless(m_Rotate)
        {
            ZoneScopedN("CameraRotation")

            Rotate(m_OldMousePosition, m_NewMousePosition, ts);
            m_Rotate = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCameraController::OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent) {
        if (!(keyPressedEvent.m_Key ^ Key::Left)) {
            MoveLeft();
        } else if (!(keyPressedEvent.m_Key ^ Key::Right)) {
            MoveRight();
        } else if (!(keyPressedEvent.m_Key ^ Key::Up)) {
            MoveNear();
        } else if (!(keyPressedEvent.m_Key ^ Key::Down)) {
            MoveFar();
        } else if (!(keyPressedEvent.m_Key ^ Key::Q)) {
            MoveUp();
        } else if (!(keyPressedEvent.m_Key ^ Key::E)) {
            MoveDown();
        }
    }

    void PerspectiveCameraController::OnMouseScrolled(const MouseScrolledEvent &event) {
        m_TranslationVec.z -= event.m_YOffset;
        m_TranslationVec.x -= event.m_XOffset;
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
            m_OldMousePosition.x = m_NewMousePosition.x;
            m_OldMousePosition.y = m_NewMousePosition.y;

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
