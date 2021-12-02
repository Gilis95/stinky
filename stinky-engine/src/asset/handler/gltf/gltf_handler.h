//
// Created by christian on 9/13/21.
//

#ifndef STINKY_GLTF_HANDLER_H
#define STINKY_GLTF_HANDLER_H

#include "asset/handler/asset_handler.h"
#include "core/stinky_memory.h"

namespace tinygltf {
class TinyGLTF;
}

namespace stinky {
class gltf_handler : public asset_handler {
public:
  gltf_handler();

  ~gltf_handler() override;

public:
  [[nodiscard]] bool can_handle(const std::string &asset_path) const override;

  [[nodiscard]] bool import(const std::string &asset_path) const override;

  void register_asset(const std::filesystem::path &asset) const override;
private:
  unique_ptr<tinygltf::TinyGLTF> _M_gltf;
  static std::string _S_extension;
};
} // namespace stinky
#endif // STINKY_GLTF_HANDLER_H
