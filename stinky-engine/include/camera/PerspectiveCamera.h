//
// Created by christian on 29/08/2020.
//

#pragma once

#include "stinkypch.h"

namespace stinky {
    class PerspectiveCamera {
    public:
        PerspectiveCamera(int screenWidth = 1280, int screenHeight = 720, float fov = 1280.0f / 720.0f,
                          float zNear = 100.0f, float zFar = -100.0f);

        void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

        void ApplyViewMatrix();

        void SetPosition(const glm::vec3 &pos);
        [[nodiscard]] glm::vec3 GetPosition() const;

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

        glm::mat4 GetProjectionMatrix();
        glm::mat4 GetViewMatrix();
        glm::mat4 GetViewProjectionMatrix();

    protected:
        void RecalculateViewMatrix();

    protected:

        glm::vec4 m_Viewport;

        glm::vec3 m_Position;
        glm::quat m_Rotation;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

    private:
        bool m_ViewDirty;
    };
}
