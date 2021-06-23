cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

#set(STINKY_VERSION ${GLM_VERSION_MAJOR}.${GLM_VERSION_MINOR}.${GLM_VERSION_PATCH}.${GLM_VERSION_REVISION})
project(stinky VERSION 1.0.0 LANGUAGES CXX)
#message(STATUS "Stinky : Version " ${STINKY_VERSION})

#Fetch common dependencies
include(cmake/FetchDependencies.cmake)

#Fetch editor dependencies
include(hoatzin-editor/cmake/FetchDependencies.cmake)

set(OPENGL_LIB glad)
set(WINDOW_ABSTRACTION_LIB glfw)

#Submodules
add_subdirectory(stinky-engine)
add_subdirectory(stinky-sandbox)
add_subdirectory(hoatzin-editor)

add_library(stinky::stinky-engine ALIAS stinky-engine)
add_executable(stinky::stinky-sandbox ALIAS stinky-sandbox)
add_executable(stinky::hoatzin-editor ALIAS hoatzin-editor)