################################################################################################
#Project Header directory
set(HDR_DIR ${PROJECT_SOURCE_DIR}/src)

set(APPLICATION_HDR_DIR ${HDR_DIR}/application)
set(ASSET_HDR_DIR ${HDR_DIR}/asset)
set(ASSET_ENTITY_HDR_DIR ${ASSET_HDR_DIR}/entity)
set(ASSET_ENTITY_GLTF_HDR_DIR ${ASSET_ENTITY_HDR_DIR}/gltf)
set(ASSET_ENTITY_STINKY_HDR_DIR ${ASSET_ENTITY_HDR_DIR}/stinky)
set(ASSET_HANDLER_HDR_DIR ${ASSET_HDR_DIR}/handler)
set(ASSET_HANDLER_GLTF_HDR_DIR ${ASSET_HANDLER_HDR_DIR}/gltf)
set(ASSET_HANDLER_STINKY_HDR_DIR ${ASSET_HANDLER_HDR_DIR}/stinky)
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
set(ASSET_ENTITY_SRC_DIR ${ASSET_SRC_DIR}/entity)
set(ASSET_ENTITY_GLTF_SRC_DIR ${ASSET_ENTITY_SRC_DIR}/gltf)
set(ASSET_ENTITY_STINKY_SRC_DIR ${ASSET_ENTITY_SRC_DIR}/stinky)
set(ASSET_HANDLER_SRC_DIR ${ASSET_SRC_DIR}/handler)
set(ASSET_HANDLER_GLTF_SRC_DIR ${ASSET_HANDLER_SRC_DIR}/gltf)
set(ASSET_HANDLER_STINKY_SRC_DIR ${ASSET_HANDLER_SRC_DIR}/stinky)
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
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(STB_DIR ${VENDOR_DIR}/stb_image)
set(STINKY_TINY_GLTF_DIR ${VENDOR_DIR}/tinygltf)