//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_MANAGER_H
#define STINKY_ASSET_MANAGER_H

#include <filesystem>
#include <functional>
#include <vector>

#include "core/stinky_memory.h"

namespace stinky {
class uuid;
class asset_handler;
class asset_metadata;
class asset;

class asset_manager {
public:
  asset_manager();

  ~asset_manager();

public:
  static asset_manager &instance();

public:
  bool import_file(const std::string &path);

  void register_directory(const std::string &path);
  void register_file(const std::filesystem::path &file);

  asset* load(const uuid &guid);
public:
  void register_asset_handler(const asset_handler &handler);

private:
  static unique_ptr<asset_manager> _S_instance;

private:
  std::vector<const asset_handler *> _M_handlers;
  std::function<bool(const asset_handler *, const asset_handler *)>
      _M_asset_priority_comparator;
};
} // namespace stinky
#endif // STINKY_ASSET_MANAGER_H
