//
// Created by christian on 9/16/21.
//

#ifndef STINKY_MESHASSET_H
#define STINKY_MESHASSET_H

#include "asset/asset.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>

namespace stinky {
class mesh_asset : public asset {
public:
  struct vertex {
    glm::vec3 position{0,0,0};
    glm::vec2 tex_coord{0,0};
    glm::vec3 normal{0,0,0};
    glm::vec4 tangent{0,0,0,0};
  };

  struct sub_mesh{
    std::vector<vertex> vertices;
  };
public:
  mesh_asset() = default;

  ~mesh_asset() override = default;

public:
  constexpr int get_type() override { return 1000; }

public:
  std::vector<sub_mesh> sub_meshes;
};
} // namespace stinky

#endif // STINKY_MESHASSET_H
