//
// Created by christian on 29/08/2020.
//

#include "camera/ArcballCamera.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    ArcballCamera::ArcballCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              m_Rotation(1.0, 0.0, 0.0, 0.0) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::Translate(const glm::vec3 &delta, bool local /* = true */ ) {
        if (local) {
            m_Position += m_Rotation * delta;
        } else {
            m_Position += delta;
        }
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::SetRotation(const glm::quat &rot) {
        m_Rotation = rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::quat ArcballCamera::GetRotation() const {
        return m_Rotation;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::SetEulerAngles(const glm::vec3 &eulerAngles) {
        m_Rotation = glm::quat(glm::radians(eulerAngles));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 ArcballCamera::GetEulerAngles() const {
        return glm::degrees(glm::eulerAngles(m_Rotation));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::Rotate(const glm::quat &rot) {
        m_Rotation *= rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        glm::mat4 rotate = glm::toMat4(m_Rotation);

        m_ViewMatrix = translate * rotate;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void ArcballCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        glm::mat4 rotate = glm::toMat4(m_Rotation);

        m_ViewMatrix = translate * rotate;
        m_ViewDirty = false;
    }
}