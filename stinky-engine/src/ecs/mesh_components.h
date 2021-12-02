//
// Created by christian on 13/10/2020.
//

#pragma once

#include "core/stinky_memory.h"
#include "glm/glm.hpp"
#include "stinky_prerequisites.h"

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
    _M_vertex_array = copy._M_vertex_array;

    return *this;
  }

  shared_ptr<vertex_array> _M_vertex_array;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
