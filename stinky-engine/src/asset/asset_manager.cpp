//
// Created by christian on 7/1/21.
//

#include "asset/asset_extensions.h"
#include "asset/asset_manager.h"
#include "asset/mesh/obj_mesh_asset.h"
#include "core/project.h"
#include "stinkypch.h"

namespace stinky {
    template<typename _T_asset> asset_storage<_T_asset> asset_storage_factory<_T_asset>::storage;

    /////////////////////////////////////////////////////////////////////////////////////////
    asset_manager::asset_manager()
            : m_AssetLoaders{
            [this](const asset_metadata &metadata) { return loadObjMeshAsset(metadata); },
            [this](const asset_metadata &metadata) { return loadMaterialAsset(metadata); },
            [this](const asset_metadata &metadata) { return loadProgramAsset(metadata); },
            [this](const asset_metadata &metadata) { return loadTextureAsset(metadata); },
            [this](const asset_metadata &metadata) { return loadSceneAsset(metadata); }
    } {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    asset_manager::~asset_manager() = default;

    /////////////////////////////////////////////////////////////////////////////////////////
    void asset_manager::load_directory(const std::string &directory) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::read_asset_metadata(const std::filesystem::path &file) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void asset_manager::import_directory(const std::string &directory) {
        auto dir = std::filesystem::directory_iterator(std::filesystem::path(directory));
        for (auto &file : dir) {
            if (file.is_directory()) {
                import_directory(file.path());
            } else {
                import_file(file.path());
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::import_file(const std::filesystem::path &file) {
        uuid guid;
        {
            int maxRetries = 10; // TODO:: Must be project setting
            while (m_AssetRegistry.find(guid) != m_AssetRegistry.end() && maxRetries > 0) {
                guid = uuid();
                --maxRetries;
            }
            ReturnUnless(maxRetries > 0, false)
        }

        auto assetType = _S_asset_extension_map.find(file.extension());
        ReturnIf(assetType == _S_asset_extension_map.end(), false)

        m_AssetRegistry.emplace(guid, asset_metadata{guid, file, assetType->second});
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::load_asset(const uuid &guid) {
        auto assetMetadata = m_AssetRegistry.find(guid);
        ReturnIf(assetMetadata == m_AssetRegistry.end(), false);

        bool isLoaded = m_AssetLoaders[static_cast<int>(assetMetadata->second.asset_type)](assetMetadata->second);
        assetMetadata->second.is_loaded = isLoaded;
        return isLoaded;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::loadObjMeshAsset(const asset_metadata &assetMetadata) {
        return asset_storage_factory<mesh_asset>::storage.load<obj_mesh_asset>(assetMetadata);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::loadMaterialAsset(const asset_metadata &assetMetadata) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::loadProgramAsset(const asset_metadata &assetMetadata) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::loadTextureAsset(const asset_metadata &assetMetadata) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool asset_manager::loadSceneAsset(const asset_metadata &assetMetadata) {

    }
}
