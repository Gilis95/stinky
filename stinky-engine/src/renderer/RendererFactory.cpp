#include "renderer/RendererFactory.h"
#include "renderer/platform/opengl/OpenGLRendererFactory.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    Ref<RendererFactory> RendererFactory::create(const API &api) {
        switch (api) {
            case API::none: STINKY_ASSERT_LOG("No Graphic API has been chosen");
                return nullptr;
            case API::OpenGL:
                return CreateRef<OpenGLRendererFactory>();
            default: STINKY_ASSERT_LOG("No Graphic API has been chosen");
                return nullptr;
        }
    }
}
