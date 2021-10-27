cmake_minimum_required(VERSION 3.21.3)
project(engine
        VERSION 0.001
        DESCRIPTION "engine"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(RmlUi CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

add_subdirectory(Engine)
add_subdirectory(External)
add_subdirectory(Game)
add_subdirectory(apps)

#file(GLOB SOURCES "src/*/**.cpp" "src/*/**.c")
#file(GLOB INCLUDE "include/*/**.hpp" "include/*/**.h")

#include_directories(${INCLUDE})

#add_executable(engine_to_cmake ${SOURCES})

#target_include_directories(engine_to_cmake PRIVATE ${INCLUDE})
#target_link_libraries(engine_to_cmake PRIVATE SDL2::SDL2 SDL2::SDL2main)