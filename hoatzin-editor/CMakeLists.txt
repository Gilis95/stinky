cmake_minimum_required(VERSION 3.16)
project(hoatzin-editor)

set(CMAKE_CXX_STANDARD 17)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# 3rd party lib dir
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

# Definitions
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

#3rd party libraries
add_subdirectory(${IMGUI_DEAR_DIR})

add_executable(hoatzin-editor ${SRC_FILES} ${HDR_FILES})

target_include_directories(hoatzin-editor PRIVATE
        ${ENTT_DIR_INCLUDE_DIR}
        ${GLM_DIR}
        ${HDR_DIR}
        ${IMGUI_DEAR_DIR}/
        ${STINKY_ENGINE_DIR}/src
        ${WINDOW_ABSTRACTION_INCLUDE_DIR}
        )

target_link_libraries(hoatzin-editor PRIVATE
        stinky::stinky-engine
        glm
        imgui-dear
        spdlog
        ${WINDOW_ABSTRACTION_INCLUDE_DIR}
        )
