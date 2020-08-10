cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

#set(STINKY_VERSION ${GLM_VERSION_MAJOR}.${GLM_VERSION_MINOR}.${GLM_VERSION_PATCH}.${GLM_VERSION_REVISION})
project(stinky LANGUAGES CXX)
#message(STATUS "Stinky : Version " ${STINKY_VERSION})

enable_testing()

set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/vendor/spdlog)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/vendor/glm)

#3rd party libraries
add_subdirectory(${SPDLOG_DIR})
add_subdirectory(${GLM_DIR})

#Submodules
add_subdirectory(stinky-engine)
add_subdirectory(stinky-sandbox)

add_library(stinky::stinky-engine ALIAS stinky-engine)
add_executable(stinky::stinky-sandbox ALIAS stinky-sandbox)