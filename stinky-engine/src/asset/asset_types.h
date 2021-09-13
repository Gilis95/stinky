//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_TYPES_H
#define STINKY_ASSET_TYPES_H

#include "asset/asset.h"
#include "src/asset/mesh/mesh_asset.h"

namespace stinky {
    enum class asset_type : int {
        OBJ_Mesh = 0,
        Material,
        Program,
        Texture,
        Scene
    };
}
#endif //STINKY_ASSET_TYPES_H
