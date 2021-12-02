include(cmake/Variables.cmake)

file(GLOB APPLICATION_HEADER ${APPLICATION_HDR_DIR}/*.h)
file(GLOB APPLICATION_INLINE ${APPLICATION_HDR_DIR}/*.hpp)
file(GLOB APPLICATION_SOURCE ${APPLICATION_SRC_DIR}/*.cpp)

file(GLOB ASSET_HEADER ${ASSET_HDR_DIR}/*.h)
file(GLOB ASSET_INLINE ${ASSET_HDR_DIR}/*.hpp)
file(GLOB ASSET_SOURCE ${ASSET_SRC_DIR}/*.cpp)

file(GLOB ASSET_ENTITY_HEADER ${ASSET_ENTITY_HDR_DIR}/*.h)
file(GLOB ASSET_ENTITY_INLINE ${ASSET_ENTITY_HDR_DIR}/*.hpp)
file(GLOB ASSET_ENTITY_SOURCE ${ASSET_ENTITY_SRC_DIR}/*.cpp)

file(GLOB ASSET_ENTITY_GLTF_HEADER ${ASSET_ENTITY_GLTF_HDR_DIR}/*.h)
file(GLOB ASSET_ENTITY_GLTF_INLINE ${ASSET_ENTITY_GLTF_HDR_DIR}/*.hpp)
file(GLOB ASSET_ENTITY_GLTF_SOURCE ${ASSET_ENTITY_GLTF_SRC_DIR}/*.cpp)

file(GLOB ASSET_ENTITY_STINKY_HEADER ${ASSET_ENTITY_STINKY_HDR_DIR}/*.cpp)
file(GLOB ASSET_ENTITY_STINKY_INLINE ${ASSET_ENTITY_STINKY_HDR_DIR}/*.cpp)
file(GLOB ASSET_ENTITY_STINKY_SOURCE ${ASSET_ENTITY_STINKY_SRC_DIR}/*.cpp)

file(GLOB ASSET_HANDLER_HEADER ${ASSET_HANDLER_HDR_DIR}/*.h)
file(GLOB ASSET_HANDLER_INLINE ${ASSET_HANDLER_HDR_DIR}/*.hpp)
file(GLOB ASSET_HANDLER_SOURCE ${ASSET_HANDLER_SRC_DIR}/*.cpp)

file(GLOB ASSET_HANDLER_GLTF_HEADER ${ASSET_HANDLER_GLTF_HDR_DIR}/*.h)
file(GLOB ASSET_HANDLER_GLTF_INLINE ${ASSET_HANDLER_GLTF_HDR_DIR}/*.hpp)
file(GLOB ASSET_HANDLER_GLTF_SOURCE ${ASSET_HANDLER_GLTF_SRC_DIR}/*.cpp)

file(GLOB ASSET_HANDLER_STINKY_HEADER ${ASSET_HANDLER_STINKY_HDR_DIR}/*.h)
file(GLOB ASSET_HANDLER_STINKY_INLINE ${ASSET_HANDLER_STINKY_HDR_DIR}/*.hpp)
file(GLOB ASSET_HANDLER_STINKY_SOURCE ${ASSET_HANDLER_STINKY_SRC_DIR}/*.cpp)

file(GLOB CAMERA_SOURCE ${CAMERA_SRC_DIR}/*.cpp)
file(GLOB CAMERA_HEADER ${CAMERA_HDR_DIR}/*.h)
file(GLOB CAMERA_INLINE ${CAMERA_HDR_DIR}/*.hpp)

file(GLOB CORE_SOURCE ${CORE_SRC_DIR}/*.cpp)
file(GLOB CORE_HEADER ${CORE_HDR_DIR}/*.h)
file(GLOB CORE_INLINE ${CORE_HDR_DIR}/*.hpp)

file(GLOB ECS_SOURCE ${ECS_SRC_DIR}/*.cpp)
file(GLOB ECS_HEADER ${ECS_HDR_DIR}/*.h)
file(GLOB ECS_INLINE ${ECS_HDR_DIR}/*.hpp)

file(GLOB EVENT_SOURCE ${EVENT_SRC_DIR}/*.cpp)
file(GLOB EVENT_HEADER ${EVENT_HDR_DIR}/*.h)
file(GLOB EVENT_INLINE ${EVENT_HDR_DIR}/*.hpp)

file(GLOB GLA_SOURCE ${GLA_SRC_DIR}/*.cpp)
file(GLOB GLA_HEADER ${GLA_HDR_DIR}/*.h)
file(GLOB GLA_INLINE ${GLA_HDR_DIR}/*.hpp)

file(GLOB GLA_OPENGL_SOURCE ${OPENGL_SRC_DIR}/*.cpp)
file(GLOB GLA_OPENGL_HEADER ${OPENGL_HDR_DIR}/*.h)
file(GLOB GLA_OPENGL_INLINE ${OPENGL_HDR_DIR}/*.hpp)

file(GLOB RENDERER_SOURCE ${RENDERER_SRC_DIR}/*.cpp)
file(GLOB RENDERER_HEADER ${RENDERER_HDR_DIR}/*.h)
file(GLOB RENDERER_INLINE ${RENDERER_HDR_DIR}/*.hpp)

file(GLOB ROOT_SOURCE ${SRC_DIR}/*.cpp)
file(GLOB ROOT_HEADER ${HDR_DIR}/*.h)
file(GLOB ROOT_INLINE ${HDR_DIR}/*.hpp)

file(GLOB SCENE_SOURCE ${SCENE_SRC_DIR}/*.cpp)
file(GLOB SCENE_HEADER ${SCENE_HDR_DIR}/*.h)
file(GLOB SCENE_INLINE ${SCENE_HDR_DIR}/*.hpp)

file(GLOB STB_SOURCE ${STB_DIR}/*.cpp)
file(GLOB STB_HEADER ${STB_DIR}/*.h)
file(GLOB STB_INLINE ${STB_DIR}/*.hpp)

file(GLOB STINKY_TINY_GLTF_SOURCE ${STINKY_TINY_GLTF_DIR}/*.cpp)

file(GLOB WINDOW_SOURCE ${WINDOW_SRC_DIR}/*.cpp)
file(GLOB WINDOW_HEADER ${WINDOW_HDR_DIR}/*.h)
file(GLOB WINDOW_INLINE ${WINDOW_HDR_DIR}/*.hpp)

file(GLOB WINDOW_GLFW_SOURCE ${WINDOW_GLFW_SRC_DIR}/*.cpp)
file(GLOB WINDOW_GLFW_HEADER ${WINDOW_GLFW_HDR_DIR}/*.h)
file(GLOB WINDOW_GLFW_INLINE ${WINDOW_GLFW_HDR_DIR}/*.hpp)

source_group("Header Files/application" FILES ${APPLICATION_HEADER})
source_group("Inline Files/application" FILES ${APPLICATION_INLINE})
source_group("Source Files/application" FILES ${APPLICATION_SOURCE})

source_group("Header Files/asset" FILES ${ASSET_HEADER})
source_group("Inline Files/asset" FILES ${ASSET_INLINE})
source_group("Source Files/asset" FILES ${ASSET_SOURCE})

source_group("Header Files/asset/entity" FILES ${ASSET_ENTITY_HEADER})
source_group("Inline Files/asset/entity" FILES ${ASSET_ENTITY_INLINE})
source_group("Source Files/asset/entity" FILES ${ASSET_ENTITY_SOURCE})

source_group("Header Files/asset/entity/gltf" FILES ${ASSET_ENTITY_GLTF_HEADER})
source_group("Inline Files/asset/entity/gltf" FILES ${ASSET_ENTITY_GLTF_INLINE})
source_group("Source Files/asset/entity/gltf" FILES ${ASSET_ENTITY_GLTF_SOURCE})

source_group("Header Files/asset/entity/stinky" FILES ${ASSET_ENTITY_STINKY_HEADER})
source_group("Inline Files/asset/entity/stinky" FILES ${ASSET_ENTITY_STINKY_INLINE})
source_group("Source Files/asset/entity/stinky" FILES ${ASSET_ENTITY_STINKY_SOURCE})

source_group("Header Files/asset/handler" FILES ${ASSET_HANDLER_HEADER})
source_group("Inline Files/asset/handler" FILES ${ASSET_HANDLER_INLINE})
source_group("Source Files/asset/handler" FILES ${ASSET_HANDLER_SOURCE})

source_group("Header Files/asset/handler/gltf" FILES ${ASSET_HANDLER_GLTF_HEADER})
source_group("Inline Files/asset/handler/gltf" FILES ${ASSET_HANDLER__GLTF_INLINE})
source_group("Source Files/asset/handler/gltf" FILES ${ASSET_HANDLER_GLTF_SOURCE})

source_group("Header Files/asset/handler/stinky" FILES ${ASSET_HANDLER_STINKY_HEADER})
source_group("Inline Files/asset/handler/stinky" FILES ${ASSET_HANDLER_STINKY_INLINE})
source_group("Source Files/asset/handler/stinky" FILES ${ASSET_HANDLER_STINKY_SOURCE})

source_group("Header Files/camera" FILES ${CAMERA_HEADER})
source_group("Inline Files/camera" FILES ${CAMERA_INLINE})
source_group("Source Files/camera" FILES ${CAMERA_SOURCE})

source_group("Header Files/core" FILES ${CORE_HEADER})
source_group("Inline Files/core" FILES ${CORE_INLINE})
source_group("Source Files/core" FILES ${CORE_SOURCE})

source_group("Header Files/ecs" FILES ${ECS_HEADER})
source_group("Inline Files/ecs" FILES ${ECS_INLINE})
source_group("Source Files/ecs" FILES ${ECS_SOURCE})

source_group("Header Files/event" FILES ${EVENT_HEADER})
source_group("Inline Files/event" FILES ${EVENT_INLINE})
source_group("Source Files/event" FILES ${EVENT_SOURCE})

source_group("Header Files/gla" FILES ${GLA_HEADER})
source_group("Inline Files/gla" FILES ${GLA_INLINE})
source_group("Source Files/gla" FILES ${GLA_SOURCE})

source_group("Inline OPENGL Files/gla/opengl" FILES ${GLA_OPENGL_INLINE})
source_group("Source OPENGL Files/gla/opengl" FILES ${GLA_OPENGL_SOURCE})
source_group("Header OPENGL Files/gla/opengl" FILES ${GLA_OPENGL_HEADER})

source_group("Header Files/renderer" FILES ${RENDERER_HEADER})
source_group("Inline Files/renderer" FILES ${RENDERER_INLINE})
source_group("Source Files/renderer" FILES ${RENDERER_SOURCE})

source_group("Header Files/" FILES ${ROOT_HEADER})
source_group("Inline Files/" FILES ${ROOT_INLINE})
source_group("Source Files/" FILES ${ROOT_SOURCE})

source_group("Header Files/scene" FILES ${SCENE_HEADER})
source_group("Inline Files/scene" FILES ${SCENE_INLINE})
source_group("Source Files/scene" FILES ${SCENE_SOURCE})

source_group("Header Files/stb" FILES ${STB_HEADER})
source_group("Inline Files/stb" FILES ${STB_INLINE})
source_group("Source Files/stb" FILES ${STB_SOURCE})

source_group("Source Files/tinygltf" FILES ${STINKY_TINY_GLTF_SOURCE})

source_group("Header Files/windows" FILES ${WINDOW_HEADER})
source_group("Inline Files/windows" FILES ${WINDOW_INLINE})
source_group("Source Files/window" FILES ${WINDOW_SOURCE})

source_group("Header Files/windows" FILES ${WINDOW_GLFW_HEADER})
source_group("Inline Files/windows" FILES ${WINDOW_GLFW_INLINE})
source_group("Source Files/window" FILES ${WINDOW_GLFW_SOURCE})
set(STINKY_HEADERS
        ${APPLICATION_HEADER}
        ${APPLICATION_INLINE}
        ${ASSET_HEADER}
        ${ASSET_INLINE}
        ${ASSET_ENTITY_HEADER}
        ${ASSET_ENTITY_INLINE}
        ${ASSET_ENTITY_GLTF_HEADER}
        ${ASSET_ENTITY_GLTF_INLINE}
        ${ASSET_ENTITY_STINKY_HEADER}
        ${ASSET_ENTITY_STINKY_INLINE}
        ${ASSET_HANDLER_HEADER}
        ${ASSET_HANDLER_INLINE}
        ${ASSET_HANDLER_GLTF_HEADER}
        ${ASSET_HANDLER_GLTF_INLINE}
        ${ASSET_HANDLER_STINKY_HEADER}
        ${ASSET_HANDLER_STINKY_INLINE}
        ${CAMERA_HEADER}
        ${CAMERA_HEADER}
        ${CORE_HEADER}
        ${CORE_INLINE}
        ${ECS_HEADER}
        ${ECS_INLINE}
        ${EVENT_HEADER}
        ${EVENT_INLINE}
        ${GLA_HEADER}
        ${GLA_INLINE}
        ${GLA_OPENGL_HEADER}
        ${GLA_OPENGL_INLINE}
        ${ROOT_HEADER}
        ${ROOT_INLINE}
        ${RENDERER_HEADER}
        ${RENDERER_INLINE}
        ${SCENE_HEADER}
        ${SCENE_INLINE}
        ${STB_HEADER}
        ${STB_INLINE}
        ${WINDOW_HEADER}
        ${WINDOW_INLINE}
        ${WINDOW_GLFW_HEADER}
        ${WINDOW_GLFW_INLINE}
        )

set(STINKY_SOURCES
        ${APPLICATION_SOURCE}
        ${ASSET_SOURCE}
        ${ASSET_ENTITY_SOURCE}
        ${ASSET_ENTITY_GLTF_SOURCE}
        ${ASSET_ENTITY_STINKY_SOURCE}
        ${ASSET_HANDLER_SOURCE}
        ${ASSET_HANDLER_GLTF_SOURCE}
        ${ASSET_HANDLER_STINKY_SOURCE}
        ${CAMERA_SOURCE}
        ${CORE_SOURCE}
        ${ECS_SOURCE}
        ${EVENT_SOURCE}
        ${GLA_SOURCE}
        ${GLA_OPENGL_SOURCE}
        ${RENDERER_SOURCE}
        ${ROOT_SOURCE}
        ${SCENE_SOURCE}
        ${STB_SOURCE}
        ${STINKY_TINY_GLTF_SOURCE}
        ${WINDOW_SOURCE}
        ${WINDOW_GLFW_SOURCE}
        )