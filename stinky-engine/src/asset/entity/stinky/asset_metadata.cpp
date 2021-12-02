//
// Created by christian on 10/20/21.
//
#include "asset/entity/stinky/asset_metadata.h"
#include "core/stinky_logger.h"
#include <yaml-cpp/yaml.h>

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
asset_metadata::asset_metadata(const std::string &_asset_path) : asset_path(_asset_path) {
//  load(asset_path);
}

/////////////////////////////////////////////////////////////////////////////////////////
asset_metadata::asset_metadata(asset_metadata &&_asset_metadata) noexcept
    : guid(std::move(_asset_metadata.guid)),
      asset_path(std::move(_asset_metadata.asset_path)),
      is_loaded(_asset_metadata.is_loaded) {}

/////////////////////////////////////////////////////////////////////////////////////////
asset_metadata::~asset_metadata() = default;

/////////////////////////////////////////////////////////////////////////////////////////
void asset_metadata::load(const std::string &_asset_path) {
  try {
    YAML::Node parsed_file = YAML::LoadFile(_asset_path);

    guid = parsed_file["guid"].as<uuid>();
    asset_path = parsed_file["path"].as<std::string>();
  } catch (const YAML::BadFile &e) {
    STINKY_ERROR(e.msg);
  }
}
} // namespace stinky