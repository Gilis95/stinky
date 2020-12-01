//
// Created by christian on 29/08/2020.
//

#include "camera/FPSCamera.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCamera::FPSCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              m_Rotation(0.0f, 0.0f, -1.0f) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Translate(const glm::vec3 &delta, bool local /* = true */ ) {
        m_Position += delta;
        m_ViewDirty = true;
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Rotate(float x, float y) {
        m_Rotation.x += x;
        m_Rotation.y += y;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);

        m_ViewMatrix = glm::lookAt(
                m_Position,
                m_Rotation,
                glm::vec3(0, 1, 0)
        );
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);

        m_ViewMatrix = glm::lookAt(
                m_Position,
                m_Rotation,
                glm::vec3(0, 1, 0)
        );
        m_ViewDirty = false;
    }
}