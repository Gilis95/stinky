//
// Created by christian on 04/10/2020.
//

#pragma once

#include "core/StinkyLogger.h"
#include "core/StinkyMacros.h"
#include "core/StinkyMemory.h"

namespace stinky {
    /** ################################ Graphic Layer Abstraction Classes ####################################### */
    class CubeTexture;
    class FrameBuffer;
    struct FrameBufferSpecification;
    class GraphicLayerAbstractionFactory;
    class IndexBuffer;
    class Shader;
    class Texture;
    class VertexArray;
    class VertexBuffer;
    class BufferLayout;
    class RendererApi;
    /** ################################ Graphic Layer Abstraction Classes ####################################### */

    /** ################################ Entity Component Classes ################################################ */
    class MeshComponent;
    class TransformComponent;
    class MaterialComponent;
    class ProgramComponent;
    /** ################################ Entity Component Classes ################################################ */

    /** ################################ Cameras ################################################################# */
    class PerspectiveCamera;
    class OrthographicCamera;
    /** ################################ Cameras ################################################################# */

    /** ################################ Events ################################################################# */
    class AppTickEvent;
    class AppUpdateEvent;
    class AppRenderEvent;

    class KeyPressedEvent;
    class KeyReleasedEvent;
    class KeyTypedEvent;

    class MouseMovedEvent;
    class MouseScrolledEvent;
    class MouseButtonPressedEvent;
    class MouseButtonReleasedEvent;

    class Timestep;

    class WindowResizeEvent;
    class WindowCloseEvent;
    /** ################################ Events ################################################################# */

    /** ################################ Window ################################################################# */
    class Window;
    /** ################################ Window ################################################################# */
}