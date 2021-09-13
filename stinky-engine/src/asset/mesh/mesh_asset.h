//
// Created by christian on 7/1/21.
//

#ifndef STINKY_MESH_ASSET_H
#define STINKY_MESH_ASSET_H

#include "asset/asset.h"

namespace stinky {
    struct asset_metadata;
    class index_buffer;
    class vertex_buffer;
    class vertex_array;
    class mesh_serializer;

    class mesh_asset : public asset {
    public:
        mesh_asset() = default;
        ~mesh_asset() override = default;
    public:
        virtual mesh_serializer& getSerializerImpl() = 0;
    public:
        bool load(const asset_metadata &assetMetadata) override;
    public:
        index_buffer *indexBuffer = nullptr;
        vertex_buffer *vertexBuffer = nullptr;
        vertex_array *vertexArray = nullptr;
    };
}
#endif //STINKY_MESH_ASSET_H
