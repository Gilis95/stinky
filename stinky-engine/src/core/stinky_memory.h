//
// Created by christian on 19.11.20 г..
//

#pragma once

#ifdef STINKY_MEMORY_DEBUG
#include <iostream>
#endif

#include <memory>

namespace stinky {
template <typename T> using shared_ptr = std::shared_ptr<T>;

template <typename T> using unique_ptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr unique_ptr<T> create_scope(Args &&...args) {
#ifdef STINKY_MEMORY_DEBUG
  std::cout << "Unique pointer creation: " << __builtin_FUNCTION() << std::endl;
#endif
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T> using shared_ptr = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr shared_ptr<T> create_ref(Args &&...args) {
#ifdef STINKY_MEMORY_DEBUG
  std::cout << "Shared pointer creation: " << __builtin_FUNCTION() << std::endl;
#endif
  return std::make_shared<T>(std::forward<Args>(args)...);
}
} // namespace stinky
