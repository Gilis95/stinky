//
// Created by christian on 7/1/21.
//

#ifndef STINKY_MESH_SERIALIZER_H
#define STINKY_MESH_SERIALIZER_H

#include <filesystem>

namespace stinky {
    class mesh_asset;

    class mesh_serializer {
    public:
        mesh_serializer() = default;

        virtual ~mesh_serializer() = default;

        virtual void deserialize(const std::filesystem::path &path, mesh_asset &outMeshAsset) = 0;
    };
}

#endif //STINKY_MESH_SERIALIZER_H
