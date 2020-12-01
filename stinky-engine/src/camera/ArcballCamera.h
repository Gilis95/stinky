//
// Created by christian on 29/08/2020.
//

#pragma once

#include <glm/detail/type_quat.hpp>
#include "camera/Camera.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class ArcballCamera : public Camera {
    public:
        explicit ArcballCamera(int screenWidth = 1280, int screenHeight = 720, float fov = 45.0f,
                               float zNear = 1.0f, float zFar = -1.0f);
        ~ArcballCamera() override = default;


        void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

        // Translate the camera by some amount. If local is TRUE (default) then the translation should
        // be applied in the local-space of the camera. If local is FALSE, then the translation is
        // applied in world-space.
        void Translate(const glm::vec3 &delta, bool local = true);

        void SetRotation(const glm::quat &rot);
        [[nodiscard]] glm::quat GetRotation() const;

        void SetEulerAngles(const glm::vec3 &eulerAngles);
        [[nodiscard]] glm::vec3 GetEulerAngles() const;

        // Rotate the camera by some amount.
        void Rotate(const glm::quat &rot);
    protected:
        void RecalculateViewProjectionMatrix() override;
        void RecalculateViewMatrix() override;
    protected:
        glm::quat m_Rotation;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////