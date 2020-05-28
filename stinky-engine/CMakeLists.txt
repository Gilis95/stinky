cmake_minimum_required(VERSION 3.2)
project(stinky-engine)

set (CMAKE_CXX_STANDARD 17)

add_definitions(-DENABLE_LOG -DENABLE_ASSERTS -D_CRT_SECURE_NO_WARNINGS)

#Project Header directory
set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(RENDERER_HDR_DIR ${HDR_DIR}/renderer)
set(OPENGL_HDR_DIR ${RENDERER_HDR_DIR}/platform/opengl)
set(WINDOW_HDR_DIR ${HDR_DIR}/window)

#Projetc source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(RENDERER_SRC_DIR ${SRC_DIR}/renderer)
set(OPENGL_SRC_DIR ${RENDERER_SRC_DIR}/platform/opengl)
set(WINDOW_SRC_DIR ${SRC_DIR}/window)

#Dependecies directory
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/vendor/glfw/)
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/vendor/glm/)
set(STB_DIR ${PROJECT_SOURCE_DIR}/vendor/stb_image)

set(HDR_FILES 
    # Renderer API
    ${RENDERER_HDR_DIR}/RendererFactory.h 
    ${RENDERER_HDR_DIR}/Renderer.h 
    ${RENDERER_HDR_DIR}/RendererApi.h 
    ${RENDERER_HDR_DIR}/VertexBuffer.h 
    ${RENDERER_HDR_DIR}/VertexArray.h 
    ${RENDERER_HDR_DIR}/Shader.h 
    ${RENDERER_HDR_DIR}/Texture.h 

    #Renderer OpenGL implementation
    ${OPENGL_HDR_DIR}/OpenGLRendererFactory.h 
    ${OPENGL_HDR_DIR}/OpenGLRenderer.h  
    ${OPENGL_HDR_DIR}/OpenGLVertexBuffer.h 
    ${OPENGL_HDR_DIR}/OpenGLVertexArray.h 
    ${OPENGL_HDR_DIR}/OpenGLShader.h 
    ${OPENGL_HDR_DIR}/OpenGLTexture.h 

    #Window submodule
    ${WINDOW_HDR_DIR}/Window.h
    ${WINDOW_HDR_DIR}/glfw/WindowsWindow.h

    ${HDR_DIR}/StinkyLogger.h
    ${HDR_DIR}/StinkyMacros.h
    ${HDR_DIR}/stinkypch.h

    ${STB_DIR}/stb_image.h
    )

set(SRC_FILES 
    #Rendere API
    ${RENDERER_SRC_DIR}/RendererFactory.cpp
    ${RENDERER_SRC_DIR}/Renderer.cpp 

    #Renderer OpenGL implementation
    ${OPENGL_SRC_DIR}/OpenGLRendererFactory.cpp
    ${OPENGL_SRC_DIR}/OpenGLRenderer.cpp
    ${OPENGL_SRC_DIR}/OpenGLVertexBuffer.cpp 
    ${OPENGL_SRC_DIR}/OpenGLIndexBuffer.cpp
    ${OPENGL_SRC_DIR}/OpenGLVertexArray.cpp 
    ${OPENGL_SRC_DIR}/OpenGLShader.cpp
    ${OPENGL_SRC_DIR}/OpenGLTexture.cpp

    #Window submodule
    ${WINDOW_SRC_DIR}/Window.cpp
    ${WINDOW_SRC_DIR}/glfw/WindowsWindow.cpp

    ${SRC_DIR}/StinkyLogger.cpp
    ${STB_DIR}/stb_image.cpp
    )

add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLAD_DIR})
add_subdirectory(${GLM_DIR})

add_library(stinky-engine STATIC ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-engine PRIVATE 
                            ${HDR_DIR}
                            ${STB_DIR}
                            ${GLAD_INCLUDE_DIRS}
                            ${GLFW_DIR}/include
                            ${GLM_DIR}/glm
                            ${SPDLOG_DIR}/include
                            )

target_link_libraries(stinky-engine PRIVATE 
                     glad
                     glm
                     glfw
                     spdlog
                     )
