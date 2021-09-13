//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_METADATA_H
#define STINKY_ASSET_METADATA_H

#include <filesystem>
#include "asset/asset_types.h"
#include "core/uuid.h"

namespace stinky{
    struct asset_metadata {
        uuid guid{0};
        std::filesystem::path file_path;
        asset_type asset_type;
        bool is_loaded = false;
    };
}
#endif //STINKY_ASSET_METADATA_H
