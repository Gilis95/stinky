//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_H
#define STINKY_ASSET_H

#include <type_traits>

namespace stinky {
class asset {
public:
  asset() = default;

  virtual ~asset() = default;

  virtual void load() = 0;

  virtual constexpr int get_type() = 0;

  template <class T, class Enable = void> T &as() { return nullptr; }

  template <class T, std::enable_if_t<std::is_base_of<asset, T>::value>>
  T &as() {
    if constexpr (get_type() == T::type) {
      return static_cast<T>(*this);
    }
    return nullptr;
  }
};
} // namespace stinky

#endif // STINKY_ASSET_H
