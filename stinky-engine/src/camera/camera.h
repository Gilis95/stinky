//
// Created by christian on 12/10/2020.
//

#pragma once

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class camera {
    public:
        explicit camera(glm::mat4 &projectionMatrix);
        explicit camera(glm::mat4 &&projectionMatrix);

        camera(camera &&camera) noexcept;

        virtual ~camera() = default;

        [[nodiscard]] const glm::mat4 &get_projection_matrix() const { return _M_projection_matrix; }

        [[nodiscard]] const glm::mat4 &get_view_matrix() {
            recalculate_view_matrix();
            return _M_view_matrix;
        }

        void set_view_matrix(const glm::mat4& viewMatrix) {
            _M_view_matrix = viewMatrix;
        }

        [[nodiscard]] const glm::mat4 &get_view_projection_matrix() {
            recalculate_view_projection_matrix();
            return _M_view_projection_matrix;
        }

        void set_position(const glm::vec3 &pos) {
            _M_position = pos;
            _M_view_dirty = true;
        }

        [[nodiscard]]const glm::vec3 &get_position() const {
            return _M_position;
        }

    protected:
        virtual void recalculate_view_projection_matrix() = 0;

        virtual void recalculate_view_matrix() = 0;

    protected:
        glm::mat4 _M_projection_matrix;
        glm::mat4 _M_view_matrix{1.0f};
        glm::mat4 _M_view_projection_matrix;

        glm::vec3 _M_position{0.0f};

        bool _M_view_dirty = false;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////