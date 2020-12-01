//
// Created by christian on 07/10/2020.
//
#pragma once

#include "glm/glm.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class TransformComponent {
    public:
        TransformComponent() = default;
        explicit TransformComponent(glm::vec3 &translation, glm::vec3 &scale, glm::vec3 &rotation);
        explicit TransformComponent(glm::vec3 &&translation, glm::vec3 &&scale, glm::vec3 &&rotation);
        TransformComponent(TransformComponent &&) = default;

        ~TransformComponent() = default;

        TransformComponent &operator=(TransformComponent &&copy) noexcept {
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
