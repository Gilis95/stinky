#pragma once

#include "stinky_prerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class graphic_layer_abstraction_factory {
public:
  enum class API { none, OpenGL };

  virtual ~graphic_layer_abstraction_factory() = default;

  static stinky::unique_ptr<graphic_layer_abstraction_factory>
  create(const API &api = API::OpenGL);

  [[nodiscard]] virtual stinky::unique_ptr<renderer_api>
  create_renderer_api() const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<frame_buffer> create_frame_buffer(
      const frame_buffer_specification &frameBufferSpecification) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<index_buffer>
  create_index_buffer(const void *data, unsigned int count) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<shader>
  CreateShader(asset_metadata &&metadata) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<texture>
  CreateTexture(const std::string &path) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<texture>
  CreateTexture(uint32_t width, uint32_t height) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<texture>
  CreateCubeTexture(const std::string &path) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<vertex_buffer>
  CreateVertexBuffer(unsigned int size, const BufferLayout &layout) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<vertex_buffer>
  CreateVertexBuffer(const void *data, unsigned int size,
                     const BufferLayout &layout) const = 0;

  [[nodiscard]] virtual stinky::shared_ptr<vertex_array>
  CreateVertexArray() const = 0;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
