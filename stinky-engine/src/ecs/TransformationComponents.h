//
// Created by christian on 07/10/2020.
//
#pragma once

#include "glm/glm.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class TranslateComponent {
    public:
        explicit TranslateComponent(glm::vec3 &translation);
        explicit TranslateComponent(glm::vec3 &&translation);
        TranslateComponent(TranslateComponent &&) = default;

        ~TranslateComponent() = default;

        TranslateComponent &operator=(TranslateComponent &&copy) noexcept {
            translation = copy.translation;
            return *this;
        };

        glm::vec3 translation;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class ScaleComponent {
    public:
        explicit ScaleComponent(glm::vec3 &amount);
        explicit ScaleComponent(glm::vec3 &&amount);
        ScaleComponent(ScaleComponent &&) = default;

        ~ScaleComponent() = default;

        ScaleComponent &operator=(ScaleComponent &&copy) noexcept {
            scale = copy.scale;

            return *this;
        }

        glm::vec3 scale;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
