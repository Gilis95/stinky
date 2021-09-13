//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_EXTENSIONS_H
#define STINKY_ASSET_EXTENSIONS_H

#include <unordered_map>
#include <string>
#include "asset/asset_types.h"

namespace stinky {

    inline static std::unordered_map <std::string, const asset_type> _S_asset_extension_map =
            {
                    {".stinky", asset_type::Scene},
//                    {".fbx",    AssetType::Mesh},
//                    {".gltf",   AssetType::Mesh},
//                    {".glb",    AssetType::Mesh},
                    {".obj",    asset_type::OBJ_Mesh},
                    {".mtl",    asset_type::Material},
                    {".png",    asset_type::Texture},
            };
}
#endif //STINKY_ASSET_EXTENSIONS_H
