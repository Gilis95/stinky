//
// Created by christian on 29/08/2020.
//

#include "camera/FPSCamera.h"
#include "core/Time.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    FPSCamera::FPSCamera(uint32_t screenWidth, uint32_t screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              PerspectiveCameraController(0.09f, 0.8f), m_Yaw(0.0f), m_Pitch(0.0f), m_FocalPoint(0.0f) {
        glm::vec3 position = {-5, 5, 5};
        m_Distance = glm::distance(position, m_FocalPoint);

        FPSCamera::RecalculateViewProjectionMatrix();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void FPSCamera::RecalculateViewProjectionMatrix() {
        ReturnUnless(m_ViewDirty);
        glm::vec3 position(CalculatePosition());

        glm::quat orientation = GetOrientation();
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
        m_ViewMatrix = glm::inverse(m_ViewMatrix);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty);
        glm::vec3 position(CalculatePosition());

        glm::quat orientation = GetOrientation();
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
        m_ViewMatrix = glm::inverse(m_ViewMatrix);

        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) {
        glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.03f;

        auto[xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) {
        glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.009f;

        float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
        m_Yaw += yawSign * delta.x * m_RotationSpeed;
        m_Pitch += delta.y * m_RotationSpeed;

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Translate(const glm::vec3 &delta) {
        auto[xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDirection() * delta.x * 0.7f * xSpeed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * 0.7f * ySpeed * m_Distance;
        Zoom(-delta.z, 0.0f);

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::Zoom(float yOffset, float xOffset) {
        m_Distance -= yOffset * ZoomSpeed() * 0.07f;
        if (m_Distance < 1.0f) {
            m_FocalPoint += GetForwardDirection();
            m_Distance = 1.0f;
        }

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void FPSCamera::OnWindowResize(uint32_t width, uint32_t height) {
        m_ViewportWidth = width;
        m_ViewportHeight = height;
        float aspectRatio = static_cast<float>(m_ViewportWidth) / static_cast<float>(m_ViewportHeight);
        SetProjectionRH(45, aspectRatio, 1, -1);
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 FPSCamera::GetUpDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 FPSCamera::GetRightDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 FPSCamera::GetForwardDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 FPSCamera::CalculatePosition() const {
        return m_FocalPoint - GetForwardDirection() * m_Distance;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::quat FPSCamera::GetOrientation() const {
        return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    std::pair<float, float> FPSCamera::PanSpeed() const {
        float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
        float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

        return {xFactor, yFactor};
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    float FPSCamera::ZoomSpeed() const {
        float distance = m_Distance * 0.2f;
        distance = std::max(distance, 0.0f);
        float speed = distance * distance;
        speed = std::min(speed, 100.0f); // max speed = 100
        return speed;
    }
}