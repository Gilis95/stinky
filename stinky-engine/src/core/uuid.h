//
// Created by christian on 6/30/21.
//

#ifndef STINKY_UUID_H
#define STINKY_UUID_H

#include <cstdint>
namespace stinky {

/**
 * Currently this class is just randomly generated 64-bit integer.
 */
class uuid {
public:
  uuid();
  explicit uuid(uint64_t uuid);
  uuid(const uuid &other);
  uuid(uuid &&other) noexcept;

  uuid &operator=(uint64_t uuid);
  uuid &operator=(uuid &&uuid) noexcept;
  bool operator==(const uuid &other) const;
  explicit operator uint64_t() const;

public:
  uint64_t value;
};
} // namespace stinky

namespace YAML {
class Node;
template <typename T> struct convert;

template <> struct convert<stinky::uuid> {
  static Node encode(const stinky::uuid &rhs);

  static bool decode(const Node &node, stinky::uuid &rhs);
};
} // namespace YAML

namespace std {
template <class T> struct hash;

template <> struct hash<stinky::uuid> {
  std::size_t operator()(const stinky::uuid &uuid) const;
};
} // namespace std
#endif // STINKY_UUID_H
