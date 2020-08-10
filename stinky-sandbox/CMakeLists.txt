cmake_minimum_required(VERSION 3.16)
project(stinky-sandbox)

set (CMAKE_CXX_STANDARD 17)


set(HDR_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(STINKY_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../stinky-engine)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/../vendor/glm/)

set(HDR_FILES  
    ${HDR_DIR}/StinkyApplication.h 
    ${HDR_DIR}/StinkyLayer.h
    )

set(SRC_FILES 
    ${SRC_DIR}/StinkyApplication.cpp
    ${SRC_DIR}/StinkyLayer.cpp
    )

add_executable(stinky-sandbox ${SRC_FILES} ${HDR_FILES})

target_include_directories(stinky-sandbox PRIVATE 
                            ${HDR_DIR}
                            ${STINKY_ENGINE_DIR}/include
                            ${SPDLOG_DIR}/include
                            ${GLM_DIR}
                            )

target_link_libraries(stinky-sandbox PRIVATE 
                      stinky::stinky-engine
                      spdlog
                      )
