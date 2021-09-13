//
// Created by christian on 23/08/2020.
//

#pragma once

#include <glm/glm.hpp>
#include "camera/camera.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class orthographic_camera : public camera {
    public:
        orthographic_camera(float left, float right, float bottom, float top);

        void translate(const glm::vec3 &delta);
        void rotate(float delta);
        void set_projection(float left, float right, float bottom, float top);

        void SetRotation(float rotation) {
            m_Rotation = rotation;
            m_ViewDirty = true;
        }

        [[nodiscard]] float GetRotation() const { return m_Rotation; }

    protected:
        void recalculate_view_projection_matrix() override;
        void recalculate_view_matrix() override;
    private:
        float m_Rotation;

        bool m_ViewDirty;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////