//
// Created by christian on 10/15/21.
//

#ifndef STINKY_GLTF_MATERIAL_ASSET_H
#define STINKY_GLTF_MATERIAL_ASSET_H

#include "asset/entity/material_asset.h"
namespace stinky {
class gltf_material_asset : public material_asset {
  gltf_material_asset();

  ~gltf_material_asset() override;

public:
  constexpr int get_type() override;
  void load() override;
}
} // namespace stinky
#endif // STINKY_GLTF_MATERIAL_ASSET_H
