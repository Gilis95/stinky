include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY git@github.com:Gilis95/imgui.git
        GIT_TAG 5cf21ec4f7b9db6d672525fea47b59e135d6ed71
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    set(IMGUI_OPENGL ON)
    set(IMGUI_GLFW ON)
    add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR})
endif()