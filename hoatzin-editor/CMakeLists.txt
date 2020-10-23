cmake_minimum_required(VERSION 3.16)
project(hoatzin-editor)

set(CMAKE_CXX_STANDARD 17)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# 3rd party lib dir
set(ETT_DIR ${PROJECT_SOURCE_DIR}/../vendor/entt)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/../vendor/glfw/)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/../vendor/glm/)
set(IMGUI_DEAR_DIR ${PROJECT_SOURCE_DIR}/vendor/imgui/)

# Submodules dir
set(STINKY_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../stinky-engine)

set(HDR_FILES
        ${HDR_DIR}/HoatzinApplication.h
        ${HDR_DIR}/HoatzinEditorLayer.h
        ${HDR_DIR}/ImGuiLayer.h)

set(SRC_FILES
        ${SRC_DIR}/HoatzinApplication.cpp
        ${SRC_DIR}/HoatzinEditorLayer.cpp
        ${SRC_DIR}/ImGuiLayer.cpp)

#3rd party libraries
add_subdirectory(${IMGUI_DEAR_DIR})

add_executable(hoatzin-editor ${SRC_FILES} ${HDR_FILES})

target_include_directories(hoatzin-editor PRIVATE
        ${ETT_DIR}/src
        ${GLM_DIR}
        ${GLFW_DIR}/include
        ${HDR_DIR}
        ${IMGUI_DEAR_DIR}/
        ${STINKY_ENGINE_DIR}/src
        )

target_link_libraries(hoatzin-editor PRIVATE
        stinky::stinky-engine
        glfw
        glm
        imgui-dear
        spdlog
        )
