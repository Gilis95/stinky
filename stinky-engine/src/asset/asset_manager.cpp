//
// Created by christian on 7/1/21.
//

#include <memory>

#include "asset/asset.h"
#include "asset/asset_manager.h"
#include "asset/asset_storage.h"
#include "asset/handler/asset_handler.h"
#include "core/project.h"
#include "stinkypch.h"

namespace stinky {
unique_ptr<asset_manager> asset_manager::_S_instance;

/////////////////////////////////////////////////////////////////////////////////////////
asset_manager::asset_manager()
    : _M_asset_priority_comparator([](const asset_handler *handler1,
                                      const asset_handler *handler2) -> bool {
        ReturnUnless(handler1, false)
                ReturnUnless(handler2, true) return handler1->priority >
            handler2->priority; // highest priority first
      }) {}

/////////////////////////////////////////////////////////////////////////////////////////
asset_manager::~asset_manager() = default;

/////////////////////////////////////////////////////////////////////////////////////////
asset_manager &asset_manager::instance() {
  if (_S_instance == nullptr) {
    _S_instance = std::make_unique<asset_manager>();
  }

  return *_S_instance;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool asset_manager::import_file(const std::string &asset_path) {
  return std::ranges::any_of(
      _M_handlers.begin(), _M_handlers.end(),
      [&asset_path](const asset_handler *&handler) {
        ReturnUnless(handler->can_handle(asset_path), false);
        return handler->import(asset_path); // parse and validate the asset
      });
}

/////////////////////////////////////////////////////////////////////////////////////////
void asset_manager::register_directory(const std::string &directory) {
  auto dir =
      std::filesystem::directory_iterator(std::filesystem::path(directory));
  for (auto &file : dir) {
    if (file.is_directory()) {
      register_directory(file.path());
    } else {
      register_file(file.path());
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void asset_manager::register_file(const std::filesystem::path &file) {
  for (auto handler : _M_handlers) {
    ContinueUnless(handler->can_handle(file));
    handler->register_asset(file);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
bool asset_manager::load(const uuid &guid) {
  auto *object = asset_storage::instance().get(guid);

  ReturnUnless(object, false);

  object->load();
}

/////////////////////////////////////////////////////////////////////////////////////////
void asset_manager::register_asset_handler(const asset_handler &handler) {
  _M_handlers.push_back(&handler);
  std::sort(_M_handlers.begin(), _M_handlers.end(),
            _M_asset_priority_comparator);
}
} // namespace stinky
