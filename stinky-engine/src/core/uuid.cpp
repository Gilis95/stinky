#include "uuid.h"
#include "stinkypch.h"

#include <random>
#include <yaml-cpp/node/convert.h>

namespace stinky {
static std::random_device s_RandomDevice;
static std::mt19937_64 eng(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

uuid::uuid() : value(s_UniformDistribution(eng)) {}

uuid::uuid(uint64_t uuid) : value(uuid) {}

uuid::uuid(const uuid &other) = default;

uuid::uuid(uuid &&other) noexcept : value(other.value){};

uuid &uuid::operator=(uint64_t uuid) {
  value = uuid;
  return *this;
}

uuid &uuid::operator=(uuid &&uuid) noexcept {
  value = uuid.value;

  return *this;
}

bool uuid::operator==(const uuid &other) const { return value == other.value; }

uuid::operator uint64_t() const { return value; }
} // namespace stinky

namespace YAML {
Node convert<stinky::uuid>::encode(const stinky::uuid &rhs) {
  Node node;
  node.push_back(rhs.value);
  return node;
}

bool convert<stinky::uuid>::decode(const Node &node, stinky::uuid &rhs) {
  rhs = node.as<uint64_t>();
  return true;
}
} // namespace YAML

std::size_t
std::hash<stinky::uuid>::operator()(const stinky::uuid &uuid) const {
  return hash<uint64_t>()(uuid.value);
}