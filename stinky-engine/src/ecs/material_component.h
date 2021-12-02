//
// Created by christian on 19/10/2020.
//
#pragma once

#include <glm/vec4.hpp>
#include <string>

#include "core/stinky_memory.h"
#include "stinky_prerequisites.h"
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
enum class material_type { SOLID, TEXTURED };

/////////////////////////////////////////////////////////////////////////////////////////
enum class material_flag { DepthTest, TwoSided };

/////////////////////////////////////////////////////////////////////////////////////////
class material_component {
public:
  typedef std::unordered_map<material_flag, bool> material_flags;

public:
  explicit material_component(shared_ptr<texture> material,
                              bool depthTest = true);
  explicit material_component(glm::vec4 colour, bool depthTest = true);
  material_component(material_component &&path) noexcept = default;

  ~material_component() = default;

  material_component &operator=(material_component &&copy) noexcept {
    material = copy.material;
    colour = copy.colour;
    type = copy.type;
    flags = copy.flags;
    return *this;
  };

  bool get_flag(material_flag flag) const;

  shared_ptr<texture> material;
  glm::vec4 colour{};
  material_type type;
  material_flags flags;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////