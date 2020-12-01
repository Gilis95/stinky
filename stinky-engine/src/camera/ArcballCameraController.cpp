//
// Created by christian on 30/08/2020.
//
#include <Tracy.hpp>
#include "camera/ArcballCamera.h"
#include "camera/ArcballCameraController.h"
#include "event/MouseEvent.h"
#include "event/KeyEvent.h"
#include "event/Timestep.h"
#include "event/WindowsEvent.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    ArcballCameraController::ArcballCameraController() : ArcballCameraController(nullptr) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    ArcballCameraController::ArcballCameraController(ArcballCamera *camera) : m_Camera(camera) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    ArcballCameraController::~ArcballCameraController() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCameraController::Rotate(const Timestep &ts) {
        glm::vec2 delta = m_NewMousePosition - m_OldMousePosition;

        float pitch = delta.y * m_RotationSpeed * ts;
        float yaw = delta.x * m_RotationSpeed * ts;

        glm::quat cameraRotation = glm::toQuat(glm::eulerAngleXY(glm::radians(pitch), glm::radians(yaw)));
        m_Camera->Rotate(cameraRotation);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCameraController::Translate(const Timestep &ts) {
        ZoneScopedN("CameraTranslation")
        m_CameraPosition.x *= (m_CameraSpeed * ts);
        m_CameraPosition.y *= (m_CameraSpeed * ts);
        m_CameraPosition.z *= (m_CameraSpeed * ts);

        m_Camera->Translate(m_CameraPosition);

        m_CameraPosition.x = 0;
        m_CameraPosition.y = 0;
        m_CameraPosition.z = 0;
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCameraController::OnWindowResize(uint32_t width, uint32_t height) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        m_Camera->SetProjectionRH(45, aspectRatio, 1, -1);
    }
}
