include(FetchContent)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.7.1
)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Gilis95/glad.git
        GIT_TAG ab5edbd78901d3639a13934634f6c2de46640c3b
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.4
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.8.5
)

FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/Gilis95/tracy.git
        GIT_TAG 1c0b429689045aa1ae3fcc58c8ae1617bb7f5ebf
)

FetchContent_Declare(
        yaml
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)

FetchContent_Declare(
        tinygltf
        GIT_REPOSITORY https://github.com/Gilis95/tinygltf.git
        GIT_TAG 1484fea15f09dfec9ad6c7e3496d8198eba6417e
)

FetchContent_GetProperties(tinygltf)
if(NOT tinygltf_POPULATED)
    FetchContent_Populate(tinygltf)
    set(TINYGLTF_HEADER_ONLY ON)
    add_subdirectory(${tinygltf_SOURCE_DIR} ${tinygltf_BINARY_DIR})
endif()

FetchContent_MakeAvailable(EnTT glad glfw glm spdlog tracy yaml)