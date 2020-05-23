cmake_minimum_required(VERSION 3.16)
project(engine)

set (CMAKE_CXX_STANDARD 17)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(HDR_FILES 
    ${HDR_DIR}/Renderer.h 
    ${HDR_DIR}/VertexBuffer.h 
    ${HDR_DIR}/VertexArray.h
    ${HDR_DIR}/VertexBufferLayout.h 
    ${HDR_DIR}/Shader.h 
    include/Texture.h)

set(SRC_FILES 
    ${SRC_DIR}/main.cpp  
    ${SRC_DIR}/Renderer.cpp  
    ${SRC_DIR}/VertexBuffer.cpp 
    ${SRC_DIR}/IndexBuffer.cpp
    ${SRC_DIR}/VertexArray.cpp 
    ${SRC_DIR}/VertexBufferLayout.cpp  
    ${SRC_DIR}/Shader.cpp
    ${SRC_DIR}/Texture.cpp)

include_directories(include)

add_executable(engine ${SRC_FILES} ${HDR_FILES})

target_include_directories(engine PRIVATE 
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glm/gtx
    ${PROJECT_SOURCE_DIR}/vendor/glm/simd
    ${PROJECT_SOURCE_DIR}/vendor/glm/gtc
    ${PROJECT_SOURCE_DIR}/vendor/glm/ext
    ${PROJECT_SOURCE_DIR}/vendor/glm/detail
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    ${PROJECT_SOURCE_DIR}/vendor/stb
    )

target_link_directories(engine PRIVATE 
    ${PROJECT_SOURCE_DIR}/vendor/glfw/
    ${PROJECT_SOURCE_DIR}/vendor/glm/
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/
    )

target_link_libraries(engine glfw3 )