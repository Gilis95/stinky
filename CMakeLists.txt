cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

#set(STINKY_VERSION ${GLM_VERSION_MAJOR}.${GLM_VERSION_MINOR}.${GLM_VERSION_PATCH}.${GLM_VERSION_REVISION})
project(stinky LANGUAGES CXX)
#message(STATUS "Stinky : Version " ${STINKY_VERSION})

enable_testing()

add_subdirectory(stinky-engine)
add_subdirectory(stinky-sandbox)

add_library(stinky::stinky-engine ALIAS stinky-engine)

