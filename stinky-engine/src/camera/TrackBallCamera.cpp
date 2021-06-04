//
// Created by christian on 29/08/2020.
//

#include <Tracy.hpp>
#include "camera/TrackBallCamera.h"
#include "core/Time.h"

#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    TrackBallCamera::TrackBallCamera(uint32_t screenWidth, uint32_t screenHeight, float fov, float zNear, float zFar)
            : Camera(glm::perspective(glm::radians(fov), (float) screenWidth / (float) screenHeight, zNear, zFar)),
              PerspectiveCameraController(0.04f, 0.56f), m_FocalPoint(0.0f), m_Rotation(1.0, 0.0, 0.0, 0.0) {
        glm::vec3 position = {-5, 5, 5};
        m_Distance = glm::distance(position, m_FocalPoint);

        TrackBallCamera::RecalculateViewProjectionMatrix();
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
        glm::vec3 position(CalculatePosition());

        m_ViewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(m_Rotation);
        m_ViewMatrix = glm::inverse(m_ViewMatrix);

        m_ViewDirty = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void
    TrackBallCamera::Pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) {
        glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.03f;

        auto[xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void
    TrackBallCamera::Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) {
        glm::vec3 rotVector = glm::normalize(glm::cross(newMousePosition - oldMousePosition, glm::vec3(0, 0, -2)));

        float rotationAngle =
                glm::acos(std::clamp(glm::dot(glm::normalize(oldMousePosition), glm::normalize(newMousePosition)), -1.0f,
                        1.0f)) * ts.MiliSeconds() * m_RotationSpeed;
        float rotationAngleCos = glm::cos(rotationAngle);
        float rotationAngleSin = glm::sin(rotationAngle);

        glm::quat rotQuat(rotationAngleCos,
                          rotationAngleSin *
                          rotVector);

        Rotate(rotQuat);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::Translate(const glm::vec3 &delta) {
        auto[xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDirection() * delta.x * 0.3f * xSpeed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * 0.3f * ySpeed * m_Distance;
        Zoom(-delta.z, 0.0f);

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::Zoom(float yOffset, float xOffset) {
        m_Distance -= yOffset * ZoomSpeed() * 0.08f;
        if (m_Distance < 1.0f) {
            m_FocalPoint += GetForwardDirection();
            m_Distance = 1.0f;
        }

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TrackBallCamera::OnWindowResize(uint32_t width, uint32_t height) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        SetProjectionRH(45, aspectRatio, 1, -1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 TrackBallCamera::GetUpDirection() const {
        return glm::rotate(m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 TrackBallCamera::GetRightDirection() const {
        return glm::rotate(m_Rotation, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 TrackBallCamera::GetForwardDirection() const {
        return glm::rotate(m_Rotation, glm::vec3(0.0f, 0.0f, -1.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    glm::vec3 TrackBallCamera::CalculatePosition() const {
        return m_FocalPoint - GetForwardDirection() * m_Distance;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    std::pair<float, float> TrackBallCamera::PanSpeed() const {
        float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
        float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

        return {xFactor, yFactor};
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    float TrackBallCamera::ZoomSpeed() const {
        float distance = m_Distance * 0.2f;
        distance = std::max(distance, 0.0f);
        float speed = distance * distance;
        speed = std::min(speed, 100.0f); // max speed = 100
        return speed;
    }
}