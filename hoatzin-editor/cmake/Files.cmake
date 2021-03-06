include(cmake/Variables.cmake)

file(GLOB EVENT_HEADER ${EVENT_HDR_DIR}/*.h)
file(GLOB EVENT_INLINE ${EVENT_HDR_DIR}/*.hpp)
file(GLOB EVENT_SOURCE ${EVENT_SRC_DIR}/*.cpp)

file(GLOB HOATZIN_IMGUI_GLFW_HEADER ${HOATZIN_IMGUI_GLFW_HDR_DIR}/*.h)
file(GLOB HOATZIN_IMGUI_GLFW_INLINE ${HOATZIN_IMGUI_GLFW_HDR_DIR}/*.hpp)
file(GLOB HOATZIN_IMGUI_GLFW_SOURCE ${HOATZIN_IMGUI_GLFW_SRC_DIR}/*.cpp)

file(GLOB PANELS_HEADER ${PANELS_HDR_DIR}/*.h)
file(GLOB PANELS_INLINE ${PANELS_HDR_DIR}/*.hpp)
file(GLOB PANELS_SOURCE ${PANELS_SRC_DIR}/*.cpp)

file(GLOB ROOT_HEADER ${HDR_DIR}/*.h)
file(GLOB ROOT_INLINE ${HDR_DIR}/*.hpp)
file(GLOB ROOT_SOURCE ${SRC_DIR}/*.cpp)

file(GLOB SAVE_HEADER ${SAVE_HDR_DIR}/*.h)
file(GLOB SAVE_INLINE ${SAVE_HDR_DIR}/*.hpp)
file(GLOB SAVE_SOURCE ${SAVE_SRC_DIR}/*.cpp)

file(GLOB STYLE_HEADER ${STYLE_HDR_DIR}/*.h)
file(GLOB STYLE_INLINE ${STYLE_HDR_DIR}/*.hpp)
file(GLOB STYLE_SOURCE ${STYLE_SRC_DIR}/*.cpp)

set(HDR_FILES
        ${EVENT_HEADER}
        ${EVENT_INLINE}
        ${HOATZIN_IMGUI_GLFW_HEADER}
        ${HOATZIN_IMGUI_GLFW_INLINE}
        ${PANELS_HEADER}
        ${PANELS_INLINE}
        ${ROOT_HEADER}
        ${ROOT_INLINE}
        ${SAVE_HEADER}
        ${SAVE_INLINE}
        ${STYLE_HEADER}
        ${STYLE_INLINE}
        )

set(SRC_FILES
        ${EVENT_SOURCE}
        ${HOATZIN_IMGUI_GLFW_SOURCE}
        ${PANELS_SOURCE}
        ${ROOT_SOURCE}
        ${SAVE_SOURCE}
        ${STYLE_SOURCE}
        )
