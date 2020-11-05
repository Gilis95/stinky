//
// Created by christian on 13/10/2020.
//

#pragma once

#include "glm/glm.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class MeshComponent {
    public:
        MeshComponent() = default;
        explicit MeshComponent(unsigned verticesCount, glm::vec4 *vertices, unsigned indicesCount, unsigned *indices);
        MeshComponent(MeshComponent &&) = default;
        virtual ~MeshComponent() = default;

        MeshComponent &operator=(MeshComponent &&copy) noexcept {
            vertices = copy.vertices;
            verticesCount = copy.verticesCount;

            indices = copy.indices;
            indicesCount = copy.indicesCount;

            return *this;
        }

        unsigned verticesCount;
        glm::vec4 *vertices;

        unsigned indicesCount;
        unsigned *indices;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
