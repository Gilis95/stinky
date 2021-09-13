//
// Created by christian on 7/8/21.
//

#include "asset/mesh/obj_mesh_asset.h"

namespace stinky {
    obj_mesh_asset::obj_mesh_asset() = default;
    obj_mesh_asset::~obj_mesh_asset() = default;

    mesh_serializer &obj_mesh_asset::getSerializerImpl() {
        return m_Serializer;
    }
}

