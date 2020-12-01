//
// Created by christian on 30/08/2020.
//
#include <Tracy.hpp>
#include "camera/FPSCamera.h"
#include "camera/FPSCameraController.h"
#include "event/MouseEvent.h"
#include "event/KeyEvent.h"
#include "event/Timestep.h"
#include "event/WindowsEvent.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCameraController::FPSCameraController() : FPSCameraController(nullptr) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCameraController::FPSCameraController(FPSCamera *camera) : m_Camera(camera) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCameraController::~FPSCameraController() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCameraController::Rotate(const Timestep &ts) {
        glm::vec2 delta = m_OldMousePosition - m_NewMousePosition;

        m_Camera->Rotate((delta.x * m_RotationSpeed * ts), (delta.y * m_RotationSpeed * ts));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCameraController::Translate(const Timestep &ts) {
        m_CameraPosition.x *= (m_CameraSpeed * ts);
        m_CameraPosition.y *= (m_CameraSpeed * ts);
        m_CameraPosition.z *= (m_CameraSpeed * ts);

        m_Camera->Translate(m_CameraPosition);

        m_CameraPosition.x = 0;
        m_CameraPosition.y = 0;
        m_CameraPosition.z = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCameraController::OnWindowResize(uint32_t width, uint32_t height) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        m_Camera->SetProjectionRH(45, aspectRatio, 1, -1);
    }
}
