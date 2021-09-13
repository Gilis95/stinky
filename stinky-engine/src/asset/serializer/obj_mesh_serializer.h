//
// Created by christian on 7/1/21.
//

#ifndef STINKY_OBJ_MESH_SERIALIZER_H
#define STINKY_OBJ_MESH_SERIALIZER_H

#include "asset/serializer/mesh_serializer.h"

namespace stinky {
    class obj_mesh_serializer : public mesh_serializer {
    public:
        obj_mesh_serializer() = default;
        ~obj_mesh_serializer() override = default;
    public:
        void deserialize(const std::filesystem::path &path, mesh_asset &outMeshAsset) override;
    };
}

#endif //STINKY_OBJ_MESH_SERIALIZER_H
