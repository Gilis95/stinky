//
// Created by christian on 07/10/2020.
//

#pragma once

#include <entt/entity/registry.hpp>

#include "ecs/entity.h"
#include "renderer/renderer.h"
#include "stinky_prerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class entity;

class scene {
public:
  explicit scene(const graphic_layer_abstraction_factory *rendererFactory);
  ~scene() = default;

  void on_update();

  void on_close();

  /** NOTE:: maybe in separate class */
  entity CreateEntity();

  void each(std::function<void(entity &entt)> func);

private:
  entt::registry _M_registry;
  unique_ptr<renderer> _M_renderer;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
