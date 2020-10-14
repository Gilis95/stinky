#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/platform/opengl/OpenGLGraphicLayerFactory.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    Scope<GraphicLayerAbstractionFactory> GraphicLayerAbstractionFactory::create(const API &api) {
        switch (api) {
            case API::none: STINKY_LOG_ERROR_AND_BREAK("No Graphic API has been chosen");
                return nullptr;
            case API::OpenGL:
                return CreateScope<OpenGLGraphicLayerFactory>();
            default: STINKY_LOG_ERROR_AND_BREAK("No Graphic API has been chosen");
                return nullptr;
        }
    }
}
