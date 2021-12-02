//
// Created by christian on 1/26/20.
//
#pragma once

#include "asset/asset.h"
#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class shader : public asset {
public:
  ~shader() override = default;

  virtual void bind() const = 0;

  virtual void unbind() const = 0;

  virtual void set_integer(const std::string &name, int i) = 0;

  virtual void set_float4(const std::string &name, glm::vec4 vector) = 0;

  virtual void set_mat4(const std::string &name, glm::mat4 matrix) = 0;

  constexpr int get_type() override { return 3000; }
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
