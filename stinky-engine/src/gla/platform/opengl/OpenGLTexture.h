//
// Created by christian on 09/02/2020.
//
#pragma once

#include "gla/texture.h"
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class OpenGLTexture : public texture {
public:
  explicit OpenGLTexture(const std::string &path);

  OpenGLTexture(uint32_t width, uint32_t height);

  ~OpenGLTexture() override;

  void bind(unsigned int slot = 0) const override;

  void unbind(uint32_t slot) const override;

  void set_data(void *data) override;

  [[nodiscard]] uint32_t get_width() const override { return _M_width; };

  [[nodiscard]] uint32_t get_height() const override { return _M_height; };

private:
  int _M_width, _M_height;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////