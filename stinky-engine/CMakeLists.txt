cmake_minimum_required(VERSION 3.2)
project(stinky-engine)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSTINKY_ENABLE_LOG -D_CRT_SECURE_NO_WARNINGS -DSTINKY_ENGINE_DEBUG -DTRACY_ENABLE)

################################################################################################
#Project Header directory
set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_HDR_DIR ${HDR_DIR}/application)
set(CAMERA_HDR_DIR ${HDR_DIR}/camera)
set(CORE_HDR_DIR ${HDR_DIR}/core)
set(ECS_HDR_DIR ${HDR_DIR}/ecs)
set(EVENT_HDR_DIR ${HDR_DIR}/event)
set(GLA_HDR_DIR ${HDR_DIR}/gla)
set(OPENGL_HDR_DIR ${GLA_HDR_DIR}/platform/opengl)
set(RENDERER_HDR_DIR ${HDR_DIR}/renderer)
set(SCENE_HDR_DIR ${HDR_DIR}/scene)
set(WINDOW_HDR_DIR ${HDR_DIR}/window)

################################################################################################
#Project source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_SRC_DIR ${SRC_DIR}/application)
set(CAMERA_SRC_DIR ${SRC_DIR}/camera)
set(CORE_SRC_DIR ${SRC_DIR}/core)
set(EVENT_SRC_DIR ${SRC_DIR}/event)
set(ECS_SRC_DIR ${SRC_DIR}/ecs)
set(GLA_SRC_DIR ${SRC_DIR}/gla)
set(OPENGL_SRC_DIR ${GLA_SRC_DIR}/platform/opengl)
set(RENDERER_SRC_DIR ${SRC_DIR}/renderer)
set(SCENE_SRC_DIR ${SRC_DIR}/scene)
set(WINDOW_SRC_DIR ${SRC_DIR}/window)

################################################################################################
#Dependencies directory
set(STB_DIR ${PROJECT_SOURCE_DIR}/vendor/stb_image)

################################################################################################
set(HDR_FILES
        # Application module
        ${APPLICATION_HDR_DIR}/Application.h
        ${APPLICATION_HDR_DIR}/EntryPoint.h

        # Camera module
        ${CAMERA_HDR_DIR}/Camera.h
        ${CAMERA_HDR_DIR}/OrthographicCamera.h
        ${CAMERA_HDR_DIR}/OrthographicCameraController.h
        ${CAMERA_HDR_DIR}/PerspectiveCamera.h
        ${CAMERA_HDR_DIR}/PerspectiveCameraController.h

        #Core component
        ${CORE_HDR_DIR}/KeyboardCodes.h
        ${CORE_HDR_DIR}/MouseCodes.h
        ${CORE_HDR_DIR}/StinkyLogger.h
        ${CORE_HDR_DIR}/StinkyMacros.h

        # Entity Component System
        ${ECS_HDR_DIR}/CameraComponent.h
        ${ECS_HDR_DIR}/Entity.h
        ${ECS_HDR_DIR}/TransformComponent.h
        ${ECS_HDR_DIR}/MeshComponents.h
        ${ECS_HDR_DIR}/ProgramComponent.h
        ${ECS_HDR_DIR}/MaterialComponent.h

        #Event submodule
        ${EVENT_HDR_DIR}/Event.h
        ${EVENT_HDR_DIR}/EventController.h
        ${EVENT_HDR_DIR}/KeyEvent.h
        ${EVENT_HDR_DIR}/Layer.h
        ${EVENT_HDR_DIR}/LayerStack.h
        ${EVENT_HDR_DIR}/MouseEvent.h
        ${EVENT_HDR_DIR}/Timestep.h
        ${EVENT_HDR_DIR}/ApplicationEvent.h
        ${EVENT_HDR_DIR}/platform/glfw/GLFWWindowEvent.h
        ${EVENT_HDR_DIR}/WindowsEvent.h

        # Graphic Layer Abstraction module
        ${GLA_HDR_DIR}/CubeTexture.h
        ${GLA_HDR_DIR}/FrameBuffer.h
        ${GLA_HDR_DIR}/GraphicLayerAbstractionFactory.h
        ${GLA_HDR_DIR}/RendererApi.h
        ${GLA_HDR_DIR}/Shader.h
        ${GLA_HDR_DIR}/Texture.h
        ${GLA_HDR_DIR}/VertexBuffer.h
        ${GLA_HDR_DIR}/VertexArray.h

        # Root dir
        ${HDR_DIR}/stinkypch.h
        ${HDR_DIR}/StinkyPrerequisites.h

        # Graphic Layer Abstraction OpenGL implementation
        ${OPENGL_HDR_DIR}/OpenGLFrameBuffer.h
        ${OPENGL_HDR_DIR}/OpenGLGraphicLayerFactory.h
        ${OPENGL_HDR_DIR}/OpenGLRenderer.h
        ${OPENGL_HDR_DIR}/OpenGLVertexBuffer.h
        ${OPENGL_HDR_DIR}/OpenGLVertexArray.h
        ${OPENGL_HDR_DIR}/OpenGLShader.h
        ${OPENGL_HDR_DIR}/OpenGLCubeTexture.h
        ${OPENGL_HDR_DIR}/OpenGLTexture.h

        # Renderer API
        ${RENDERER_HDR_DIR}/Renderer.h

        # Scene
        ${SCENE_HDR_DIR}/Scene.h

        #Window submodule
        ${WINDOW_HDR_DIR}/Window.h
        ${WINDOW_HDR_DIR}/glfw/PlatformIndependentWindow.h

        ${STB_DIR}/stb_image.h
        ${STB_DIR}/stb_image_write.h
        )

################################################################################################
set(SRC_FILES
        #Application
        ${APPLICATION_SRC_DIR}/Application.cpp

        # Camera
        ${CAMERA_SRC_DIR}/Camera.cpp
        ${CAMERA_SRC_DIR}/OrthographicCamera.cpp
        ${CAMERA_SRC_DIR}/OrthographicCameraController.cpp
        ${CAMERA_SRC_DIR}/PerspectiveCamera.cpp
        ${CAMERA_SRC_DIR}/PerspectiveCameraController.cpp

        ${CORE_SRC_DIR}/StinkyMemory.h

        # Entity Component System
        ${ECS_SRC_DIR}/CameraComponent.cpp
        ${ECS_SRC_DIR}/MaterialComponent.cpp
        ${ECS_SRC_DIR}/MeshComponents.cpp
        ${ECS_SRC_DIR}/ProgramComponent.cpp
        ${ECS_SRC_DIR}/TagComponent.h
        ${ECS_SRC_DIR}/TransformComponent.cpp

        #Events
        ${EVENT_SRC_DIR}/LayerStack.cpp
        ${EVENT_SRC_DIR}/Layer.cpp
        ${EVENT_SRC_DIR}/EventController.cpp

        # Graphic Layer Abstraction
        ${GLA_SRC_DIR}/GraphicLayerAbstractionFactory.cpp
        ${GLA_SRC_DIR}/CubeTexture.cpp

        #Renderer OpenGL implementation
        ${OPENGL_SRC_DIR}/OpenGLGraphicLayerFactory.cpp
        ${OPENGL_SRC_DIR}/OpenGLFrameBuffer.cpp
        ${OPENGL_SRC_DIR}/OpenGLIndexBuffer.cpp
        ${OPENGL_SRC_DIR}/OpenGLRenderer.cpp
        ${OPENGL_SRC_DIR}/OpenGLShader.cpp
        ${OPENGL_SRC_DIR}/OpenGLTexture.cpp
        ${OPENGL_SRC_DIR}/OpenGLVertexBuffer.cpp
        ${OPENGL_SRC_DIR}/OpenGLVertexArray.cpp
        ${OPENGL_SRC_DIR}/OpenGLCubeTexture.cpp

        #Render API
        ${RENDERER_SRC_DIR}/Renderer.cpp

        # Scene
        ${SCENE_SRC_DIR}/Scene.cpp

        #General purpose
        ${SRC_DIR}/StinkyLogger.cpp

        #STB dependency
        ${STB_DIR}/stb_image.cpp

        #Window submodule
        ${WINDOW_SRC_DIR}/Window.cpp
        ${WINDOW_SRC_DIR}/glfw/PlatformIndependentWindow.cpp
        )

add_library(stinky-engine STATIC ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-engine PRIVATE
        ${ENTT_DIR_INCLUDE_DIR}
        ${GLM_DIR}
        ${HDR_DIR}
        ${OPENGL_INCLUDE_DIRS}
        ${SPDLOG_DIR}/include
        ${STB_DIR}
        ${TRACY_DIR}
        ${WINDOW_ABSTRACTION_INCLUDE_DIR}
        )

target_link_libraries(stinky-engine PRIVATE
        glm
        ${OPENGL_LIB}
        spdlog
        tracy
        ${WINDOW_ABSTRACTION_LIB}
        )
