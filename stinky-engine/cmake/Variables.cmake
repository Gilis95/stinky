################################################################################################
#Project Header directory
set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_HDR_DIR ${HDR_DIR}/application)
set(ASSET_HDR_DIR ${HDR_DIR}/asset)
set(ASSET_MESH_HDR_DIR ${ASSET_HDR_DIR}/mesh)
set(ASSET_SERIALIZER_HDR_DIR ${ASSET_HDR_DIR}/serializer)
set(CAMERA_HDR_DIR ${HDR_DIR}/camera)
set(CORE_HDR_DIR ${HDR_DIR}/core)
set(ECS_HDR_DIR ${HDR_DIR}/ecs)
set(EVENT_HDR_DIR ${HDR_DIR}/event)
set(GLA_HDR_DIR ${HDR_DIR}/gla)
set(OPENGL_HDR_DIR ${GLA_HDR_DIR}/platform/opengl)
set(RENDERER_HDR_DIR ${HDR_DIR}/renderer)
set(SCENE_HDR_DIR ${HDR_DIR}/scene)
set(WINDOW_HDR_DIR ${HDR_DIR}/window)
set(WINDOW_GLFW_HDR_DIR ${WINDOW_HDR_DIR}/glfw)

################################################################################################
#Project source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_SRC_DIR ${SRC_DIR}/application)
set(ASSET_SRC_DIR ${SRC_DIR}/asset)
set(ASSET_MESH_SRC_DIR ${ASSET_SRC_DIR}/mesh)
set(ASSET_SERIALIZER_SRC_DIR ${ASSET_SRC_DIR}/serializer)
set(CAMERA_SRC_DIR ${SRC_DIR}/camera)
set(CORE_SRC_DIR ${SRC_DIR}/core)
set(EVENT_SRC_DIR ${SRC_DIR}/event)
set(ECS_SRC_DIR ${SRC_DIR}/ecs)
set(GLA_SRC_DIR ${SRC_DIR}/gla)
set(OPENGL_SRC_DIR ${GLA_SRC_DIR}/platform/opengl)
set(RENDERER_SRC_DIR ${SRC_DIR}/renderer)
set(SCENE_SRC_DIR ${SRC_DIR}/scene)
set(WINDOW_SRC_DIR ${SRC_DIR}/window)
set(WINDOW_GLFW_SRC_DIR ${WINDOW_SRC_DIR}/glfw)

################################################################################################
#Dependencies directory
set(STB_DIR ${PROJECT_SOURCE_DIR}/vendor/stb_image)