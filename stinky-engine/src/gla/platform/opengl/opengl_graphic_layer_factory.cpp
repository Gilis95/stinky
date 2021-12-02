#include "asset/entity/stinky/asset_metadata.h"

#include "gla/platform/opengl/opengl_graphic_layer_factory.h"

#include "gla/cube_texture.h"
#include "gla/frame_buffer.h"
#include "gla/index_buffer.h"
#include "gla/shader.h"
#include "gla/texture.h"
#include "gla/vertex_array.h"
#include "gla/vertex_buffer.h"

#include "gla/platform/opengl/OpenGLCubeTexture.h"
#include "gla/platform/opengl/OpenGLFrameBuffer.h"
#include "gla/platform/opengl/OpenGLRenderer.h"
#include "gla/platform/opengl/OpenGLTexture.h"
#include "gla/platform/opengl/OpenGLVertexArray.h"
#include "gla/platform/opengl/OpenGLVertexBuffer.h"
#include "gla/platform/opengl/opengl_index_buffer.h"
#include "gla/platform/opengl/opengl_shader.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
unique_ptr<renderer_api>
opengl_graphic_layer_factory::create_renderer_api() const {
  return create_scope<OpenGLRenderer>();
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<frame_buffer> opengl_graphic_layer_factory::create_frame_buffer(
    const frame_buffer_specification &frameBufferSpecification) const {
  return create_ref<OpenGLFrameBuffer>(frameBufferSpecification);
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<index_buffer>
opengl_graphic_layer_factory::create_index_buffer(const void *data,
                                               unsigned int count) const {
  return create_ref<opengl_index_buffer>(data, count);
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<vertex_buffer> opengl_graphic_layer_factory::CreateVertexBuffer(
    unsigned int size, const BufferLayout &layout) const {
  return create_ref<OpenGLVertexBuffer>(layout, size);
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<vertex_buffer> opengl_graphic_layer_factory::CreateVertexBuffer(
    const void *data, unsigned int size, const BufferLayout &layout) const {
  return create_ref<OpenGLVertexBuffer>(layout, data, size);
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<vertex_array>
opengl_graphic_layer_factory::CreateVertexArray() const {
  return create_ref<OpenGLVertexArray>();
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<shader>
opengl_graphic_layer_factory::CreateShader(asset_metadata &&metadata) const {
  return create_ref<opengl_shader>(std::forward<asset_metadata>(metadata));
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<texture>
opengl_graphic_layer_factory::CreateTexture(const std::string &path) const {
  return create_ref<OpenGLTexture>(path);
}

/////////////////////////////////////////////////////////////////////////////////////////
shared_ptr<texture>
opengl_graphic_layer_factory::CreateTexture(uint32_t width,
                                         uint32_t height) const {
  return create_ref<OpenGLTexture>(width, height);
}

/////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] shared_ptr<texture>
opengl_graphic_layer_factory::CreateCubeTexture(const std::string &path) const {
  return create_ref<OpenGLCubeTexture>(path);
}

} // namespace stinky