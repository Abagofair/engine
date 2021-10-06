file(   GLOB_RECURSE
        HEADER_LIST
        LIST_DIRECTORIES true
        CONFIGURE_DEPENDS
        "${engine_SOURCE_DIR}/Game/include/*.hpp")

add_library(
        Game

        STATIC

        src/Ball.cpp
        src/Block.cpp
        src/Paddle.cpp
        src/PaddleGame.cpp
        src/TestScene.cpp

        ${HEADER_LIST})

target_include_directories(Game PUBLIC "${engine_SOURCE_DIR}")
target_include_directories(Game PUBLIC ${HEADER_LIST})

target_link_libraries(Game PUBLIC External)
target_link_libraries(Game PUBLIC Engine)