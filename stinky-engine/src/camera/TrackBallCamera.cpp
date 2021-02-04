//
// Created by christian on 29/08/2020.
//

#include <Tracy.hpp>
#include "camera/TrackBallCamera.h"
#include "core/Time.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    TrackBallCamera::TrackBallCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              PerspectiveCameraController(0.04f, 0.28f),
              m_Rotation(1.0, 0.0, 0.0, 0.0) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::SetRotation(const glm::quat &rot) {
        m_Rotation = rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::quat TrackBallCamera::GetRotation() const {
        return m_Rotation;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::Rotate(const glm::quat &rot) {
        m_Rotation *= rot;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        glm::mat4 rotate = glm::toMat4(m_Rotation);

        m_ViewMatrix = translate * rotate;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 translate = glm::translate(-m_Position);
        glm::mat4 rotate = glm::toMat4(m_Rotation);

        m_ViewMatrix = translate * rotate;
        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::Translate(const glm::vec3 &delta, bool local /* = true */ ) {
        if (local) {
            m_Position += m_Rotation * delta;
        } else {
            m_Position += delta;
        }
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void
    TrackBallCamera::Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) {
        glm::vec3 rotVector = glm::normalize(glm::cross(newMousePosition - oldMousePosition, glm::vec3(0, 0, -2)));

        float rotationAngle =
                glm::acos(std::max(
                        std::min(glm::dot(glm::normalize(oldMousePosition), glm::normalize(newMousePosition)), 1.0f),
                        -1.0f)) * ts.MiliSeconds() * m_RotationSpeed;
        float rotationAngleCos = glm::cos(rotationAngle);
        float rotationAngleSin = glm::sin(rotationAngle);

        glm::quat rotQuat(rotationAngleCos,
                          rotationAngleSin *
                          rotVector);

        Rotate(rotQuat);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::OnWindowResize(uint32_t width, uint32_t height) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        SetProjectionRH(45, aspectRatio, 1, -1);
    }
}