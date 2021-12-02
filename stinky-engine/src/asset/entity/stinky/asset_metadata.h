// entity
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_METADATA_H
#define STINKY_ASSET_METADATA_H

#include "core/uuid.h"
#include <filesystem>

namespace stinky {
class asset_handler;

class asset_metadata {
public:
  explicit asset_metadata(const std::string &asset_path);
  asset_metadata(asset_metadata&& _asset_metadata) noexcept;
  ~asset_metadata();

public:
  void load(const std::string &asset_path);

public:
  uuid guid{0};
  std::filesystem::path asset_path;
  bool is_loaded = false;
};
} // namespace stinky
#endif // STINKY_ASSET_METADATA_H
