cmake_minimum_required(VERSION 3.16)
project(stinky-engine)

set (CMAKE_CXX_STANDARD 17)

add_definitions(-DENABLE_LOG)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(GLFW_DIR ${PROJECT_SOURCE_DIR}/vendor/glfw/)
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/vendor/glm/)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/vendor/spdlog)
set(STB_DIR ${PROJECT_SOURCE_DIR}/vendor/stb_image)

set(HDR_FILES 
    ${HDR_DIR}/Renderer.h 
    ${HDR_DIR}/VertexBuffer.h 
    ${HDR_DIR}/VertexArray.h
    ${HDR_DIR}/VertexBufferLayout.h 
    ${HDR_DIR}/Shader.h 
    ${HDR_DIR}/Texture.h
    ${HDR_DIR}/Logger.h
    ${HDR_DIR}/Macros.h
    ${STB_DIR}/stb_image.h)

set(SRC_FILES 
    ${SRC_DIR}/main.cpp  
    ${SRC_DIR}/Renderer.cpp  
    ${SRC_DIR}/VertexBuffer.cpp 
    ${SRC_DIR}/IndexBuffer.cpp
    ${SRC_DIR}/VertexArray.cpp 
    ${SRC_DIR}/Shader.cpp
    ${SRC_DIR}/Texture.cpp
    ${SRC_DIR}/Logger.cpp
    ${STB_DIR}/stb_image.cpp)

add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLAD_DIR})
add_subdirectory(${GLM_DIR})
add_subdirectory(${SPDLOG_DIR})

add_executable(stinky-engine ${SRC_FILES} ${HDR_FILES})

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
