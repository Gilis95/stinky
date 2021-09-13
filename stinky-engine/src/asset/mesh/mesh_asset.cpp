//
// Created by christian on 7/8/21.
//

#include "asset/asset_metadata.h"
#include "asset/mesh/mesh_asset.h"
#include "asset/serializer/mesh_serializer.h"


namespace stinky {
    bool mesh_asset::load(const asset_metadata& assetMetadata) {
        auto& serializer = getSerializerImpl();
        serializer.deserialize(assetMetadata.file_path, *this);

        return true;
    }
}