//
// Created by christian on 1/26/20.
//
#pragma once

#include <unordered_map>

#include "asset/entity/stinky/asset_metadata.h"
#include "gla/shader.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

class asset_metadata;

/////////////////////////////////////////////////////////////////////////////////////////
class opengl_shader : public shader {
public:
  explicit opengl_shader(asset_metadata&& asset_metadata);

  ~opengl_shader() override;

public: //shader virtual methods
  void bind() const override;

  void unbind() const override;

  void set_integer(const std::string &name, int i) override;

  void set_float4(const std::string &name, glm::vec4 vector) override;

  void set_mat4(const std::string &name, glm::mat4 matrix) override;

public: // asset virtual methods
  constexpr int get_type() override{
    return shader::get_type() + 1;
  }

  void load() override;

private:
  uint32_t m_RendererID;
  asset_metadata _M_asset_metadata;
  std::unordered_map<uint32_t, std::string> m_ShaderSources;
  std::unordered_map<std::string, int> m_UniformLocationsCache;

private:
  void create_program();

  void parse_shaders(const std::string &source);

  int get_uniform_location(const std::string &name);

  static uint32_t compile_shader(uint32_t type, const std::string &shaderCode);
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////