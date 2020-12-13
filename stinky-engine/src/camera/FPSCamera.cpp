//
// Created by christian on 29/08/2020.
//

#include "camera/FPSCamera.h"
#include "event/Timestep.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCamera::FPSCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              PerspectiveCameraController(300.0f, 20.0f),
              m_Yaw(0.0f), m_Pitch(0.0f),
              m_QuatRotation(1.0, 0.0, 0.0, 0.0),
              m_Mat4Rotation(glm::toMat4(m_QuatRotation)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);

        m_ViewMatrix = translate * m_Mat4Rotation;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);

        m_ViewMatrix = translate * m_Mat4Rotation;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Translate(const glm::vec3 &delta, bool local /* = true */ ) {
        if (local) {
            m_Position += (m_QuatRotation * delta);
        } else {
            m_Position += delta;
        }
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const Timestep &ts) {
        glm::vec3 delta = newMousePosition - oldMousePosition;
        m_Pitch += delta.y * m_RotationSpeed * ts;
        m_Yaw += delta.x * m_RotationSpeed * ts;

        m_Mat4Rotation = glm::eulerAngleXY(m_Pitch, m_Yaw);
        m_QuatRotation = glm::toQuat(m_Mat4Rotation);

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::OnWindowResize(uint32_t width, uint32_t height) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        SetProjectionRH(45, aspectRatio, 1, -1);
    }
}