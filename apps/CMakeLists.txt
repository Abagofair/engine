add_executable(Paddle main.cpp)

target_compile_features(Paddle PRIVATE cxx_std_17)

target_include_directories(Paddle PRIVATE ${engine_SOURCE_DIR}/Game/include)

target_link_libraries(Paddle PRIVATE External)
target_link_libraries(Paddle PRIVATE Engine)
target_link_libraries(Paddle PRIVATE Game)

target_link_libraries(Paddle PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(Engine PRIVATE SDL2::SDL2_image)