//
// Created by christian on 13/10/2020.
//

#include "glm/glm.hpp"
#include "mesh_components.h"

#include <utility>
#include "gla/vertex_array.h"


namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    mesh_component::mesh_component(shared_ptr<vertex_array> vertexArray)
            : vertex_array(std::move(vertexArray)) {
    }

}