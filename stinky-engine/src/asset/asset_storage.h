//
// Created by christian on 6/30/21.
//

#ifndef STINKY_ASSET_STORAGE_H
#define STINKY_ASSET_STORAGE_H

#include "asset/asset.h"
#include "core/stinky_macros.h"
#include "core/uuid.h"
#include <unordered_map>

namespace std {
template <class _Type> class optional;
}

namespace stinky {
class asset_storage {
private:
  asset_storage();

public:
  ~asset_storage();

public:
  static asset_storage &instance();

public:
  template <class _AssetType>
  std::enable_if_t<std::is_base_of<asset, _AssetType>::value, _AssetType> *
  get(const uuid &_guid) {
    auto _element = _M_storage.find(_guid);

    ReturnIf(_element == _M_storage.end(), nullptr);

    auto _asset = _element->second.get();
    return _asset == nullptr ? nullptr : _asset->as<_AssetType>();
  }

  bool emplace(uuid &&_guid, unique_ptr<asset> &&_asset);

  const asset *get(const uuid &_guid) const;
  asset *get(const uuid &_guid);
  std::optional<uuid> generate_uuid();

private:
  static unique_ptr<asset_storage> _S_instance;
  std::unordered_map<uuid, unique_ptr<asset>> _M_storage;
};
} // namespace stinky
#endif // STINKY_ASSET_STORAGE_H
