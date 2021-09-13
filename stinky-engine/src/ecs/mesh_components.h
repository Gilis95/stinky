//
// Created by christian on 13/10/2020.
//

#pragma once

#include "glm/glm.hpp"
#include "StinkyPrerequisites.h"
#include "core/stinky_memory.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class mesh_component {
    public:
        mesh_component() = default;
        explicit mesh_component(shared_ptr<vertex_array> vertexArray);
        mesh_component(mesh_component &&) = default;
        virtual ~mesh_component() = default;

        mesh_component &operator=(mesh_component &&copy) noexcept {
            vertex_array = copy.vertex_array;

            return *this;
        }

        shared_ptr<vertex_array> vertex_array;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
