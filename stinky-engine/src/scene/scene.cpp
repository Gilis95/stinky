//
// Created by christian on 05/10/2020.
//

#include "scene/scene.h"

#include <Tracy.hpp>
#include <entt/entt.hpp>

#include "asset/asset.h"
#include "asset/asset_manager.h"
#include "asset/entity/scene_asset.h"
#include "camera/camera.h"
#include "core/uuid.h"
#include "ecs/camera_component.h"
#include "ecs/entity.h"
#include "ecs/material_component.h"
#include "ecs/mesh_components.h"
#include "ecs/program_component.h"
#include "ecs/transform_component.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace stinky {

////////////////////////////////////////////////////////////////////////////////
scene::scene(const graphic_layer_abstraction_factory *rendererFactory)
    : _M_renderer(create_scope<renderer>(rendererFactory)) {
  _M_renderer->init();
}

////////////////////////////////////////////////////////////////////////////////
void scene::on_update() {
  camera *camera;

  ZoneScopedN("SceneUpdate")

      auto camerasView = _M_registry.view<camera_component>();

  for (auto cameraView : camerasView) {
    auto &tmpCameraRef = camerasView.get<camera_component>(cameraView);
    ContinueUnless(tmpCameraRef._M_is_primary) camera = tmpCameraRef._M_camera;
  }

  AssertReturnUnless(camera);

  _M_renderer->clear();
  _M_renderer->begin_scene(camera->get_view_matrix(),
                           camera->get_projection_matrix());

  auto meshesGroup = _M_registry.group<mesh_component, transform_component,
                                       program_component, material_component>();

  for (auto mesh : meshesGroup) {
    _M_renderer->draw({meshesGroup.get<mesh_component>(mesh),
                       meshesGroup.get<transform_component>(mesh),
                       meshesGroup.get<program_component>(mesh),
                       meshesGroup.get<material_component>(mesh)});
  }

  _M_renderer->end_scene();
}

////////////////////////////////////////////////////////////////////////////////
void scene::on_close() { _M_registry.clear<>(); }

////////////////////////////////////////////////////////////////////////////////
entity scene::CreateEntity() { return entity(&_M_registry); }

////////////////////////////////////////////////////////////////////////////////
void scene::each(std::function<void(entity &entt)> func) {

  _M_registry.each([this, &func](const auto &it) -> void {
    entity entt(&_M_registry, it);
    func(entt);
  });
}

////////////////////////////////////////////////////////////////////////////////
bool scene::load_scene(const uuid& guid)
{
  auto& _instance = asset_manager::instance();

  auto* _asset = _instance.load(guid);
  ReturnUnless(_asset, false);

  auto* _scene_asset = _asset->as<scene_asset>();
  ReturnUnless(_scene_asset, false);



  return true;
}

} // namespace stinky