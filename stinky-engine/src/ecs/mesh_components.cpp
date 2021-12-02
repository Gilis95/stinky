//
// Created by christian on 13/10/2020.
//

#include "mesh_components.h"
#include "glm/glm.hpp"

#include "gla/vertex_array.h"
#include <utility>

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
mesh_component::mesh_component(shared_ptr<vertex_array> vertexArray)
    : _M_vertex_array(std::move(vertexArray)) {}

} // namespace stinky