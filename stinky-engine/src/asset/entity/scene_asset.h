//
// Created by christian on 10/8/21.
//

#ifndef STINKY_SCENE_ASSET_H
#define STINKY_SCENE_ASSET_H

#include "asset/asset.h"
#include <vector>

namespace stinky {
class uuid;

class scene_asset : public asset {
public:
  scene_asset();
  virtual ~scene_asset();

public:
  constexpr int get_type() override { return 1; }

private:
  std::vector<uuid> meshes;
  std::vector<uuid> materials;
};
} // namespace stinky
#endif // STINKY_SCENE_ASSET_H
