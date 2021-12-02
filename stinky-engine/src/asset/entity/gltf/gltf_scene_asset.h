//
// Created by christian on 10/15/21.
//

#ifndef STINKY_GLTF_SCENE_ASSET_H
#define STINKY_GLTF_SCENE_ASSET_H

#include "asset/entity/scene_asset.h"

namespace stinky {
class gltf_scene_asset : public scene_asset {
public:
  gltf_scene_asset();
  virtual ~gltf_scene_asset();

public:
  constexpr int get_type() override;
  void load() override;
};
} // namespace stinky

#endif // STINKY_GLTF_SCENE_ASSET_H
