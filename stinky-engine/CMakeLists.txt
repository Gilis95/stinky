project(stinky-engine VERSION 1.0.0 LANGUAGES CXX)

add_definitions(-DSTINKY_ENABLE_LOG -D_CRT_SECURE_NO_WARNINGS -DSTINKY_ENGINE_DEBUG -DTRACY_ENABLE -DGLFW_INCLUDE_NONE)

option(STINKY_ENGINE_INSTALL "Generate installation target" OFF)

include(cmake/Files.cmake)

################################################################################################
add_library(stinky-engine STATIC ${STINKY_HEADERS} ${STINKY_SOURCES})

target_include_directories(stinky-engine PUBLIC
        $<BUILD_INTERFACE: ${HDR_DIR} ${STB_DIR}>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(stinky-engine PRIVATE EnTT glad glfw glm spdlog tracy)

if (STINKY_ENGINE_INSTALL)
    # cmake install dirs
    include(GNUInstallDirs)

    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/stinkyEngineConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/stinkyEngineConfig.cmake")
    set(targets_export_name "stinkyEngineTargets")
    set(namespace "stinky::")

    # Include module with function 'write_basic_package_version_file'
    include(CMakePackageConfigHelpers)

    # Configure 'gladConfigVersion.cmake'
    # PROJECT_VERSION is used as a VERSION
    write_basic_package_version_file("${version_config}" COMPATIBILITY SameMajorVersion)

    # Configure 'tracyConfig.cmake'
    # Uses targets_export_name variable.
    configure_package_config_file(
            "Config.cmake.in"
            "${project_config}"
            INSTALL_DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/stinky)

    # Targets:
    install(
            TARGETS stinky-engine
            EXPORT "${targets_export_name}"
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${APPLICATION_HEADER} ${APPLICATION_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/application)

    install(FILES ${CAMERA_HEADER} ${CAMERA_HEADER}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/camera)

    install(FILES ${CORE_HEADER} ${CORE_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/core)

    install(FILES ${ECS_HEADER} ${ECS_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/ecs)

    install(FILES ${EVENT_HEADER} ${EVENT_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/event)

    install(FILES ${GLA_HEADER} ${GLA_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/gla)

    install(FILES ${GLA_OPENGL_HEADER} ${GLA_OPENGL_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/gla/platform/opengl)

    install(FILES ${ROOT_HEADER} ${ROOT_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/)

    install(FILES ${RENDERER_HEADER} ${RENDERER_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/renderer)

    install(FILES ${SCENE_HEADER} ${SCENE_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/scene)

    install(FILES ${WINDOW_HEADER} ${WINDOW_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/window)

    install(FILES ${WINDOW_GLFW_HEADER} ${WINDOW_GLFW_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/stinky/window)

    # Install stinkyConfig.cmake, stinkyConfigVersion.cmake
    install(
            FILES "${project_config}" "${version_config}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/stinky)

    # Create and install stinkyTargets.cmake
    install(
            EXPORT "${targets_export_name}"
            NAMESPACE "${namespace}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/stinky)
endif ()