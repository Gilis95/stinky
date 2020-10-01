//
// Created by christian on 23/08/2020.
//

#pragma once

#include <glm/glm.hpp>

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void Translate(const glm::vec3 &delta);
        void Rotate(float delta);
        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3 &position) {
            m_Position = position;
            m_ViewDirty = true;
        }

        void SetRotation(float rotation) {
            m_Rotation = rotation;
            m_ViewDirty = true;
        }

        [[nodiscard]] const glm::vec3 &GetPosition() const { return m_Position; }

        [[nodiscard]] float GetRotation() const { return m_Rotation; }

        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

        [[nodiscard]] const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }

        [[nodiscard]] const glm::mat4 &
        GetViewProjectionMatrix() {
            RecalculateViewMatrix();
            return m_ViewProjectionMatrix;
        }

    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        float m_Rotation;

        bool m_ViewDirty;
    };
}