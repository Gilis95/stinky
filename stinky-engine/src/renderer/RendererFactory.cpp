#include "renderer/RendererFactory.h"
#include "renderer/platform/opengl/OpenGLRendererFactory.h"

namespace stinky {
    Ref<RendererFactory> RendererFactory::create(const API& api) {
        switch (api)
        {
        case API::none:
            ASSERT(false, "No Graphic API has been choosen");
            return nullptr;
        case API::OpenGL:
            return CreateRef<OpenGLRendererFactory>();
        default:
            ASSERT(false, "No Graphic API has been choosen");
            return nullptr;
        }
    }
}
