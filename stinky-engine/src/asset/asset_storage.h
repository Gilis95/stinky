//
// Created by christian on 6/30/21.
//

#ifndef STINKY_ASSET_STORAGE_H
#define STINKY_ASSET_STORAGE_H

#include <optional>
#include <unordered_map>
#include "asset/asset_metadata.h"
#include "core/stinky_macros.h"
#include "core/stinky_memory.h"

namespace stinky {
    template<class AssetType>
    class asset_storage {
    public:
        asset_storage() = default;
        ~asset_storage() = default;
    public:
        std::optional<std::reference_wrapper<const AssetType>> get(const uuid &guid) const {
            auto element = storage.find(guid);

            ReturnIf(element == storage.end(), std::nullopt)

            return {std::reference_wrapper<const AssetType>(**element)};
        }

        template<class AssetTypeChild = AssetType>
        bool load(const asset_metadata &assetMetadata) {
            unique_ptr<AssetTypeChild> asset = CreateScope<AssetTypeChild>();

            bool result = asset->load(assetMetadata);
            if (result) {
                storage.emplace(assetMetadata.guid, std::move(asset));
            }

            return result;
        }

    private:
        std::unordered_map<uuid, unique_ptr<AssetType>> storage;
    };
}
#endif //STINKY_ASSET_STORAGE_H
