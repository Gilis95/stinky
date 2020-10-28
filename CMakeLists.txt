cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

#set(STINKY_VERSION ${GLM_VERSION_MAJOR}.${GLM_VERSION_MINOR}.${GLM_VERSION_PATCH}.${GLM_VERSION_REVISION})
project(stinky LANGUAGES CXX)
#message(STATUS "Stinky : Version " ${STINKY_VERSION})

enable_testing()

set(ENTT_DIR ${PROJECT_SOURCE_DIR}/vendor/entt)
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/vendor/glfw/)
set(GLM_DIR ${PROJECT_SOURCE_DIR}/vendor/glm)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/vendor/spdlog)

set(ENTT_DIR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/entt/src)
set(OPENGL_INCLUDE_DIRS ${GLAD_DIR}/include)
set(WINDOW_ABSTRACTION_INCLUDE_DIR ${GLFW_DIR}/include)

set(OPENGL_LIB glad)
set(WINDOW_ABSTRACTION_LIB glfw)

#3rd party libraries
add_subdirectory(${ENTT_DIR})
add_subdirectory(${GLAD_DIR})
add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLM_DIR})
add_subdirectory(${SPDLOG_DIR})

#Submodules
add_subdirectory(stinky-engine)
add_subdirectory(stinky-sandbox)
add_subdirectory(hoatzin-editor)

add_library(stinky::stinky-engine ALIAS stinky-engine)
add_executable(stinky::stinky-sandbox ALIAS stinky-sandbox)
add_executable(stinky::hoatzin-editor ALIAS hoatzin-editor)