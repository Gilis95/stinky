cmake_minimum_required(VERSION 3.2)
project(stinky-sandbox)

set (CMAKE_CXX_STANDARD 17)

add_definitions(-DSTINKY_ENABLE_LOG -D_CRT_SECURE_NO_WARNINGS -DSTINKY_ENGINE_DEBUG -DTRACY_ENABLE)

set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(ETT_DIR ${PROJECT_SOURCE_DIR}/../vendor/entt)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/../vendor/glm/)
set(STINKY_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../stinky-engine)

set(HDR_FILES  
    ${HDR_DIR}/StinkyApplication.h 
    ${HDR_DIR}/StinkyLayer.h
        ../stinky-engine/src/camera/FPSCamera.h)

set(SRC_FILES 
    ${SRC_DIR}/StinkyApplication.cpp
    ${SRC_DIR}/StinkyLayer.cpp
    )

add_executable(stinky-sandbox ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-sandbox PRIVATE 
                            ${HDR_DIR}
                            ${STINKY_ENGINE_DIR}/src
                            ${SPDLOG_DIR}/include
                            ${GLM_DIR}
                            ${ETT_DIR}/src
                            )

target_link_libraries(stinky-sandbox PRIVATE 
                      stinky::stinky-engine
                      spdlog
                      )
