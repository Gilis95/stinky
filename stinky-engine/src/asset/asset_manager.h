//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_MANAGER_H
#define STINKY_ASSET_MANAGER_H

#include <unordered_map>

#include "asset/asset_metadata.h"
#include "asset/asset_storage_factory.h"
#include "core/stinky_memory.h"
#include "core/uuid.h"

namespace stinky {
    class asset_manager {
    public:
        using AssetRegistry = std::unordered_map<uuid, asset_metadata>;
    public:
        asset_manager();

        ~asset_manager();

    public:
        void load_directory(const std::string &directory);
        bool read_asset_metadata(const std::filesystem::path &file);

        void import_directory(const std::string &directory);
        bool import_file(const std::filesystem::path &file);

        bool load_asset(const uuid &guid);
    public:
        template<typename asset_type>
        std::optional<std::reference_wrapper<const asset_type>> get_asset(const uuid &guid) const {
            return asset_storage_factory<asset_type>::storage->get(guid);
        }

    protected:
        static bool loadObjMeshAsset(const asset_metadata &assetMetadata);
        static bool loadMaterialAsset(const asset_metadata &assetMetadata);
        static bool loadProgramAsset(const asset_metadata &assetMetadata);
        static bool loadTextureAsset(const asset_metadata &assetMetadata);

        bool loadSceneAsset(const asset_metadata &assetMetadata);

    private:
        AssetRegistry m_AssetRegistry;
        std::function<bool(const asset_metadata &assetMetadata)> m_AssetLoaders[5];
    };
}
#endif //STINKY_ASSET_MANAGER_H
