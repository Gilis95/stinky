project(hoatzin-editor)

# Definitions
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD -DSTINKY_ENABLE_LOG -DSK_PLATFORM_LINUX)

include(cmake/Files.cmake)

add_executable(hoatzin-editor ${imgui_INCLUDES} ${imgui_SOURCES} ${SRC_FILES} ${HDR_FILES})

target_include_directories(hoatzin-editor PRIVATE ${imgui_INCLUDES} ${stinky-engine_INCLUDES} ${HDR_DIR})

target_link_libraries(hoatzin-editor PRIVATE EnTT glad glfw glm imgui spdlog stinky::stinky-engine tracy)
