//
// Created by christian on 9/13/21.
//

#ifndef STINKY_ASSETHANDLER_H
#define STINKY_ASSETHANDLER_H

#include <string>
#include <filesystem>

namespace stinky {
class asset_handler {
public:
  explicit asset_handler(int priority);
  virtual ~asset_handler();

public:
  [[nodiscard]] virtual bool
  can_handle(const std::string &asset_path) const = 0;

  [[nodiscard]] virtual bool import(const std::string &asset_path) const {
    return true;
  }

  virtual void register_asset(const std::filesystem::path &asset) const {}
public:
  int priority = 0;
};
} // namespace stinky
#endif // STINKY_ASSETHANDLER_H
