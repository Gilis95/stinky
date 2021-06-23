include(FetchContent)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY git@github.com:skypjack/entt.git
        GIT_TAG v3.7.1
)

FetchContent_Declare(
        glad
        GIT_REPOSITORY git@github.com:Gilis95/glad.git
        GIT_TAG ab5edbd78901d3639a13934634f6c2de46640c3b
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY git@github.com:glfw/glfw.git
        GIT_TAG 3.3.4
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY git@github.com:g-truc/glm.git
        GIT_TAG 0.9.9.8
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY git@github.com:gabime/spdlog.git
        GIT_TAG v1.8.5
)

FetchContent_Declare(
        tracy
        GIT_REPOSITORY git@github.com:Gilis95/tracy.git
        GIT_TAG 15d25f811950bc5c63e8681dbdd75537ca78c9ac
)

FetchContent_MakeAvailable(EnTT glad glfw glm spdlog tracy)