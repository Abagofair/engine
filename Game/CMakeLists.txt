include_directories(${engine_SOURCE_DIR}/Game/include)

add_library(
        Game

        STATIC

        src/Ball.cpp
        src/Block.cpp
        src/Paddle.cpp
        src/PaddleGame.cpp
        src/TestScene.cpp

        include/Generated/EntityType.hpp
        include/Ball.hpp
        include/Block.hpp
        include/GameComponents.hpp
        include/Paddle.hpp
        include/PaddleGame.hpp
        include/TestScene.hpp
)

target_include_directories(Game PUBLIC ${engine_SOURCE_DIR}/Game/include)

target_link_libraries(Game PUBLIC External)
target_link_libraries(Game PUBLIC Engine)