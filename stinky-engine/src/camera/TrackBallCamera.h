//
// Created by christian on 29/08/2020.
//

#pragma once

#include <glm/detail/type_quat.hpp>
#include "camera/Camera.h"
#include "PerspectiveCameraController.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class TrackBallCamera : public Camera, public PerspectiveCameraController {
    public:
        explicit TrackBallCamera(uint32_t screenWidth = 1280, uint32_t screenHeight = 720, float fov = 45.0f,
                                 float zNear = 1.0f, float zFar = -1.0f);

        ~TrackBallCamera() override = default;

        void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

        void SetRotation(const glm::quat &rot);

        [[nodiscard]] glm::quat GetRotation() const;

        // Rotate the camera by some amount.
        void Rotate(const glm::quat &rot);

    public:
        // Controller functions
        void Pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) override;
        void Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) override;
        void Translate(const glm::vec3 &delta) override;
        void Zoom(float yOffset, float xOffset);
        void OnWindowResize(uint32_t width, uint32_t height) override;
        // Controller functions
    protected:
        void RecalculateViewProjectionMatrix() override;
        void RecalculateViewMatrix() override;
    private:
        [[nodiscard]] glm::vec3 GetUpDirection() const;
        [[nodiscard]] glm::vec3 GetRightDirection() const;
        [[nodiscard]] glm::vec3 GetForwardDirection() const;
        [[nodiscard]] glm::vec3 CalculatePosition() const;

        [[nodiscard]] float                     ZoomSpeed() const;
        [[nodiscard]] std::pair<float, float>   PanSpeed() const;
    private:
        float m_Distance;
        glm::quat m_Rotation;

        uint32_t m_ViewportWidth, m_ViewportHeight;

        glm::vec3 m_FocalPoint;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////