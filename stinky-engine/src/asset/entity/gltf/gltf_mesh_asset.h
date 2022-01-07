//
// Created by christian on 10/15/21.
//

#ifndef STINKY_GLTF_MESH_ASSET_H
#define STINKY_GLTF_MESH_ASSET_H

#include "asset/entity/mesh_asset.h"

namespace tinygltf {
class Model;
}

namespace stinky {
class gltf_mesh_asset : public mesh_asset {
public:
  gltf_mesh_asset(const tinygltf::Model &model, int meshIndex);

  ~gltf_mesh_asset() override;

public:
  constexpr int get_type() override { return mesh_asset::get_type() + 1; }
  void load() override;
  void deserialize(const tinygltf::Model &_model, int meshIndex);
  void serialize(const tinygltf::Model &_model, int meshIndex) const;
};

} // namespace stinky

#endif // STINKY_GLTF_MESH_ASSET_H
