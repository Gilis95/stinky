//
// Created by christian on 12/10/2020.
//

#pragma once

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Camera {
    public:
        explicit Camera(glm::mat4 &projectionMatrix);
        explicit Camera(glm::mat4 &&projectionMatrix);

        Camera(Camera &&camera) noexcept;

        virtual ~Camera() = default;

        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

        [[nodiscard]] const glm::mat4 &GetViewMatrix() {
            RecalculateViewMatrix();
            return m_ViewMatrix;
        }

        void SetViewMatrix(const glm::mat4& viewMatrix) {
            m_ViewMatrix = viewMatrix;
        }

        [[nodiscard]] const glm::mat4 &GetViewProjectionMatrix() {
            RecalculateViewProjectionMatrix();
            return m_ViewProjectionMatrix;
        }

        void SetPosition(const glm::vec3 &pos) {
            m_Position = pos;
            m_ViewDirty = true;
        }

        [[nodiscard]]const glm::vec3 &GetPosition() const {
            return m_Position;
        }

    protected:
        virtual void RecalculateViewProjectionMatrix() = 0;

        virtual void RecalculateViewMatrix() = 0;

    protected:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix{1.0f};
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position{0.0f};

        bool m_ViewDirty = false;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////