include(FetchContent)
cmake_minimum_required(VERSION 3.20)
project(Pong)

set(CMAKE_C_STANDARD 99)
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(${PROJECT_NAME} src/Main.c
        src/Game.c
        src/Objects/Paddle.h
        src/Core.h
        src/Objects/Paddle.c
        src/Objects/Ball.h
        src/Objects/Ball.c
        src/Core.c
        src/States/Gameplay.c
        src/States/Gameplay.h
        src/SaveData.c
        src/SaveData.h
        src/States/Menu.c
        src/States/Menu.h
        src/States/Menu.c
        src/States/End.c
        src/States/End.h
        src/States/Settings.c
        src/States/Settings.h
        src/States/Pause.c
        src/States/Pause.h
)
include_directories(include)
target_link_libraries(${PROJECT_NAME} raylib)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res)
