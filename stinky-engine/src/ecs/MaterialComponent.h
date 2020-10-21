//
// Created by christian on 19/10/2020.
//
#pragma once

#include <string>
#include <glm/vec4.hpp>

#include "core/StinkyMacros.h"
#include "StinkyPrerequisites.h"
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    enum class MaterialType {
        SOLID, TEXTURED
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class MaterialComponent {
    public:
        explicit MaterialComponent(Ref<Texture> material);
        explicit MaterialComponent(glm::vec4 colour);
        MaterialComponent(MaterialComponent &&path) noexcept = default;

        ~MaterialComponent() = default;

        MaterialComponent &operator=(MaterialComponent &&copy) noexcept {
            material = copy.material;
            colour = copy.colour;
            type = copy.type;
            return *this;
        };

        Ref<Texture> material;
        glm::vec4 colour{};
        MaterialType type;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////