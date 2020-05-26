#include "renderer/RendererFactory.h"
#include "renderer/platform/opengl/OpenGLRendererFactory.h"

namespace stinky {
    Ref<RendererFactory> RendererFactory::create(API api) {
        switch (api)
        {
        case stinky::RendererFactory::API::none:
            ASSERT(false, "No Graphic API has been choosen");
            break;
        case stinky::RendererFactory::API::OpenGL:
            return createRef<OpenGLRendererFactory>();
        default:
            ASSERT(false, "No Graphic API has been choosen");
            break;
        }
    }
}
