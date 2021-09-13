//
// Created by christian on 07/10/2020.
//
#pragma once

#include "glm/glm.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class transform_component {
    public:
        transform_component() = default;
        explicit transform_component(glm::vec3 &translation, glm::vec3 &scale, glm::vec3 &rotation);
        explicit transform_component(glm::vec3 &&translation, glm::vec3 &&scale, glm::vec3 &&rotation);
        transform_component(transform_component &&) = default;

        ~transform_component() = default;

        transform_component &operator=(transform_component &&copy) noexcept {
            translation = copy.translation;
            scale = copy.scale;
            rotation = copy.rotation;

            return *this;
        };

        glm::vec3 translation;
        glm::vec3 scale;
        glm::vec3 rotation;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
