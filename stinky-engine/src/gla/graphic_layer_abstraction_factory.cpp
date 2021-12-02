#include "gla/graphic_layer_abstraction_factory.h"
#include "gla/platform/opengl/opengl_graphic_layer_factory.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
unique_ptr<graphic_layer_abstraction_factory>
graphic_layer_abstraction_factory::create(const API &api) {
  switch (api) {
  case API::none:
    STINKY_LOG_ERROR_AND_BREAK("No Graphic API has been chosen");
    return nullptr;
  case API::OpenGL:
    return create_scope<opengl_graphic_layer_factory>();
  default:
    STINKY_LOG_ERROR_AND_BREAK("No Graphic API has been chosen");
    return nullptr;
  }
}
} // namespace stinky
