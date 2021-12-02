//
// Created by christian on 10/8/21.
//

#ifndef STINKY_MATERIAL_ASSET_H
#define STINKY_MATERIAL_ASSET_H

#include "asset/asset.h"

namespace stinky {
class material_asset : public asset {
public:
  material_asset() = default

  ~material_asset() override = default;

public:
  constexpr int get_type() override{return 2000}
};
} // namespace stinky
#endif // STINKY_MATERIAL_ASSET_H
