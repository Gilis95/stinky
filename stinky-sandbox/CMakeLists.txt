project(stinky-sandbox)

add_definitions(-DSTINKY_ENABLE_LOG -DSK_PLATFORM_LINUX -DTRACY_ENABLE -DGLFW_INCLUDE_NONE)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(HDR_FILES
        ${HDR_DIR}/StinkyApplication.h
        ${HDR_DIR}/StinkyLayer.h
        )

set(SRC_FILES
        ${SRC_DIR}/StinkyApplication.cpp
        ${SRC_DIR}/StinkyLayer.cpp
        )

add_executable(stinky-sandbox ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-sandbox PRIVATE ${stinky-engine_INCLUDES} ${HDR_DIR})

target_link_libraries(stinky-sandbox PRIVATE EnTT glad glfw glm spdlog stinky::stinky-engine tracy)
