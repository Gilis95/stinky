//
// Created by christian on 19/10/2020.
//
#pragma once

#include <string>
#include <glm/vec4.hpp>

#include "core/StinkyMemory.h"
#include "StinkyPrerequisites.h"
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    enum class MaterialType {
        SOLID, TEXTURED
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    enum class MaterialFlag {
        DepthTest, TwoSided
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class MaterialComponent {
    public:
        typedef std::unordered_map<MaterialFlag, bool> Flags;
    public:
        explicit MaterialComponent(Ref<Texture> material, bool depthTest = true);
        explicit MaterialComponent(glm::vec4 colour, bool depthTest = true);
        MaterialComponent(MaterialComponent &&path) noexcept = default;

        ~MaterialComponent() = default;

        MaterialComponent &operator=(MaterialComponent &&copy) noexcept {
            material = copy.material;
            colour = copy.colour;
            type = copy.type;
            flags = copy.flags;
            return *this;
        };

        bool GetFlag(MaterialFlag flag) const;

        Ref<Texture> material;
        glm::vec4 colour{};
        MaterialType type;
        Flags flags;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////