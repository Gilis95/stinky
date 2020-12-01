//
// Created by christian on 23/08/2020.
//

#pragma once

#include <glm/glm.hpp>
#include "camera/Camera.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void Translate(const glm::vec3 &delta);
        void Rotate(float delta);
        void SetProjection(float left, float right, float bottom, float top);

        void SetRotation(float rotation) {
            m_Rotation = rotation;
            m_ViewDirty = true;
        }

        [[nodiscard]] float GetRotation() const { return m_Rotation; }

    protected:
        void RecalculateViewProjectionMatrix() override;
        void RecalculateViewMatrix() override;
    private:
        float m_Rotation;

        bool m_ViewDirty;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////