//
// Created by christian on 9/13/21.
//
#include "asset/handler/gltf/gltf_handler.h"
#include "asset/asset_manager.h"
#include "stinkypch.h"

#define TINYGLTF_NOEXCEPTION
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#define TINYGLTF_NO_INCLUDE_STB_IMAGE_WRITE

#define TINYGLTF_USE_CPP14
#include <asset/asset_storage.h>
#include <filesystem>
#include <tiny_gltf.h>
#include <vendor/stb_image/stb_image.h>
#include <vendor/stb_image/stb_image_write.h>

#include "asset/entity/gltf/gltf_mesh_asset.h"
#include "core/uuid.h"

namespace stinky {

std::string gltf_handler::_S_extension = ".gltf";

/////////////////////////////////////////////////////////////////////////////////////////
gltf_handler::gltf_handler()
    : asset_handler(1), _M_gltf(create_scope<tinygltf::TinyGLTF>()) {
  asset_manager::instance().register_asset_handler(*this);
}

gltf_handler::~gltf_handler() = default;

/////////////////////////////////////////////////////////////////////////////////////////
bool gltf_handler::can_handle(const std::string &asset_path) const {
  return !asset_path.compare(asset_path.length() - _S_extension.length(),
                             _S_extension.length(), _S_extension);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool gltf_handler::import(const std::string &asset_path) const {
  tinygltf::Model _data;
  std::string err;
  std::string warn;
  _M_gltf->LoadASCIIFromFile(&_data, &err, &warn, asset_path);

  ReturnUnless(err.empty(), false);

  if (!warn.empty()) {
    STINKY_WARN(warn);
  }

  int ix = 0;
  for (auto &mesh : _data.meshes) {
    uuid _guid;
    mesh.extensions["id"] = tinygltf::Value(static_cast<uint64_t>(_guid));

    asset_storage::instance().emplace(
        std::move(_guid),
        std::move(create_scope<gltf_mesh_asset>(_data, ix++)));
  }

  for (auto &material : _data.materials) {
    material.extensions["id"] = tinygltf::Value(static_cast<uint64_t>(uuid()));
  }

  for (auto &scene : _data.scenes) {
    scene.extensions["id"] = tinygltf::Value(static_cast<uint64_t>(uuid()));
  }

  _M_gltf->WriteGltfSceneToFile(&_data, asset_path, /*embedImages*/ false,
                                /*embedBuffers*/ false, /*prettyPrint*/ true,
                                /*writeBinary*/ false);

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void gltf_handler::register_asset(const std::filesystem::path &asset) const {
  tinygltf::Model data;
  std::string err;
  std::string warn;
  _M_gltf->LoadASCIIFromFile(&data, &err, &warn, asset);

  int ix = 0;
  for (auto _mesh : data.meshes) {
    create_scope<gltf_mesh_asset>(data, ix++);
  }

  ReturnUnless(err.empty());

  if (!warn.empty()) {
    STINKY_WARN(warn);
  }
}
} // namespace stinky