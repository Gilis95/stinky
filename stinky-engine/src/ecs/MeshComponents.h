//
// Created by christian on 13/10/2020.
//

#pragma once

#include "glm/glm.hpp"

namespace stinky {
/** ####################################### Mesh Component Interfaces #######################################*/
    class MeshVertexComponent {
    public:
        MeshVertexComponent(unsigned verticesCount, glm::vec4 *vertices);
        MeshVertexComponent(MeshVertexComponent &&) = default;
        virtual ~MeshVertexComponent() = default;

        MeshVertexComponent &operator=(MeshVertexComponent &&copy) noexcept {
            vertices = copy.vertices;
            verticesCount = copy.verticesCount;
            return *this;
        }

        unsigned verticesCount;
        glm::vec4 *vertices;
    };

    class MeshIndexComponent {
    public:
        MeshIndexComponent(unsigned indicesCount, unsigned *indices);
        MeshIndexComponent(MeshIndexComponent &&) = default;
        virtual ~MeshIndexComponent() = default;

        MeshIndexComponent &operator=(MeshIndexComponent &&copy) noexcept {
            indices = copy.indices;
            indicesCount = copy.indicesCount;
            return *this;
        }

        unsigned indicesCount;
        unsigned *indices;
    };

/** ####################################### Mesh Component Interfaces #######################################*/
}