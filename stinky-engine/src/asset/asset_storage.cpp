//
// Created by christian on 10/14/21.
//
#include "asset/asset_storage.h"
#include "core/stinky_memory.h"
#include <optional>

namespace stinky {
unique_ptr<asset_storage> asset_storage::_S_instance;

////////////////////////////////////////////////////////////////////////////////
asset_storage::asset_storage() = default;

////////////////////////////////////////////////////////////////////////////////
asset_storage::~asset_storage() = default;

////////////////////////////////////////////////////////////////////////////////
asset_storage &asset_storage::instance() {
  if (!_S_instance) {
    _S_instance.reset(new asset_storage());
  }

  return *(_S_instance.get());
}

////////////////////////////////////////////////////////////////////////////////
bool asset_storage::emplace(uuid &&_guid, unique_ptr<asset> &&_asset) {
  return _M_storage.emplace(_guid, std::forward<std::unique_ptr<asset>>(_asset))
      .second;
}

////////////////////////////////////////////////////////////////////////////////
const asset *asset_storage::get(const uuid &_guid) const {
  auto element = _M_storage.find(_guid);

  ReturnIf(element == _M_storage.end(), nullptr);

  return element->second.get();
}

////////////////////////////////////////////////////////////////////////////////
asset *asset_storage::get(const uuid &_guid) {
  auto element = _M_storage.find(_guid);

  ReturnIf(element == _M_storage.end(), nullptr);

  return element->second.get();
}

////////////////////////////////////////////////////////////////////////////////
std::optional<uuid> asset_storage::generate_uuid() {
  uuid _guid;
  {
    int maxRetries = 10; // TODO:: Must be project setting
    while (_M_storage.find(_guid) != _M_storage.end() && maxRetries > 0) {
      _guid = uuid();
      --maxRetries;
    }

    AssertReturnUnless(maxRetries > 0, {})
  }

  return _guid;
}

} // namespace stinky