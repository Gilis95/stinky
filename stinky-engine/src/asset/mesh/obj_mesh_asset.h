//
// Created by christian on 7/8/21.
//

#ifndef STINKY_OBJ_MESH_ASSET_H
#define STINKY_OBJ_MESH_ASSET_H

#include "asset/serializer/obj_mesh_serializer.h"
#include "asset/mesh/mesh_asset.h"

namespace stinky {
    class obj_mesh_asset : public mesh_asset {
    public:
        obj_mesh_asset();
        ~obj_mesh_asset() override;
    public:
        mesh_serializer& getSerializerImpl() override;
    private:
        obj_mesh_serializer m_Serializer;
    };
}
#endif //STINKY_OBJ_MESH_ASSET_H
