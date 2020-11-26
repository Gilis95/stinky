//
// Created by christian on 29/08/2020.
//

#include "camera/PerspectiveCamera.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    PerspectiveCamera::PerspectiveCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              m_Rotation(1.0, 0.0, 0.0, 0.0) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::Translate(const glm::vec3 &delta, bool local /* = true */ ) {
        if (local) {
            m_Position += m_Rotation * delta;
        } else {
            m_Position += delta;
        }
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::SetRotation(const glm::quat &rot) {
        m_Rotation = rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::quat PerspectiveCamera::GetRotation() const {
        return m_Rotation;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::SetEulerAngles(const glm::vec3 &eulerAngles) {
        m_Rotation = glm::quat(glm::radians(eulerAngles));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 PerspectiveCamera::GetEulerAngles() const {
        return glm::degrees(glm::eulerAngles(m_Rotation));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::Rotate(const glm::quat &rot) {
        m_Rotation = m_Rotation * rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        // Since we know the rotation matrix is orthonormalized, we can simply
        // transpose the rotation matrix instead of inversing.
        glm::mat4 rotate = glm::transpose(glm::toMat4(m_Rotation));

        m_ViewMatrix = rotate * translate;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PerspectiveCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        // Since we know the rotation matrix is orthonormalized, we can simply
        // transpose the rotation matrix instead of inversing.
        glm::mat4 rotate = glm::transpose(glm::toMat4(m_Rotation));

        m_ViewMatrix = rotate * translate;
    }
}