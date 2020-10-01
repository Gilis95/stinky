cmake_minimum_required(VERSION 3.2)
project(stinky-engine)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DENABLE_LOG -DENABLE_ASSERTS -D_CRT_SECURE_NO_WARNINGS -DDEBUG)

################################################################################################

#Project Header directory
set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)

set(APPLICATION_HDR_DIR ${HDR_DIR}/application)
set(CAMERA_HDR_DIR ${HDR_DIR}/camera)
set(CORE_HDR_DIR ${HDR_DIR}/core)
set(EVENT_HDR_DIR ${HDR_DIR}/event)
set(GLA_HDR_DIR ${HDR_DIR}/gla)
set(RENDERER_HDR_DIR ${HDR_DIR}/renderer)
set(OPENGL_HDR_DIR ${GLA_HDR_DIR}/platform/opengl)
set(WINDOW_HDR_DIR ${HDR_DIR}/window)

################################################################################################

#Project source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_SRC_DIR ${SRC_DIR}/application)
set(CAMERA_SRC_DIR ${SRC_DIR}/camera)
set(EVENT_SRC_DIR ${SRC_DIR}/event)
set(GLA_SRC_DIR ${SRC_DIR}/gla)
set(RENDERER_SRC_DIR ${SRC_DIR}/renderer)
set(OPENGL_SRC_DIR ${GLA_SRC_DIR}/platform/opengl)
set(WINDOW_SRC_DIR ${SRC_DIR}/window)

################################################################################################

#Dependencies directory
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/vendor/glfw/)
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/../vendor/glm/)
set(STB_DIR ${PROJECT_SOURCE_DIR}/vendor/stb_image)

################################################################################################

set(HDR_FILES
        # Application module
        ${APPLICATION_HDR_DIR}/Application.h
        ${APPLICATION_HDR_DIR}/EntryPoint.h

        # Camera module
        ${CAMERA_HDR_DIR}/OrthographicCamera.h
        ${CAMERA_HDR_DIR}/OrthographicCameraController.h
        ${CAMERA_HDR_DIR}/PerspectiveCamera.h

        # Graphic Layer Abstraction module
        ${GLA_HDR_DIR}/GraphicLayerAbstractionFactory.h
        ${GLA_HDR_DIR}/RendererApi.h
        ${GLA_HDR_DIR}/VertexBuffer.h
        ${GLA_HDR_DIR}/VertexArray.h
        ${GLA_HDR_DIR}/Shader.h
        ${GLA_HDR_DIR}/Texture.h
        ${GLA_HDR_DIR}/FrameBuffer.h

        # Renderer API
        ${RENDERER_HDR_DIR}/Renderer.h
        ${RENDERER_HDR_DIR}/Renderer2D.h
        ${RENDERER_HDR_DIR}/Renderer3D.h

        # Graphic Layer Abstraction OpenGL implementation
        ${OPENGL_HDR_DIR}/OpenGLGraphicLayerFactory.h
        ${OPENGL_HDR_DIR}/OpenGLRenderer.h
        ${OPENGL_HDR_DIR}/OpenGLVertexBuffer.h
        ${OPENGL_HDR_DIR}/OpenGLVertexArray.h
        ${OPENGL_HDR_DIR}/OpenGLShader.h
        ${OPENGL_HDR_DIR}/OpenGLTexture.h
        ${OPENGL_HDR_DIR}/OpenGLFrameBuffer.h

        #Window submodule
        ${WINDOW_HDR_DIR}/Window.h
        ${WINDOW_HDR_DIR}/glfw/PlatformIndependentWindow.h

        #Event submodule
        ${EVENT_HDR_DIR}/Event.h
        ${EVENT_HDR_DIR}/EventController.h
        ${EVENT_HDR_DIR}/KeyEvent.h
        ${EVENT_HDR_DIR}/Layer.h
        ${EVENT_HDR_DIR}/LayerStack.h
        ${EVENT_HDR_DIR}/MouseEvent.h
        ${EVENT_HDR_DIR}/Timestep.h
        ${EVENT_HDR_DIR}/ApplicationEvent.h

        #Core component
        ${CORE_HDR_DIR}/KeyboardCodes.h
        ${CORE_HDR_DIR}/MouseCodes.h
        ${CORE_HDR_DIR}/StinkyLogger.h
        ${CORE_HDR_DIR}/StinkyMacros.h

        ${HDR_DIR}/stinkypch.h


        ${STB_DIR}/stb_image.h
        include/camera/PerspectiveCameraController.h)

################################################################################################

set(SRC_FILES
        #Application
        ${APPLICATION_SRC_DIR}/Application.cpp

        # Camera
        ${CAMERA_SRC_DIR}/OrthographicCamera.cpp
        ${CAMERA_SRC_DIR}/OrthographicCameraController.cpp

        #Events
        ${EVENT_SRC_DIR}/EventController.cpp
        ${EVENT_SRC_DIR}/LayerStack.cpp
        ${EVENT_SRC_DIR}/Layer.cpp

        # Graphic Layer Abstraction
        ${GLA_SRC_DIR}/GraphicLayerAbstractionFactory.cpp

        #Renderer OpenGL implementation
        ${OPENGL_SRC_DIR}/OpenGLGraphicLayerFactory.cpp
        ${OPENGL_SRC_DIR}/OpenGLRenderer.cpp
        ${OPENGL_SRC_DIR}/OpenGLVertexBuffer.cpp
        ${OPENGL_SRC_DIR}/OpenGLIndexBuffer.cpp
        ${OPENGL_SRC_DIR}/OpenGLVertexArray.cpp
        ${OPENGL_SRC_DIR}/OpenGLShader.cpp
        ${OPENGL_SRC_DIR}/OpenGLTexture.cpp
        ${OPENGL_SRC_DIR}/OpenGLFrameBuffer.cpp

        #Render API
        ${RENDERER_SRC_DIR}/Renderer.cpp
        ${RENDERER_SRC_DIR}/Renderer2D.cpp
        ${RENDERER_SRC_DIR}/Renderer3D.cpp

        #General purpose
        ${SRC_DIR}/StinkyLogger.cpp

        #STB dependency
        ${STB_DIR}/stb_image.cpp

        #Window submodule
        ${WINDOW_SRC_DIR}/Window.cpp
        ${WINDOW_SRC_DIR}/glfw/PlatformIndependentWindow.cpp
        src/camera/PerspectiveCamera.cpp src/camera/PerspectiveCameraController.cpp)

add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLAD_DIR})

add_library(stinky-engine STATIC ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-engine PRIVATE
        ${HDR_DIR}
        ${STB_DIR}
        ${GLAD_INCLUDE_DIRS}
        ${GLFW_DIR}/include
        ${GLM_DIR}
        ${SPDLOG_DIR}/include
        )

target_link_libraries(stinky-engine PRIVATE
        glad
        glm
        glfw
        spdlog
        )
