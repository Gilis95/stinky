cmake_minimum_required(VERSION 3.16)
project(hoatzin-editor)

set(CMAKE_CXX_STANDARD 17)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)
set(EVENT_HDR_DIR ${HDR_DIR}/event)
set(HOATZIN_IMGUI_HDR_DIR ${HDR_DIR}/imgui)
set(HOATZIN_IMGUI_GLFW_HDR_DIR ${HOATZIN_IMGUI_HDR_DIR}/platform/glfw)
set(PANELS_HDR_DIR ${HDR_DIR}/panels)
set(SAVE_HDR_DIR ${HDR_DIR}/save)
set(STYLE_HDR_DIR ${HDR_DIR}/style)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(EVENT_SRC_DIR ${SRC_DIR}/event)
set(HOATZIN_IMGUI_SRC_DIR ${SRC_DIR}/imgui)
set(HOATZIN_IMGUI_GLFW_SRC_DIR ${HOATZIN_IMGUI_SRC_DIR}/platform/glfw)
set(PANELS_SRC_DIR ${SRC_DIR}/panels)
set(SAVE_SRC_DIR ${SRC_DIR}/save)
set(STYLE_SRC_DIR ${SRC_DIR}/style)

# 3rd party lib dir
set(IMGUI_DEAR_DIR ${PROJECT_SOURCE_DIR}/vendor/imgui/)

# Submodules dir
set(STINKY_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../stinky-engine)

set(HDR_FILES
        ${EVENT_HDR_DIR}/HoatzinEditorLayer.h
        ${HDR_DIR}/HoatzinApplication.h
        ${HOATZIN_IMGUI_GLFW_HDR_DIR}/ImGuiInitializer.h
        ${PANELS_HDR_DIR}/SceneHierarchyPanel.h
        ${PANELS_HDR_DIR}/EntityInspectorPanel.h
        ${PANELS_HDR_DIR}/ScenePanel.h
        ${PANELS_HDR_DIR}/Workspace.h
        ${SAVE_HDR_DIR}/SaveManager.h
        ${STYLE_HDR_DIR}/HoatzinImGui.h
        )

set(SRC_FILES
        ${EVENT_SRC_DIR}/HoatzinEditorLayer.cpp
        ${HOATZIN_IMGUI_GLFW_SRC_DIR}/ImGuiInitializer.cpp
        ${PANELS_SRC_DIR}/EntityInspectorPanel.cpp
        ${PANELS_SRC_DIR}/SceneHierarchyPanel.cpp
        ${PANELS_SRC_DIR}/ScenePanel.cpp
        ${PANELS_SRC_DIR}/Workspace.cpp
        ${SAVE_SRC_DIR}/SaveManager.cpp
        ${SRC_DIR}/HoatzinApplication.cpp
        ${STYLE_SRC_DIR}/HoatzinImGui.cpp
        )

# Definitions
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD -DSTINKY_ENABLE_LOG -DTRACY_ENABLE )

#3rd party libraries
add_subdirectory(${IMGUI_DEAR_DIR})

add_executable(hoatzin-editor ${SRC_FILES} ${HDR_FILES})

target_include_directories(hoatzin-editor PRIVATE
        ${ENTT_DIR_INCLUDE_DIR}
        ${GLM_DIR}
        ${HDR_DIR}
        ${IMGUI_DEAR_DIR}/
        ${STINKY_ENGINE_DIR}/src
        ${TRACY_DIR}
        ${WINDOW_ABSTRACTION_INCLUDE_DIR}
        )

target_link_libraries(hoatzin-editor PRIVATE
        stinky::stinky-engine
        glm
        imgui-dear
        spdlog
        tracy
        ${WINDOW_ABSTRACTION_INCLUDE_DIR}
        )
